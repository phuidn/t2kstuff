//Notes: is matrix right way round?
//		are bounds and energies in corect units
//


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <TSystem.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TSVDUnfold.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <math.h>

using namespace std;

void SetupROOT();
int parseline(int nelements, double* outarray, ifstream *file);	
int populateTH1D(int nbins,double *bounds, double *bins,TH1D *graph);
int populateTH2D(int nbins, double *bounds, double **matrix, TH2D *hist);

int main(int argc, char* argv[])
{
	//Setup
	TApplication *App = new TApplication("Application",(Int_t*)&argc, argv);
	TCanvas *canvas = new TCanvas("canvas", "canvas", 640, 640);
	SetupROOT();		

	//Input section
	//	Reads from kinetic energy list to make matrix and data vectors
	ifstream matrixfile("kinetic-out2.txt"), datafile("magnetTPC.txt");
	string line;
	vector<double> truthv,reconv,data,datatruth;
	int nbins=5;
	double bounds[6]={0.,0.25,0.5,0.75,1.,1.25};
//	for(int i=0;i<6;i++) bounds[i] = bounds[i]*1000000./(2.*938.);
	for(int i=0;i<6;i++) cout << bounds[i] <<endl;
	int startpos,endpos;
	int len=-1;
	cout << "reading matrix file" << endl;
	while(matrixfile.good())
	{
		getline(matrixfile,line,',');
		reconv.push_back(atof(line.c_str())/1000000.);
		getline(matrixfile,line);
		truthv.push_back(atof(line.c_str())/1000000.);
		len++;
	}
	cout << "reading data file" << endl;
	while(datafile.good()){
		getline(datafile, line, ',');
		data.push_back(atof(line.c_str()));
		data.back()/=1000000.;//(2.*938.);
		getline(datafile, line);
		datatruth.push_back(atof(line.c_str()));
		datatruth.back()/=1000000.;//(2.*938.);
	}
	cout << "scaling matrix data" << endl;
//	for(int i=0;i<len;i++)
//	{//normalise to correct units
//		truthv[i] = truthv[i]/(2.*938.);
//		reconv[i] = reconv[i]/(2.*938.);
//	}
	cout << "Vectors made, "<<len<<" lines long."<<endl;

	//Populate Histograms for unfolding
	TH1D *reconhist = new TH1D("reconhist","Title",nbins,bounds);
	TH1D *truthhist = new TH1D("truthhist","Title",nbins,bounds);
	TH2D *matrixhist= new TH2D("matrixhist","Detector Response Matrix",nbins,bounds,nbins,bounds);
	TH1D *datahist = new TH1D("datahist","Title",nbins,bounds);
	TH1D *truedatahist = new TH1D("truedatahist","Title",nbins,bounds);
	TH2D *meascov;
	TH1D *unfolded;
	TH2D *unfcov;
	TH1D *dvec;
	cout <<"Looping over vectors to make TH1Ds..."<<endl;
	for(int i=0;i<len;i++)
	{
		reconhist->Fill(reconv[i]);
		truthhist->Fill(truthv[i]);
		matrixhist->Fill(reconv[i],truthv[i]);
	}
	for(int i=0; i<data.size(); i++){
		datahist->Fill(data[i]);
		truedatahist->Fill(datatruth[i]);
	}
	Double_t mcPOT = 5.e17 * 1554;
	
	TSVDUnfold *unf = new TSVDUnfold(datahist,reconhist,truthhist,matrixhist);
	unfolded = unf->Unfold(2.25);
	unfcov = unf->GetAdetCovMatrix(5000, 32);  
	unfcov->Scale(sqrt(mcPOT / 1.e21));
	dvec = unf->GetD();
	cout << "truth count = " << truedatahist->GetEntries() << ", unfolded count = " << unfolded->GetEntries() << endl;
	TStyle *gStyle = new TStyle();
	gStyle->SetPalette(51,0);
	matrixhist->SetStats(0);
//	meascov->Draw("COLZ");
//	unfcov->Draw("COLZ");
	for(int k(1); k<nbins+1; k++){
		unfolded->SetBinError(k,sqrt(unfcov->GetBinContent(k,k)));
		cout << unfolded->GetBinError(k) / unfolded->GetBinContent(k) << "	";
	}
	unfolded->Draw("E1");
	truedatahist->Draw("same");
//	dvec->Draw();
	matrixhist->SetXTitle("Q^{2} / GeV^{2} (truth)");
	matrixhist->SetYTitle("Q^{2} / GeV^{2} (reconstructed)");
//	matrixhist->Draw("COLZ");
	cout << endl;
	App->Run();

	return 0;	
}


int populateTH1D(int nbins,double *bounds, double *bins,TH1D *graph)
{
	//TH1D *graph = new TH1D("graph","Title",nbins,bounds);
	for(int i=0; i<nbins; i++)
	{
		graph->SetBinContent(i+1,bins[i]);
		cout << "Bin " << i << " content= " << graph->GetBinContent(i+1) << endl;
	}
	return 0;
}

int populateTH2D(int nbins, double *bounds, double **matrix, TH2D *hist)
{
	for(int i=0; i<nbins; i++)
		for(int j=0; j<nbins;j++)
		{
			hist->SetBinContent(i+1,j+1,matrix[i][j]);
			cout << hist->GetBinContent(i+1,j+1);
			if(j==nbins-1) cout << endl;
			else cout << "    ";
		}
}

int parseline(int nelements, double* outarray, ifstream *file){	
	string line;
	for(int i=0;i<nelements; i++){
		getline(*file, line, ',');
		outarray[i] = atof(line.c_str());
		//cout << outarray[i];
		//if(i==nelements-1) cout<<endl;
		//else cout<<",";
	}
	return 0;
}

void SetupROOT(){
	gROOT->SetBatch(1);
	gSystem->AddIncludePath("-I$OAEVENT/src");
	gSystem->AddIncludePath("-I$OAANALYSISROOT/src");

	gSystem->Load("libPhysics");
	gSystem->Load("libGeom");
	gSystem->Load("libTree");
	gSystem->Load("libEG");
	gSystem->Load("libMinuit");
	gSystem->Load("libCLHEP.so");
	gSystem->Load("librecpack.so");
	gSystem->Load("liboaEvent.so");
	gSystem->Load("liboaRuntimeParameters.so");
	gSystem->Load("libMinosDBI.so");
	gSystem->Load("liboaOfflineDatabase.so");
	gSystem->Load("liboaUtility.so");
	gSystem->Load("libsmrdRecon.so");
	gSystem->Load("libBeamData.so");
	gSystem->Load("liboaBeamData.so");
	gSystem->Load("liboaAnalysis.so");
}

