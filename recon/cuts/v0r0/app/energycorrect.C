#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <TMath.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TSVDUnfold.h>
#include <TH1D.h>
#include <TH2D.h>

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
	ifstream infile("energyhists.txt");
	unsigned int nbins(0), felement(0);
	string line;
	getline(infile, line);	//line 1: number of bins
	nbins = atoi(line.c_str());
	//cout << "nbins= "<< nbins << endl;
	double bounds[nbins+1], recon[nbins], truth[nbins], data[nbins];//,matrix[nbins][nbins];
	double **matrix;
	matrix = (double**)malloc(nbins*sizeof(double*));
	for(int i=0; i<nbins;i++)
		matrix[i] = (double*)malloc(nbins*sizeof(double));
	parseline(nbins+1, bounds, &infile); //line2: bin boundaries
	parseline(nbins, recon, &infile); //line3: recon vector
	parseline(nbins, truth, &infile); //line4: truth vector
	for(int i=0; i<nbins; i++)		//line5-10: migration matrix
		parseline(nbins,matrix[i],&infile);

	//Populate Histograms for unfolding
	TH1D *reconhist = new TH1D("reconhist","Title",nbins,bounds);
	populateTH1D(nbins,bounds,recon,reconhist);
	TH1D *truthhist = new TH1D("truthhist","Title",nbins,bounds);
	populateTH1D(nbins,bounds,truth,truthhist);
	TH2D *matrixhist= new TH2D("matrixhist","Titl3",nbins,bounds,nbins,bounds);
	populateTH2D(nbins,bounds,matrix,matrixhist);


	//Unfolding section
	//****Using the same recon data atm!! ***** CHANGE!!*****//
	TSVDUnfold *unf = new TSVDUnfold(reconhist,reconhist,truthhist,matrixhist);
	unf->SetNormalize(kFALSE);
	TH1D *unfresult = unf->Unfold(0.1);
	TH1D* Dvec = unf->GetD();
	TH1D* SV = unf->GetSV();
	unfresult->Draw();
//	unfresult->Draw();
//	truthhist->Draw("same");
	for(int k(0); k<nbins+2; k++)
		cout << unfresult->GetBinContent(k)/truthhist->GetBinContent(k) << "	";
	cout << endl;
//	reconhist->Draw("same");
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

