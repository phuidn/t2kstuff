//-----------------------------------------------
//	Current file
//-----------------------------------------------

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
#include <TLorentzVector.h>
#include <TGlobalReconModule.hxx>
#include <TGRooTrackerVtx.hxx>
#include <TTruthVerticesModule.hxx>

#define ABS(x) (x>0?x:-x)

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
	TChain *gGenVtx = new TChain("TruthDir/Vertices");
	// Check if the file exists.
	if (!inputFile.is_open()){
	std::cout << "ERROR: File prod4 files not found!" << std::endl;
		std::cout << " - This file should contain a list of all data files to be processed." << std::endl;
		return 0;
	}
	else{
		std::string curFileName;

		// Add the input files to the TChains.
		//only doing 10 of the basket files, revert to while to do whole run
	//	while(getline(inputFile,curFileName)){
		for(int l = 0; l<10; l++){
			if(getline(inputFile,curFileName)){
				gRecon->Add(curFileName.c_str());
				gGenVtx->Add(curFileName.c_str());
			}
		}
	}

	std::cout << "Got input file(s)." << std::endl;

	//Setup access to the Recon tree
	int NPIDs(0);  // This variable counts the number of particles per event
	int NVtxFGD1(0), NVtxFGD2(0);
        // Declare a TClonesArray to hold objects of type TGlobalPID
 	TClonesArray *globalPIDs = new TClonesArray("ND::TGlobalReconModule::TGlobalPID",50);
	TClonesArray *VtxFGD1 = new TClonesArray("ND::TTruthVerticesModule::TTruthVertex",50);    
	TClonesArray *VtxFGD2 = new TClonesArray("ND::TTruthVerticesModule::TTruthVertex",50);    
    // Associate the right branch in the TTree to the right local variable
	gRecon->SetBranchAddress("NPIDs",&NPIDs);
    gRecon->SetBranchAddress("PIDs",&globalPIDs);
	gGenVtx->SetBranchAddress("VtxFGD1", &VtxFGD1);
	gGenVtx->SetBranchAddress("NVtxFGD1", &NVtxFGD1);
	gGenVtx->SetBranchAddress("VtxFGD2", &VtxFGD2);
	gGenVtx->SetBranchAddress("NVtxFGD2", &NVtxFGD2);
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

	//adding a 2d graph general purpose, change titles each time!
	TH2D *graph1 = new TH2D("graph1","XY positions of NC QES in FGDs", 100, -850.0 , 850.0, 100, -780.0, 890.0);

	//========================================================
	//	end		Declare Graphs n stuff here
	//========================================================

	// Loop over the entries in the TChain. (only 1/1000 of whole entries atm)
	for(unsigned int i = 0; i < gRecon->GetEntries()/10; ++i) {
		if((i+1)%10000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;
		//display status every 10,000 th entry

	// Get an entry for the Recon tree
		gRecon->GetEntry(i);
		gGenVtx->GetEntry(i);
		ND::TGlobalReconModule::TGlobalPID *gTrack = NULL;

		//added new loop for truth vertex
		gGenVtx->GetEntry(i);
		ND::TTruthVerticesModule::TTruthVertex* vtx = NULL;
		for( int j = 0; j < NVtxFGD1; j++) { 
				//get vertex (replace this with True vertex of reconmodule, not truth!
				vtx = (ND::TTruthVerticesModule::TTruthVertex*)VtxFGD1->At(j);
				//get vertex local position vector
				TLorentzVector vec = vtx->Vertex;
				//testing string, filter for neutral current quasi-elastic
				if(vtx->ReactionCode.find("Weak[NC],QES;",0)!=-1){
					if(ABS(vec.X())<832.2 && ABS(vec.Y()-55)<832.2 && ((vec.Z()>123.45&&vec.Z()<446.95)||(vec.Z()>1481.45&&vec.Z()<1807.95))){	//is it in one of the FGDs?
						graph1->Fill(vec.X(),vec.Y());
					}	
				}
				//if ( vtx->ReactionCode->String().Contains("QES") )
				//get x position
				float vtxX=vec.X();
		}

		for (int j=0; j<NPIDs; j++) {
			// Get a specific track from the TClonesArray
			gTrack = (ND::TGlobalReconModule::TGlobalPID*)globalPIDs->At(j);
			cout << gTrack->TrueParticle.Vertex.ReactionCode.c_str() << endl;
			TClonesArray *TPCObjects = new TClonesArray("ND::TGlobalReconModule::TTPCObject",gTrack->NTPCs);
			ND::TGlobalReconModule::TObject *tpcTrack = NULL;
			for ( int k = 0 ; k < gTrack->NTPCs; k++) {
				tpcTrack = (ND::TGlobalReconModule::TObject*) TPCObjects->At(k);
				//now we can access  variables through tpcTrack->PullEle for example
			}
		}

	} // End loop over events

//plotting bits at the end :D
    graph1->GetXaxis()->SetTitle("X");
    graph1->GetYaxis()->SetTitle("Y");
    graph1->Draw();
	App->Run();

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
