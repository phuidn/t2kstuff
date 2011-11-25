#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <TSystem.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TF1.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TChain.h>
#include <TClonesArray.h>
#include <TTree.h>
#include <TApplication.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TGlobalReconModule.hxx>
#include <TGRooTrackerVtx.hxx>
using namespace std;
void SetupROOT();
//---------------------------------------------------------------------------//
//Main Method
//---------------------------------------------------------------------------//
int main(int argc, char** argv)
{	
	TApplication *App = new TApplication("Application",(Int_t*)&argc, argv);
	TCanvas *Canvas = new TCanvas("canvas", "Canvas", 640, 640);

	// Set up ROOT as we require.
	SetupROOT();

	// Get list of files to run over. 
//	TString fileName("/home/physics/phuidn/epp/exercise/recon/myND280/v0r0/amd64_linux26/basket_2010b.list");
	TString fileName("/storage/epp2/phseaj/exercise/basket_2010b.list");
	std::ifstream inputFile(fileName.Data(), ios::in);

	// Declare a TChain for the TGlobalPID module
	TChain *gRecon = new TChain("ReconDir/Global");
	TChain *gGenVtx = new TChain("TruthDir/GRooTrackerVtx");
	// Check if the file exists.
	if (!inputFile.is_open()){
	std::cout << "ERROR: File prod4 files not found!" << std::endl;
		std::cout << " - This file should contain a list of all data files to be processed." << std::endl;
		return 0;
	}
	else{
		std::string curFileName;

		// Add the input files to the TChains.
		while(getline(inputFile,curFileName)){
			cout << curFileName.c_str() << endl;
			gRecon->Add(curFileName.c_str());
			gGenVtx->Add(curFileName.c_str());
		}
	}

	std::cout << "Got input file(s)." << std::endl;

	//Setup access to the TruthDir Tree
	int NPIDs(0);  // This variable counts the number of particles per event
	int NVtx(0);
        // Declare a TClonesArray to hold objects of type TGlobalPID
 	TClonesArray *globalPIDs = new TClonesArray("ND::TGlobalReconModule::TGlobalPID",50);
	TClonesArray *VtxArray = new TClonesArray("ND::GRooTrackerVtx",50);    
    // Associate the right branch in the TTree to the right local variable
	gRecon->SetBranchAddress("NPIDs",&NPIDs);
    gRecon->SetBranchAddress("PIDs",&globalPIDs);
	gGenVtx->SetBranchAddress("Vtx", &VtxArray);
	gGenVtx->SetBranchAddress("NVtx", &NVtx);
	//check that truthdir and recon have the same number of entries
	if(gRecon->GetEntries() != gGenVtx->GetEntries()) 
		cout<<"not equal entries, probably wrong"<<endl;
	// Loop over the entries in the TChain.
	for(unsigned int i = 0; i < gRecon->GetEntries()/1000; ++i) {
		if((i+1)%10000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;

	// Get an entry for the TruthDir/GRooTrackVtx tree
		gRecon->GetEntry(i);
		gGenVtx->GetEntry(i);
		ND::TGlobalReconModule::TGlobalPID *gTrack = NULL;
		for (int j=0; j<NPIDs; j++) {
			// Get a specific track from the TClonesArray
			gTrack = (ND::TGlobalReconModule::TGlobalPID*)globalPIDs->At(j);
		}

	} // End loop over events
	return 0;
}

//---------------------------------------------------------------------------//
//										Method to set up ROOT as required.										 //
//---------------------------------------------------------------------------//
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
