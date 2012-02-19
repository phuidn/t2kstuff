#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <TSystem.h>
#include <TROOT.h>

using namespace std;

void SetupROOT();
int parseline(int nelements, double* outarray, ifstream *file);	

int main()
{
	SetupROOT();		
	ifstream infile("energyhists.txt");
	unsigned int nbins(0), felement(0);
	string line;
	getline(infile, line);	//line 1: number of bins
	nbins = atoi(line.c_str());
	cout << nbins << endl;
	double bounds[nbins+1], recon[nbins], truth[nbins], data[nbins], matrix[nbins][nbins];
	parseline(nbins+1, bounds, &infile);
	return 0;	
}

int parseline(int nelements, double* outarray, ifstream *file){	
	string line;
	for(int i=0;i<nelements; i++){
		getline(*file, line, ',');
		outarray[i] = atof(line.c_str());
		cout << outarray[i] << endl;
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

