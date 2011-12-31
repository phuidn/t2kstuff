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
#include <TGlobalBaseObjects.hxx>
#include <TGRooTrackerVtx.hxx>
#include <TTruthVerticesModule.hxx>
#include <TTrueVertex.hxx>
#include <TTree.h>
#define ABS(x) (x>0?x:-x)

using namespace std;
void SetupROOT();
//---------------------------------------------------------------------------//
//Main Method
//---------------------------------------------------------------------------//
int main(int argc, char** argv)
{	

	// Set up ROOT as we require.
	SetupROOT();
	// Get list of files to run over. 
	TString fileName("/storage/epp2/phseaj/exercise/basket_2010b.list");
	std::ifstream inputFile(fileName.Data(), ios::in);

	// Declare a TChain for the TGlobalPID module
	TChain *gRecon = new TChain("ReconDir/Global");
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
//				gGenVtx->Add(curFileName.c_str());
			}
		}
	}

	std::cout << "Got input file(s)." << std::endl;

	//Setup access to the Recon tree
	int NPIDs(0);  // This variable counts the number of particles per event
	// Declare a TClonesArray to hold objects of type TGlobalPID
 	TClonesArray *globalPIDs = new TClonesArray("ND::TGlobalReconModule::TGlobalPID",50);
    // Associate the right branch in the TTree to the right local variable
	gRecon->SetBranchAddress("NPIDs",&NPIDs);
    gRecon->SetBranchAddress("PIDs",&globalPIDs);
	//check that truthdir and recon have the same number of entries
	// Loop over the entries in the TChain.

	//========================================================
	//			Declare Graphs n stuff here
	//========================================================

	//adding tclones arrays for use with detectors

	TFile treefile("../newtree.root", "RECREATE", "A test tree"); //create file for new tree (maybe)
	TTree *tree = new TTree("newtree", "a new tree");
	
	//Variables which could be put in the new tree
	UInt_t Detectors;
	UInt_t Status;
	Double_t Quality;
	Int_t NHits;
	Bool_t IsForward;
	TLorentzVector FrontPosition, BackPosition, FrontMomentum, BackMomentum;
	TVector3 FrontDirection, BackDirection;
	ND::TTrueParticle TrueParticle; //from here on aren't added to the tree yet
	Int_t NTPCs;
	TClonesArray TPC;

	Int_t NFGDs;
	TClonesArray FGD;

	Int_t NECALs;
	TClonesArray ECAL;

	Int_t NP0Ds;
	TClonesArray P0D;

	Int_t NSMRDs;
	TClonesArray SMRD;
	
	// add them  to the tree
	tree->Branch("Detectors", &Detectors);
	tree->Branch("Status", &Status);
	tree->Branch("Quality", &Quality);
	tree->Branch("NHits", &NHits);
	tree->Branch("IsForward", &IsForward);
	tree->Branch("FrontPosition","TLorentzVector", &FrontPosition);
	tree->Branch("BackPosition","TLorentzVector", &BackPosition);
	tree->Branch("FrontMomentum","TLorentzVector", &FrontMomentum);
	tree->Branch("BackMomentum","TLorentzVector", &BackMomentum);
	tree->Branch("FrontDirection","TVector3", &FrontDirection);
	tree->Branch("BackDirection","TVector3", &BackDirection);
	tree->Branch("TrueParticle", "TTrueParticle", &TrueParticle);
/*	tree->Branch("NTPCs", &NTPCs);	//it doesn't like these, it might be best to add in individual components of them that
	tree->Branch("NFGDs", &NFGDs);	//we want rather than the whole things.
	tree->Branch("NECALs", &NECALs);
	tree->Branch("NP0Ds", &NP0Ds);
	tree->Branch("NSMRDs", &NSMRDs);
	tree->Branch("TPC", &TPC);
	tree->Branch("FGD", &FGD);
	tree->Branch("ECAL", &ECAL);
	tree->Branch("P0D", &P0D);
	tree->Branch("SMRD", &SMRD);*/
	//adding a 2d graph general purpose, change titles each time!
	Int_t total(0), accepted(0);
	//========================================================
	//	end		Declare Graphs n stuff here
	//========================================================

	// Loop over the entries in the TChain. (only 1/1000 of whole entries atm)
	for(unsigned int i = 0; i < gRecon->GetEntries()/10; ++i) {
		if((i+1)%10000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;
		//display status every 10,000 th entry

	// Get an entry for the Recon tree
		gRecon->GetEntry(i);
		ND::TGlobalReconModule::TGlobalPID *gTrack = NULL;

		//added new loop for truth vertex
		
		for (int j=0; j<NPIDs; j++) {
			total++; //one more total event
			// Get a specific track from the TClonesArray
			gTrack = (ND::TGlobalReconModule::TGlobalPID*)globalPIDs->At(j);
			//get position lorentz vector
			TLorentzVector vec = gTrack->FrontPosition;
			if(ABS(vec.X())<832.2 && ABS(vec.Y()-55)<832.2 && ((vec.Z()>123.45&&vec.Z()<446.95)||(vec.Z()>1481.45&&vec.Z()<1807.95))){	//is it in one of the FGDs?
				unsigned long det;
				accepted++; //one more accepted event
				Detectors = gTrack->Detectors;
				Quality = gTrack->Quality;
				NHits = gTrack->NHits;
				Status = gTrack->Status;
				FrontPosition = gTrack->FrontPosition;
				BackPosition = gTrack->BackPosition;
				FrontDirection = gTrack->FrontDirection;
				BackDirection = gTrack->BackDirection;
				FrontMomentum = gTrack->FrontMomentum;
				BackMomentum = gTrack->BackMomentum;
				TrueParticle = gTrack->TrueParticle;
/*				NTPCs = gTrack->NTPCs;
				NFGDs = gTrack->NFGDs;
				NECALs = gTrack->NECALs;
				NP0Ds = gTrack->NP0Ds;
				NSMRDs = gTrack->NSMRDs;
				TPC = *gTrack->TPC;
				FGD = *gTrack->FGD;
				ECAL = *gTrack->ECAL;
				P0D = *gTrack->P0D;
				SMRD = *gTrack->SMRD; */
				tree->Fill();
			}
		}
	} // End loop over events

	cout<<"ratio of accepted events = " << (double)accepted/(double)total << endl;
	tree->Print();
	tree->Write();
	treefile.Write();
	treefile.Close();
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
