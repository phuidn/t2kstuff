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
#include <TTruthVerticesModule.hxx>
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
			gRecon->Add(curFileName.c_str());
			gGenVtx->Add(curFileName.c_str());
		}
	}

	std::cout << "Got input file(s)." << std::endl;

	//Setup access to the Recon tree
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

	//========================================================
	//			Declare Graphs n stuff here
	//========================================================

	//adding tclones arrays for use with detectors
	Int_t NTPCs;
	TClonesArray *TPC;

	Int_t NFDGs;
	TClonesArray *FDG;

	Int_t NECALs;
	TClonesArray *ECAL;

	Int_t NPODs;
	TClonesArray *POD;

	Int_t NSMRDs;
	TClonesArray *SMRD;

	//========================================================
	//	end		Declare Graphs n stuff here
	//========================================================

	// Loop over the entries in the TChain. (only 1/1000 of whole entries atm)
	for(unsigned int i = 0; i < gRecon->GetEntries()/1000; ++i) {
		if((i+1)%10000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;
		//display status every 10,000 th entry

	// Get an entry for the Recon tree
		gRecon->GetEntry(i);
		gGenVtx->GetEntry(i);
		ND::TGlobalReconModule::TGlobalPID *gTrack = NULL;
		for (int j=0; j<NPIDs; j++) {
			// Get a specific track from the TClonesArray
			gTrack = (ND::TGlobalReconModule::TGlobalPID*)globalPIDs->At(j);

			TClonesArray *TPCObjects = new TClonesArray("ND::TGlobalReconModule::TTPCObject",gTrack->NTPCs);
			ND::TGlobalReconModule::TObject *tpcTrack = NULL;
			for ( int k = 0 ; k < gTrack->NTPCs; k++) {
				tpcTrack = (ND::TGlobalReconModule::TObject*) TPCObjects->At(k);
				//now we can access  variables through tpcTrack->PullEle for example
			}
		}
		//added new loop for truth vertex, may want above the recon?
		gGenVtx->GetEntry(i);
		ND::TTruthVerticesModule::TTruthVertex* vtx = NULL;
		for( int j = 0; j < NVtxFGD1; j++) { 
				//get vertex
				vtx = (ND::TTruthVerticesModule::TTruthVertex*)VtxFGD1->At(j);
				//get vertex local position vector
				TLorentzVector vec = vtx->Vertex;
				//get x position
				float vtxX=vec.X();
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
