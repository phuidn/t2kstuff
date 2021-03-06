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
#include <TTrackerECALReconModule.hxx>
#include <TTrueVertex.hxx>
#include <TTree.h>
#include <TBranch.h>
#include <THStack.h>
#include <TColor.h>
#include "cuts.h"
#define ABS(x) (x>0?x:-x)

using namespace std;
void SetupROOT();

//---------------------------------------------------------------------------//
//Main Method
//---------------------------------------------------------------------------//
int main(int argc, char** argv)
{	

	//Making canvas and application - needed for standalone programs
	TApplication *App = new TApplication("Application",(Int_t*)&argc, argv);
	TCanvas *canvas = new TCanvas("canvas", "canvas", 640, 640);
	// Set up ROOT as we require.
	SetupROOT();
	// Get list of files to run over. - using basket to save time
	TString fileName("/storage/epp2/phseaj/exercise/basket_2010b.list");
	//TString fileName("../../../magnetfiles");
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
	//	for(int i=0;i<3;i++) { getline(inputFile,curFileName);
		while(getline(inputFile,curFileName)){
				gRecon->Add(curFileName.c_str());
		}
	}

	std::cout << "Got input file(s)." << std::endl;

	//Setup access to the Recon tree
	int NPIDs(0);  // This variable counts the number of particles per event
	Int_t EventID(0);
	Int_t NP0DClusters(0);
	Int_t NECalReconObject(0);//within ECal object!
	// Declare a TClonesArray to hold objects of type TGlobalPID
 	TClonesArray *globalPIDs = new TClonesArray("ND::TGlobalReconModule::TGlobalPID",50);
	//used to be ND::TTrackerECALReconModule::TECALReconObject
    // Associate the right branch in the TTree to the right local variable
	gRecon->SetBranchAddress("NPIDs",&NPIDs);
    gRecon->SetBranchAddress("PIDs",&globalPIDs);
	gRecon->SetBranchAddress("EventID", &EventID);
	//========================================================
	//			Declare Graphs n stuff here

	//Matrix one
	Float_t bins[] = {0,0.15, 0.28, 0.40, 0.70, 4};
	TH2D *hist = new TH2D("hist","Recon vs Truth Proton Momenta",5,0,1.2, 5,0,1.2);
	//Both stacked
	THStack hs("hs","Recon and truth proton momenta for NCQES");
	////need seperate hists for adding to a stack
	TH1D *truthhist = new TH1D("truthhist","Generic Title",5, bins);
	truthhist->SetFillColor(kRed);
	TH1D *reconhist = new TH1D("reconhist","Generic Title",5, bins);
	reconhist->SetFillColor(kBlue);

	//setting palette
	Double_t Red[3]    = { 1.00, 0.00, 0.00};
	Double_t Green[3]  = { 0.00, 1.00, 0.00};
	Double_t Blue[3]   = { 1.00, 0.00, 1.00};
	Double_t Length[3] = { 0.00, 0.50, 1.00 };
	Int_t nb=50;
	TColor itsCOLOUR;
	itsCOLOUR.CreateGradientColorTable(3,Length,Red,Green,Blue,nb);

	//========================================================

	//adding tclones arrays for use with detectors

	cout<<"got inputs"<<endl;
	//TFile treefile("../../../tree/testtree.root", "RECREATE", "A test tree"); //create file for new tree
	TTree *tree = new TTree("newtree", "a new tree");
	
	//Variables which could be put in the new tree
	UInt_t Detectors;
	UInt_t Status;
	Double_t Quality;
	Int_t NHits;
	Bool_t IsForward;
	Double_t FrontMomentum, BackMomentum;
	TLorentzVector FrontPosition, BackPosition;
	TVector3 FrontDirection, BackDirection;
	ND::TTrueParticle TrueParticle; //from here on aren't added to the tree yet
	UInt_t NNCES(0);
	UInt_t NTOT(0);
	UInt_t NTree(0);
	Int_t NTPCs;
	TString FName;
	TObjString FOName;
	TClonesArray TPC("ND::TGlobalReconModule::TTPCObject", 3);

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
//	tree->Branch("NECalReconObject", &NECalReconObject);
	tree->Branch("IsForward", &IsForward);
	tree->Branch("FrontPosition","TLorentzVector", &FrontPosition);
	tree->Branch("BackPosition","TLorentzVector", &BackPosition);
	tree->Branch("FrontMomentum", &FrontMomentum);
	tree->Branch("BackMomentum", &BackMomentum);
	tree->Branch("FrontDirection","TVector3", &FrontDirection);
	tree->Branch("BackDirection","TVector3", &BackDirection);
	tree->Branch("TrueParticle", "TTrueParticle", &TrueParticle);
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
	//counters for finding cut off points
//	unsigned long  c15=0,c16=0,c17=0,c18=0,c19=0,c20=0,c21=0,c22=0,c23=0,c24=0,c25=0,clo=0;

	// Loop over the entries in the TChain.
	cout<<"branched tree"<<endl;
	unsigned int tot = gRecon->GetEntries()/5;
	cout << tot << " events" << endl;
	for(unsigned int i = 0; i < tot/2; ++i) {
		if((i+1)%10000 == 0) std::cout << 100.*(double)(i+1)/(double)tot << "percent complete" << std::endl;
		//display status every 10,000 th entry
		//Get an entry for the Recon tree
		gRecon->GetEntry(i);
		ND::TGlobalReconModule::TGlobalPID *gTrack = NULL;


		for(int j=0; j<NPIDs; j++)
		{
			gTrack = (ND::TGlobalReconModule::TGlobalPID*)globalPIDs->At(j);
			if( gTrack->TrueParticle.Vertex.ReactionCode.find("Weak[NC],QES;",0)==-1)
			{//this is not a QES reaction go to next j value
				continue;
			}
			//If reaches here: this is a QES event
			if( gTrack->TrueParticle.PDG != 2212 )
			{//then not proton - then we dont care: NEXT!
				continue;
			}
			if( gTrack->NTPCs == 0 )
			{//then we cannot reconstruct it probs
				continue;
			}
			Double_t recon_mom = gTrack->FrontMomentum;
			TLorentzVector v = gTrack->TrueParticle.InitMom;
			Double_t truth_mom = sqrt(v.X()*v.X()+v.Y()*v.Y()+v.Z()*v.Z());
			Double_t recon_T = recon_mom * recon_mom / 1000000.;
			Double_t truth_T = truth_mom * truth_mom / 1000000.;
			//std::cout << "PDG = " << gTrack->TrueParticle.PDG << "\t\t" <<  recon_mom << "\t\t" << truth_mom <<  endl;
			hist->Fill(recon_T,truth_T);
		//	truthhist->Fill(truth_T);
		//	reconhist->Fill(recon_T);
		}

	} // End loop over events
	//now stack up graphs
//	hs.Add(truthhist);
//	hs.Add(reconhist);
//	hist->Print("all");
	hist->Draw("LEGO");
	hist->GetXaxis()->SetTitle("Recon Energy");
	hist->GetYaxis()->SetTitle("Truth Energy");
	hist->Draw("LEGO");
//	hs.Draw();
	//printing out number out of ranges
	//calcing total events as well
/*	unsigned long  totalevents = c15+c16+c17+c18+c19+c20+c21+c22+c23+c24+c25+clo;
	cout << "Percentage of events above 1500: " << (double)c15 / (double)totalevents << endl;
	cout << "Percentage of events above 1600: " << (double)c16 / (double)totalevents << endl;
	cout << "Percentage of events above 1700: " << (double)c17 / (double)totalevents << endl;
	cout << "Percentage of events above 1800: " << (double)c18 / (double)totalevents << endl;
	cout << "Percentage of events above 1900: " << (double)c19 / (double)totalevents << endl;
	cout << "Percentage of events above 2000: " << (double)c20 / (double)totalevents << endl;
	cout << "Percentage of events above 2100: " << (double)c21 / (double)totalevents << endl;
	cout << "Percentage of events above 2200: " << (double)c22 / (double)totalevents << endl;
	cout << "Percentage of events above 2300: " << (double)c23 / (double)totalevents << endl;
	cout << "Percentage of events above 2400: " << (double)c24 / (double)totalevents << endl;
	cout << "Percentage of events above 2500: " << (double)c25 / (double)totalevents << endl;*/
	//reconhist->Draw();
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



