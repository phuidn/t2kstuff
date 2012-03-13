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
#include <TLegend.h>
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

	//Making canvas and application - needed for standalone programs
	TApplication *App = new TApplication("Application",(Int_t*)&argc, argv);
	TCanvas *canvas = new TCanvas("canvas", "canvas", 640, 640);
	// Set up ROOT as we require.
	SetupROOT();


	Int_t j;


	// Open the TTree we made 
	//NOTE: MUST BE 3 DIRECTORIES ABOVE THE "recon" directory!!! (relative path)
	TFile *mctreefile = new TFile("../../../tree/magnetfullwindow.root");
	TTree *mctree = (TTree*) mctreefile->Get("newtree");
	TFile *realtreefile = new TFile("../../../tree/realdatafull.root");
	TTree *realtree = (TTree*) realtreefile->Get("newtree");
	//Variables to get from the monte carlo tree
	TLorentzVector *FrontPosition(0), *BackPosition(0);
	TVector3 *FrontDirection(0), *BackDirection(0);
	ND::TTrueParticle *TrueParticle(0);
	Double_t FrontMomentum,BackMomentum,Quality;
	UInt_t NTOT(0);
	Int_t NTPCs(0), NHits(0);
	TClonesArray *TPC = new TClonesArray("ND::TGlobalReconModule::TTPCObject",3);
	Int_t NFGDs;
	TClonesArray *FGD = new TClonesArray("ND::TGlobalReconModule::TFGDObject",2);

	//Things from the real tree
	TLorentzVector *realFrontPosition(0), *realBackPosition(0);
	TVector3 *realFrontDirection(0), *realBackDirection(0);
	Double_t realFrontMomentum,realBackMomentum, realQuality;
	UInt_t realNTOT(0);
	Int_t realNTPCs(0), realNHits(0);
	TClonesArray *realTPC = new TClonesArray("ND::TGlobalReconModule::TTPCObject",3);
	Int_t realNFGDs;
	TClonesArray *realFGD = new TClonesArray("ND::TGlobalReconModule::TFGDObject",2);
	// add them  to the tree
	mctree->SetBranchAddress("FrontPosition", &FrontPosition);
	mctree->SetBranchAddress("BackPosition", &BackPosition);
	mctree->SetBranchAddress("FrontMomentum", &FrontMomentum);
	mctree->SetBranchAddress("BackMomentum", &BackMomentum);
	mctree->SetBranchAddress("FrontDirection", &FrontDirection);
	mctree->SetBranchAddress("BackDirection", &BackDirection);
	mctree->SetBranchAddress("TrueParticle", &TrueParticle);
	mctree->SetBranchAddress("NTPCs", &NTPCs);
	mctree->SetBranchAddress("NFGDs", &NFGDs);
  	mctree->SetBranchAddress("TPC", &TPC);
	mctree->SetBranchAddress("FGD", &FGD);
	mctree->SetBranchAddress("NTOT", &NTOT);
	mctree->SetBranchAddress("NHits", &NHits);
	mctree->SetBranchAddress("Quality", &Quality);

	realtree->SetBranchAddress("FrontPosition", &realFrontPosition);
	realtree->SetBranchAddress("BackPosition", &realBackPosition);
	realtree->SetBranchAddress("FrontMomentum", &realFrontMomentum);
	realtree->SetBranchAddress("BackMomentum", &realBackMomentum);
	realtree->SetBranchAddress("FrontDirection", &realFrontDirection);
	realtree->SetBranchAddress("BackDirection", &realBackDirection);
	realtree->SetBranchAddress("NTPCs", &realNTPCs);
	realtree->SetBranchAddress("NFGDs", &realNFGDs);
  	realtree->SetBranchAddress("TPC", &realTPC);
	realtree->SetBranchAddress("FGD", &realFGD);
	realtree->SetBranchAddress("NTOT", &realNTOT);
	realtree->SetBranchAddress("NHits", &realNHits);
	realtree->SetBranchAddress("Quality", &Quality);
	//Counters
	Double_t mcPOT = 5.e17 * 1554;
	Double_t realPOT = 1.378e20;
	//Adding graphhs
	// change title for specific stuff
	THStack hs("hs","Initial Particle Momentum");
	//need seperate hists for adding to a stack
	TH1D *hist1 = new TH1D("hist1","Generic Title",50,0,1500);
	hist1->SetFillColor(kRed);
	TH1D *hist2 = new TH1D("hist2","Generic Title",50,0,1500);
	hist2->SetFillColor(kBlue);
	TH1D *hist3 = new TH1D("hist3","Generic Title",50,0,1500);
	hist3->SetFillColor(kMagenta);
	TH1D *hist4 = new TH1D("hist4","Generic Title",50,0,1500);
	hist4->SetFillColor(kCyan);
	TH1D *hist5 = new TH1D("hist5","Generic Title",50,0,1500);
	hist5->SetFillColor(kGreen);

	TH1D *realhist=new TH1D("realdata","Real Data",50,0,1500);
	
	//========================================================
	//	end		Declare Graphs n stuff here
	//========================================================

	// Loop over the entries in the TTree
	cout<<"Real Tree loop"<<endl;
	for(unsigned int i = 0; i < realtree->GetEntries();i++){
		realtree->GetEntry(i);
		if(realNTPCs){
			Double_t fillval = ((ND::TGlobalReconModule::TTPCObject*)realTPC->At(0))->FrontMomentum;
			if(fillval==fillval)// && realFrontPosition->Y()>-777 && realFrontPosition->Y()<887)
				realhist->Fill(fillval);
		}
	}
	cout<<"NTOT: " << NTOT << "    realNTOT: "<< realNTOT << endl;
	realhist->Scale(mcPOT/realPOT);
	cout<<"MC Tree Loop"<<endl;
	for(unsigned int i = 0; i < mctree->GetEntries(); ++i) {
		//display status every 1,000 th entry
		// Get an entry for the tree
		mctree->GetEntry(i);
		int keep = NTPCs>0;
		Double_t fillval;
		if (keep)
			fillval = ((ND::TGlobalReconModule::TTPCObject*)TPC->At(0))->FrontMomentum;
//this is for reaction type, commented out as I want particle type
		if(keep && fillval==fillval)// && FrontPosition->Y()>-777 && FrontPosition->Y()<887)
		{
			if(TrueParticle->Vertex.ReactionCode.find("Weak[NC],QES;",0)!=-1)
			{	//add to QES graph
				hist1->Fill( fillval );
			//	cout << "NCQES," << FOName->GetString() << "," << EventID << endl;
			}
			else if(TrueParticle->Vertex.ReactionCode.find(",RES;",0)!=-1)
			{	//RES is noise
				hist3->Fill( fillval );
			//	cout << "RES," << FOName->GetString() << "," << EventID << endl;
			}
			else if(TrueParticle->Vertex.ReactionCode.find(",DIS;",0)!=-1)
			{	//DIS is noise
				hist4->Fill( fillval );
			//	cout << "DIS," << FOName->GetString() << "," << EventID << endl;
			}
			else if(TrueParticle->Vertex.ReactionCode.find("Weak[CC],QES;",0)!=-1)
			{	//CCQES is noise
				hist2->Fill( fillval );
			//	cout << "CCQES," << FOName->GetString() << "," << EventID << endl;
			}
			else
			{	//other stuff is noise
				hist5->Fill( fillval );
			//	cout << "OTHER," << FOName->GetString() << "," << EventID << endl;
			}
		}
	} // End loop over events

	cout<<"HIST section"<<endl;

	//add QES and Non-QES to TStack
	hs.Add(hist1);
	hs.Add(hist2);
	hs.Add(hist3);
	hs.Add(hist4);
	hs.Add(hist5);
	//draw stacked hist
	hs.Draw("");
	hs.GetXaxis()->SetTitle("Initial Momentum / MeV/c");
	hs.GetYaxis()->SetTitle("Counts");
	realhist->SetMarkerStyle(20);
	realhist->Draw("sameE1");
	TLegend *leg = new TLegend(0.1, 0.7, 0.5, 0.9);
	leg->AddEntry(hist1, "NC Elastic", "f"); 
	leg->AddEntry(hist2, "CC Quasi-elastic", "f"); 
	leg->AddEntry(hist3, "Resonance Production", "f"); 
	leg->AddEntry(hist4, "Deep Inelastic", "f"); 
	leg->AddEntry(hist5, "Coherent Scattering", "f"); 
	leg->AddEntry(realhist, "Real Data", "lep");
	leg->Draw();
	//display the canvas!
	App->Run();
	realtreefile->Close();
	mctreefile->Close();
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
//	gSystem->Load("liboaEvent.so");
	gSystem->Load("liboaRuntimeParameters.so");
	gSystem->Load("libMinosDBI.so");
	gSystem->Load("liboaOfflineDatabase.so");
	gSystem->Load("liboaUtility.so");
	gSystem->Load("libsmrdRecon.so");
	gSystem->Load("libBeamData.so");
	gSystem->Load("liboaBeamData.so");
	gSystem->Load("liboaAnalysis.so");
}

