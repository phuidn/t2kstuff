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
	ifstream matrixfile("kinetic-out2.txt"), datafile("magnetenergies.txt");
	string line;
	vector<double> truthv,reconv,data,datatruth;
	int nbins=5;
	double bounds[6]={0.,0.224,0.448,0.672,0.896,1.12};
	for(int i=0;i<6;i++) bounds[i] = bounds[i]*1000000./(2.*938.);
	for(int i=0;i<6;i++) cout <<bounds[i] <<endl;
	int startpos,endpos;
	int len=-1;
	cout << "reading matrix file" << endl;
	while(matrixfile.good())
	{
		getline(matrixfile,line,',');
		reconv.push_back(atof(line.c_str()));
		getline(matrixfile,line);
		truthv.push_back(atof(line.c_str()));
		len++;
	}
	cout << "reading data file" << endl;
	while(datafile.good()){
		getline(datafile, line, ',');
		data.push_back(atof(line.c_str()));
		data.back()/=(2.*938.);
		getline(datafile, line);
		datatruth.push_back(atof(line.c_str()));
		datatruth.back()/=(2.*938.);
	}
	cout << "scaling matrix data" << endl;
	for(int i=0;i<len;i++)
	{//normalise to correct units
		truthv[i] = truthv[i]/(2.*938.);
		reconv[i] = reconv[i]/(2.*938.);
	}
	cout << "Vectors made, "<<len<<" lines long."<<endl;

	//Populate Histograms for unfolding
	TH1D *reconhist = new TH1D("reconhist","Title",nbins,bounds);
	TH1D *truthhist = new TH1D("truthhist","Title",nbins,bounds);
	TH2D *matrixhist= new TH2D("matrixhist","Titl3",nbins,bounds,nbins,bounds);
	TH1D *datahist = new TH1D("datahist","Title",nbins,bounds);
	TH1D *truedatahist = new TH1D("truedatahist","Title",nbins,bounds);
	TH2D *meascov;
	TH1D *unfolded;
	TH2D *unfcov;
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
	
	TSVDUnfold *unf = new TSVDUnfold(datahist,reconhist,truthhist,matrixhist);
	unfolded = unf->Unfold(2.);
//	meascov = unf->GetXinv();	//this doesn't seem to work, not sure why
	unfcov = unf->GetAdetCovMatrix(5000, 32);
	cout << "truth count = " << truedatahist->GetEntries() << ", unfolded count = " << unfolded->GetEntries() << endl;
//	meascov->Draw("COLZ");
//	unfcov->Draw("COLZ");
	for(int k(1); k<nbins+1; k++){
		unfolded->SetBinError(k,sqrt(unfcov->GetBinContent(k,k)));
		cout << unfolded->GetBinContent(k) << "	";
	}
	unfolded->Draw("E1");
	truedatahist->Draw("same");
	cout << endl;
	App->Run();

	return 0;

/*	//Input section (old)
	ifstream infile("energyhists.txt");
	unsigned int nbins(0), felement(0);
	string line;
	getline(infile, line);	//line 1: number of bins
	nbins = atoi(line.c_str());
	//cout << "nbins= "<< nbins << endl;
	double bounds[nbins+1], recon[nbins], truth[nbins], data[nbins],truedata[nbins];//,matrix[nbins][nbins];
	double **matrix;
	matrix = (double**)malloc(nbins*sizeof(double*));
	for(int i=0; i<nbins;i++)
		matrix[i] = (double*)malloc(nbins*sizeof(double));
	parseline(nbins+1, bounds, &infile); //line2: bin boundaries
	parseline(nbins, recon, &infile); //line3: recon vector
	parseline(nbins, truth, &infile); //line4: truth vector
	for(int i=0; i<nbins; i++)		//line5-10: migration matrix
		parseline(nbins,matrix[i],&infile);
	parseline(nbins, data, &infile); //lines 11 data
	parseline(nbins, truedata, &infile);//line 12 true values of data
*/

/*	//Populate Histograms for unfolding
	TH1D *reconhist = new TH1D("reconhist","Title",nbins,bounds);
	populateTH1D(nbins,bounds,recon,reconhist);
	TH1D *truthhist = new TH1D("truthhist","Title",nbins,bounds);
	populateTH1D(nbins,bounds,truth,truthhist);
	TH2D *matrixhist= new TH2D("matrixhist","Titl3",nbins,bounds,nbins,bounds);
	populateTH2D(nbins,bounds,matrix,matrixhist);
	TH1D *datahist = new TH1D("datahist","Title",nbins,bounds);
	populateTH1D(nbins,bounds,data,datahist);
	TH1D *truedatahist = new TH1D("truedatahist","Title",nbins,bounds);
	populateTH1D(nbins,bounds,truedata,truedatahist);

	//Unfolding section
	//Using the same recon data atm!! ***** CHANGE!!
	TSVDUnfold *unf = new TSVDUnfold(datahist,reconhist,truthhist,matrixhist);
	TH1D *unfresult = unf->Unfold(1);
	for(int k(0); k<nbins+2;k++)
	{
		cout << unfresult->GetBinContent(k)/truedatahist->GetBinContent(k) << "	";
	}
	truedatahist->Draw();
	unfresult->Draw("same");
	
	cout << endl;
//	reconhist->Draw("same");
	App->Run();
*/	
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

