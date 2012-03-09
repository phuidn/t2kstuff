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
#include <TBeamSummaryDataModule.hxx>
#include <TGRooTrackerVtx.hxx>
#include <TTruthVerticesModule.hxx>
#include <TTrackerECALReconModule.hxx>
#include <TTrueVertex.hxx>
#include <TTree.h>
#include <TBranch.h>
#include "cuts.h"
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
	TString fileName("../../../realdatafiles.txt");
	std::ifstream inputFile(fileName.Data(), ios::in);

	// Declare a TChain for the TGlobalPID module
	TChain *gRecon = new TChain("ReconDir/Global");
	TChain *P0Dinfo = new TChain("ReconDir/P0D");
	TChain *ECalInfo = new TChain("ReconDir/TrackerECal");
	//NEW! - for real data!
	TChain *fBeamSummary = new TChain("HeaderDir/BeamSummaryData");
	TChain *fDataQuality = new TChain("HeaderDir/BasicDataQuality");

	
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
		//for(int i=0;i<10;i++) { getline(inputFile,curFileName);
		while(getline(inputFile,curFileName)){
				gRecon->Add(curFileName.c_str());
				P0Dinfo->Add(curFileName.c_str());
				ECalInfo->Add(curFileName.c_str());
				//NEW!
				fBeamSummary->Add(curFileName.c_str());
				fDataQuality->Add(curFileName.c_str());
		}
	}

	std::cout << "Got input file(s)." << std::endl;

	//Setup access to the Recon tree
	int NPIDs(0);  // This variable counts the number of particles per event
	int nd280DQFlag(0);
	Int_t EventID(0);
	Int_t NP0DClusters(0);
	Int_t NECalReconObject(0);//within ECal object!
	// Declare a TClonesArray to hold objects of type TGlobalPID
 	TClonesArray *globalPIDs = new TClonesArray("ND::TGlobalReconModule::TGlobalPID",50);
	TClonesArray *ECalReconObject = new TClonesArray("ND::TTrackerECALReconModule::TECALReconObject",50);//REMOVE?
	//NEW!
	TClonesArray *bsdObjects = new TClonesArray("ND::TBeamSummaryDataModule::TBeamSummaryData",20);
	//used to be ND::TTrackerECALReconModule::TECALReconObject
    // Associate the right branch in the TTree to the right local variable
	gRecon->SetBranchAddress("NPIDs",&NPIDs);
    gRecon->SetBranchAddress("PIDs",&globalPIDs);
	gRecon->SetBranchAddress("EventID", &EventID);
	P0Dinfo->SetBranchAddress("NClusters", &NP0DClusters);
	ECalInfo->SetBranchAddress("NReconObject", &NECalReconObject);
	ECalInfo->SetBranchAddress("ReconObject",&ECalReconObject);
	//NEW!
	fBeamSummary->SetBranchAddress("BeamSummaryData",&bsdObjects);
	fDataQuality->SetBranchAddress("ND280OffFlag",&nd280DQFlag);
	//========================================================
	//			Declare Graphs n stuff here
	//========================================================

	//adding tclones arrays for use with detectors

	cout<<"got inputs"<<endl;
//	TFile treefile("../../../tree/evetree.root", "RECREATE", "A test tree"); //create file for new tree
//	TFile treefile("../../../tree/magnet7xwindow.root", "RECREATE", "A test tree"); //create file for new tree
	TFile treefile("../../../tree/realdatafull.root","RECREATE","Real Data");
	TTree *tree = new TTree("newtree", "Real Data");
	
	//Variables which could be put in the new tree
	UInt_t Detectors;
	UInt_t Status;
	Double_t Quality, Length, Width;
	Int_t NHits;
	Bool_t IsForward;
	Double_t FrontMomentum, BackMomentum;
	TLorentzVector FrontPosition, BackPosition;
	TVector3 FrontDirection, BackDirection;
	UInt_t NNCES(0);
	UInt_t NTOT(0);
	UInt_t NTree(0);
	Int_t NTPCs;
	TString FName;
	TObjString FOName;
	TClonesArray TPC("ND::TGlobalReconModule::TTPCObject", 3);
	TLorentzVector ECalPosition, ECalBackPosition;
	//NEW! - declarations
	Double_t fPOT(0);
	UInt_t fTriggerTime(0);
	int timeRegime;//0=MC , 1=2010a, 2=2010bpt1, 3=2010bpt2 

	Int_t NFGDs;
	TClonesArray FGD("ND::TGlobalReconModule::TFGDObject", 2);

	Int_t NECALs;
	TClonesArray ECAL("ND::TGlobalReconModule::TECALObject", 3);

	Int_t NP0Ds;
	TClonesArray P0D("ND::TGlobalReconModule::TP0DObject", 2);

	Int_t NSMRDs;
	TClonesArray SMRD("ND::TGlobalReconModule::TSMRDObject", 3);
	
	cout<<"declared things"<<endl;
	// add them  to the tree
	tree->Branch("FOName",&FOName);
	tree->Branch("EventID", &EventID);
	tree->Branch("Detectors", &Detectors);
	tree->Branch("Status", &Status);
	tree->Branch("Quality", &Quality);
	tree->Branch("NHits", &NHits);
	tree->Branch("IsForward", &IsForward);
	tree->Branch("Length", &Length);
	tree->Branch("Width", &Width);
	tree->Branch("FrontPosition","TLorentzVector", &FrontPosition);
	tree->Branch("BackPosition","TLorentzVector", &BackPosition);
	tree->Branch("FrontMomentum", &FrontMomentum);
	tree->Branch("BackMomentum", &BackMomentum);
	tree->Branch("FrontDirection","TVector3", &FrontDirection);
	tree->Branch("BackDirection","TVector3", &BackDirection);
	tree->Branch("NTPCs", &NTPCs);	
	tree->Branch("NFGDs", &NFGDs);	
	tree->Branch("NECALs", &NECALs);
	tree->Branch("NP0Ds", &NP0Ds);
	tree->Branch("NSMRDs", &NSMRDs);
	tree->Branch("TPC", &TPC);
	tree->Branch("FGD", &FGD);
	tree->Branch("ECAL", &ECAL);
	tree->Branch("P0D", &P0D);
	tree->Branch("SMRD", &SMRD);
//	tree->Branch("ECalBackPosition","TLorentzVector", &ECalBackPosition);
//	tree->Branch("ECalPosition","TLorentzVector", &ECalBackPosition);
	tree->Branch("TimeRegime",&timeRegime);
	//========================================================
	//	end		Declare Graphs n stuff here
	//========================================================

	// Loop over the entries in the TChain.
	cout<<"branched tree"<<endl;
	unsigned int tot = gRecon->GetEntries();
	cout <<"Total of "<<(int)gRecon->GetEntries()<<" entries"<<endl;
	cout <<"Looping over "<< tot << " events" << endl;
	int bunches[8] = {0,0,0,0,0,0,0,0},  //array to check number of hits per time bunch
		ecalhits[8] = {0,0,0,0,0,0,0,0};
	for(unsigned int i = 0; i < tot; ++i) {
		if((i+1)%10000 == 0)
		{
			std::cout << 100.*(double)(i+1)/(double)tot << " %% complete" << std::endl;
			std::cout << "fPOT = " << fPOT <<std::endl;
		}
		//display status every 10,000 th entry
		memset(bunches, 0, 8*sizeof(int));
		memset(ecalhits, 0, 8*sizeof(int));
		//Get an entry for the Recon tree
		gRecon->GetEntry(i);
		P0Dinfo->GetEntry(i);
		ECalInfo->GetEntry(i);
		fBeamSummary->GetEntry(i);
		fDataQuality->GetEntry(i);

		ND::TGlobalReconModule::TGlobalPID *gTrack = NULL;
		//ND::TTrackerECALReconModule::TECALReconTrack *eRecon = NULL;
		ND::TTrackerECALReconModule::TECALReconObject *eObject = NULL;
		//NEW!
		ND::TBeamSummaryDataModule::TBeamSummaryData *bsdObj=NULL;
	
		//NEW! - get event specific BeamSummary data
		bsdObj = (ND::TBeamSummaryDataModule::TBeamSummaryData*)(*bsdObjects)[0];
		if(bsdObj==NULL) cout<<"bsdObj is NULL"<<endl;
	    //NEW! - get POT (assuming only want total fPOT)
	    fPOT += bsdObj->CT5ProtonsPerSpill;
	    //NEW! - get Trigger time! (add to tree!?)
	    fTriggerTime = bsdObj->GPS1TriggerTime;
		if(fTriggerTime<1285934400) timeRegime=1;//2010a 
		else if(fTriggerTime<1294000000) timeRegime=2;//2010b pt1
		else timeRegime=3;//2010b pt2

		for (int j=0; j<NPIDs; j++){	//loop once to check number of PIDs in each bunch in a spill
			gTrack = (ND::TGlobalReconModule::TGlobalPID*)globalPIDs->At(j);
			int bunch = inTimeBunch(&gTrack->FrontPosition,timeRegime,300.);
			if(bunch != -1)
				bunches[bunch]++;
		}

		
		for (int j=0; j<NPIDs; j++) {	//loop again to perform cuts
			//Get a specific track from the TClonesArray
			gTrack = (ND::TGlobalReconModule::TGlobalPID*)globalPIDs->At(j);
			NTOT++;		//one more total event
			TLorentzVector vec = gTrack->FrontPosition;
			FrontMomentum = gTrack->FrontMomentum;
			int bunch = inTimeBunch(&vec,timeRegime, 300.);
			//NEW! - cut if detector was bad!
			if(nd280DQFlag!=0)
			{
				continue;
			}
			//NEW! - cut with trigger time
			if( (inFGD1(&vec) || inFGD2(&vec)) && inBeamTime(&vec,timeRegime) && FrontMomentum != 0. ){ //cut only lets through particles which start in an FGD
				//Real data has no true particle!
//				if(gTrack->TrueParticle.Vertex.ReactionCode.find("Weak[NC],QES;",0)!=-1)
//					NNCES++;		//one more qes event
				if(bunch==-1 || bunches[bunch]>1) //cut allows through particles with one hit per bunch 
					continue;
				FName = TString(gRecon->GetFile()->GetName());
				FOName.SetString(FName);
				Detectors = gTrack->Detectors;	
				Quality = gTrack->Quality;
				NHits = gTrack->NHits;
				Status = gTrack->Status;
				Width = gTrack->Width;
				Length = gTrack->Length;
				FrontPosition = gTrack->FrontPosition;
				BackPosition = gTrack->BackPosition;
				FrontDirection = gTrack->FrontDirection;
				BackDirection = gTrack->BackDirection;
				FrontMomentum = gTrack->FrontMomentum;
				BackMomentum = gTrack->BackMomentum;
				NTPCs = gTrack->NTPCs;
				NFGDs = gTrack->NFGDs;
				NECALs = gTrack->NECALs;
				NP0Ds = gTrack->NP0Ds;
				NSMRDs = gTrack->NSMRDs;
				TPC = *gTrack->TPC;
				FGD = *gTrack->FGD;
				ECAL = *gTrack->ECAL;
				P0D = *gTrack->P0D;
				SMRD = *gTrack->SMRD; 
				NTree++; //one more in the tree (for diagnostic purposes to see what root is doing with the trees)
				//ECalBackPosition = eRecon->Track.BackPosition;
				//cout << eRecon
				tree->Fill();
			}
		}
	} // End loop over events
	cout<<"filled tree"<<endl;
	//add two more branches for total QES and all particles and fill them once
	TBranch* qesbranch = tree->Branch("NNCES", &NNCES);
	TBranch* totbranch = tree->Branch("NTOT", &NTOT);
	TBranch* potbranch = tree->Branch("POT",&fPOT);
	qesbranch->Fill();
	totbranch->Fill();
	potbranch->Fill();
	treefile.Write();	//write tree
	treefile.Close();
	
	cout<<"NTree = "<<NTree<<endl;
	std::cout << "final fPOT = " << fPOT <<std::endl;

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



