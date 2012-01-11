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
#include <THStack.h>
#include <cuts.h>
#define ABS(x) (x>0?x:-x)

using namespace std;
void SetupROOT();

//---------------------------------------------------------------------------//
//Main Method
//---------------------------------------------------------------------------//
int main(int argc, char** argv)
{	

	//Making canvas and application
	TApplication *App = new TApplication("Application",(Int_t*)&argc, argv);
	TCanvas *canvas = new TCanvas("canvas", "canvas", 640, 640);
	// Set up ROOT as we require.
	SetupROOT();


	cout<<"opening tree"<<endl;
	// Open the TTree we made
	TFile *treefile = new TFile("../../../tree/newtree.root");
	TTree *tree = (TTree*) treefile->Get("newtree");

	//Variables to get from the tree
	UInt_t Detectors;
	UInt_t Status;
	Double_t Quality;
	Int_t NHits;
	Bool_t IsForward;
	TLorentzVector *FrontPosition(0), *BackPosition(0), *FrontMomentum(0), *BackMomentum(0);
	TVector3 *FrontDirection(0), *BackDirection(0);
	ND::TTrueParticle *TrueParticle(0);

	/*Int_t *NTPCs;
	TClonesArray *TPC;

	Int_t *NFGDs;
	TClonesArray *FGD;

	Int_t *NECALs;
	TClonesArray *ECAL;

	Int_t *NP0Ds;
	TClonesArray *P0D;

	Int_t *NSMRDs;
	TClonesArray *SMRD;*/
	
	// add them  to the tree
	cout<<"setting tree branch addresses to variables"<<endl;
	tree->SetBranchAddress("Detectors", &Detectors);
	tree->SetBranchAddress("Status", &Status);
	tree->SetBranchAddress("Quality", &Quality);
	tree->SetBranchAddress("NHits", &NHits);
	tree->SetBranchAddress("IsForward", &IsForward);
	tree->SetBranchAddress("FrontPosition", &FrontPosition);
	tree->SetBranchAddress("BackPosition", &BackPosition);
	tree->SetBranchAddress("FrontMomentum", &FrontMomentum);
	tree->SetBranchAddress("BackMomentum", &BackMomentum);
	tree->SetBranchAddress("FrontDirection", &FrontDirection);
	tree->SetBranchAddress("BackDirection", &BackDirection);
	tree->SetBranchAddress("TrueParticle", &TrueParticle);
/*	tree->SetBranchAddress("NTPCs", &NTPCs);	//it doesn't like these, it might be best to add in individual components of
	tree->SetBranchAddress("NFGDs", &NFGDs);	//them that we want rather than the whole things.
	tree->SetBranchAddress("NECALs", &NECALs);
	tree->SetBranchAddress("NP0Ds", &NP0Ds);
	tree->SetBranchAddress("NSMRDs", &NSMRDs);
	tree->SetBranchAddress("TPC", &TPC);
	tree->SetBranchAddress("FGD", &FGD);
	tree->SetBranchAddress("ECAL", &ECAL);
	tree->SetBranchAddress("P0D", &P0D);
	tree->SetBranchAddress("SMRD", &SMRD);*/
	//adding a 2d graph general purpose, change titles each time!
	Int_t accepted(0), acceptedNCES(0), acceptedNoise(0);

	//ADding graphhs
	// change title for specific stuff
	THStack hs("hs","Testing a TStack");
	//need seperate hists for adding to a stack
	TH1D *hist1 = new TH1D("hist1","Momentum of QES reactions",200,-1500,0);
	hist1->SetFillColor(kRed);
	TH1D *hist2 = new TH1D("hist2","Momentum of non-QES reactions",200,-1500,0);
	hist2->SetFillColor(kBlue);

	TH1D *hist3 = new TH1D("hist3","Momentum of QES reactions",200,-1500,0);
	hist3->SetFillColor(kGreen);
	TH1D *hist4 = new TH1D("hist4","Momentum of QES reactions",200,-1500,0);
	hist4->SetFillColor(kYellow);


	//========================================================
	//	end		Declare Graphs n stuff here
	//========================================================

	// Loop over the entries in the TTree
	cout<<"looping over " <<tree->GetEntries()<<" events"<<endl;
	for(unsigned int i = 0; i < tree->GetEntries(); ++i) {
		if((i+1)%1000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;
		//display status every 1,000 th entry
		// Get an entry for the tree
		tree->GetEntry(i);
		int keep(1); //is the particle going to be kept
		//cout<<TrueParticle->Vertex.ReactionCode<<endl;
		//apply cuts here

		if(keep){
			accepted++;
			if(TrueParticle->Vertex.ReactionCode.find("Weak[NC],QES;",0)!=-1)
			{
				acceptedNCES++;
				//add to QES graph
				hist1->Fill( FrontMomentum->Mag() );
			}
			else if(TrueParticle->Vertex.ReactionCode.find(",RES;",0)!=-1)
			{
				acceptedNoise++;
				hist2->Fill( FrontMomentum->Mag() );
			}
			else if(TrueParticle->Vertex.ReactionCode.find(",DIS;",0)!=-1)
			{
				acceptedNoise++;
				hist3->Fill( FrontMomentum->Mag() );
			}
			else
			{
				acceptedNoise++;
				hist4->Fill( FrontMomentum->Mag() );
			}
		}	
	} // End loop over events

	cout<<"signal to noise (needs changing to something better) = " << (double)acceptedNCES/(double)acceptedNoise << endl;

	//add QES and Non-QES to TStack
	hs.Add(hist1);
	hs.Add(hist2);
	hs.Add(hist3);
	hs.Add(hist4);
	//draw stacked hist
	cout<<"Drawing hist"<<endl;
	hs.Draw();

	//display the canvas!
	cout<<"Running app"<<endl;
	App->Run();
	cout<<"Ran app"<<endl;

	treefile->Close();
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

