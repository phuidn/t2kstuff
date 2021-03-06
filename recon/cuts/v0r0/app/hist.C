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
#include <TLegend.h>
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
	double avProPull;


	// Open the TTree we made 
	//NOTE: MUST BE 3 DIRECTORIES ABOVE THE "recon" directory!!! (relative path)
	TFile *treefile = new TFile("../../../tree/magnetfullwindow.root");
	TTree *tree = (TTree*) treefile->Get("newtree");

	//Variables to get from the tree
	UInt_t Detectors;
	UInt_t Status;
	Double_t Quality;
	Int_t NHits;
	Bool_t IsForward;
	Int_t NP0DClusters;
	TLorentzVector *FrontPosition(0), *BackPosition(0);
	TVector3 *FrontDirection(0), *BackDirection(0);
	ND::TTrueParticle *TrueParticle(0);
	Double_t FrontMomentum,BackMomentum;
	Int_t EventID(0);
	TObjString *FOName(0);

	Int_t NTPCs;
	TClonesArray *TPC = new TClonesArray("ND::TGlobalReconModule::TTPCObject",3);
	Int_t NFGDs;
	TClonesArray *FGD = new TClonesArray("ND::TGlobalReconModule::TFGDObject",2);
	Int_t NECALs;
	TClonesArray *ECAL = new TClonesArray("ND::TGlobalReconModule::TECALObject",3);
	Int_t NP0Ds;
	TClonesArray *P0D = new TClonesArray("ND::TGlobalReconModule::TP0DObject",2);
	Int_t NSMRDs;
	TClonesArray *SMRD = new TClonesArray("ND::TGlobalReconModule::TSMRDObject",3);

	// add them  to the tree
	tree->SetBranchAddress("Detectors", &Detectors);
	tree->SetBranchAddress("Status", &Status);
	tree->SetBranchAddress("FOName",&FOName);
	tree->SetBranchAddress("EventID",&EventID);
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
	tree->SetBranchAddress("NTPCs", &NTPCs);
	tree->SetBranchAddress("NFGDs", &NFGDs);
	tree->SetBranchAddress("NECALs", &NECALs);
	tree->SetBranchAddress("NP0Ds", &NP0Ds);
	tree->SetBranchAddress("NSMRDs", &NSMRDs);
  	tree->SetBranchAddress("TPC", &TPC);
	tree->SetBranchAddress("FGD", &FGD);
	tree->SetBranchAddress("ECAL", &ECAL);
	tree->SetBranchAddress("P0D", &P0D);
	tree->SetBranchAddress("NP0DClusters", &NP0DClusters);
	tree->SetBranchAddress("SMRD", &SMRD);

	//Counters
	Int_t accepted(0), acceptedNCES(0), acceptedNoise(0);

	//Adding graphhs
	// change title for specific stuff
	THStack hs("hs","Muon Pull for Different Particle Types");
	//need seperate hists for adding to a stack
	TH1D *hist1 = new TH1D("hist1","Generic Title",50,-5, 10);
	hist1->SetFillColor(kRed);
	TH1D *hist2 = new TH1D("hist2","Generic Title",50,-5, 10);
	hist2->SetFillColor(kBlue);
	TH1D *hist3 = new TH1D("hist3","Generic Title",50,-5, 10);
	hist3->SetFillColor(kMagenta);
	TH1D *hist4 = new TH1D("hist4","Generic Title",50,-5, 10);
	hist4->SetFillColor(kCyan);
	TH1D *hist5 = new TH1D("hist5","Generic Title",50,-5, 10);
	hist5->SetFillColor(kGreen);


	//========================================================
	//	end		Declare Graphs n stuff here
	//========================================================

	// Loop over the entries in the TTree
	for(unsigned int i = 0; i < tree->GetEntries(); ++i) {
		//display status every 1,000 th entry
		// Get an entry for the tree
		tree->GetEntry(i);
		int keep=1;
		//apply cuts here
//	keep = keep? noTPC1(Detectors): 0;
//	keep = keep? noP0Dactivity(Detectors): 0;
//	keep = keep? posCharge(NTPCs, TPC): 0;
//	keep = keep? consecutiveDetectors(Detectors):0;
//	keep = keep? muonPull(NTPCs, TPC):0;
		//looping over the number of TPCs particle passed through
		//to get average proton pull
		//looping over the number of TPCs particle passed through
				//to get average proton pull
		int avnum(0);
		for(j=0,avProPull=0;j<NTPCs;j++)
		{
			if(((ND::TGlobalReconModule::TTPCObject*)TPC->At(j))->NHits > 18){
				avnum++;
				avProPull += ((ND::TGlobalReconModule::TTPCObject*)TPC->At(j))->PullMuon;
			}
		}
		avProPull/=avnum;
		Double_t fillval = avProPull;
		
		//this is for filtering by particle type
		if(fillval!=0 && keep)
		{
			if(TrueParticle->PDG == 2212)
			{//then its a proton - yay!
				hist1->Fill(fillval);
			}
			else if(TrueParticle->PDG == 13)
			{// pi+
				hist2->Fill(fillval);
			}
			else if(TrueParticle->PDG == -13)
			{// mu+
				hist3->Fill(fillval);
			}
			else if(TrueParticle->PDG == 211)
			{//mu-
				hist4->Fill(fillval);
			}
			else
			{//other
				hist5->Fill(fillval);
			}
		}

//this is for reaction type, commented out as I want particle type
	//	if(keep)
	//	{
	//		accepted++;
	//		if(TrueParticle->Vertex.ReactionCode.find("Weak[NC],QES;",0)!=-1)
	//		{	//add to QES graph
	//			acceptedNCES++;
	//			hist1->Fill( fillval );
	//		//	cout << "NCQES," << FOName->GetString() << "," << EventID << endl;
	//		}
	//		else if(TrueParticle->Vertex.ReactionCode.find(",RES;",0)!=-1)
	//		{	//RES is noise
	//			acceptedNoise++;
	//			hist2->Fill( fillval );
	//		//	cout << "RES," << FOName->GetString() << "," << EventID << endl;
	//		}
	//		else if(TrueParticle->Vertex.ReactionCode.find(",DIS;",0)!=-1)
	//		{	//DIS is noise
	//			acceptedNoise++;
	//			hist3->Fill( fillval );
	//		//	cout << "DIS," << FOName->GetString() << "," << EventID << endl;
	//		}
	//		else if(TrueParticle->Vertex.ReactionCode.find("Weak[CC],QES;",0)!=-1)
	//		{	//CCQES is noise
	//			acceptedNoise++;
	//			hist4->Fill( fillval );
	//		//	cout << "CCQES," << FOName->GetString() << "," << EventID << endl;
	//		}
	//		else
	//		{	//other stuff is noise
	//			acceptedNoise++;
	//			hist5->Fill( fillval );
	//		//	cout << "OTHER," << FOName->GetString() << "," << EventID << endl;
	//		}
	//	}
	} // End loop over events


	//add QES and Non-QES to TStack
	hs.Add(hist1);
	hs.Add(hist2);
	hs.Add(hist3);
	hs.Add(hist4);
	hs.Add(hist5);
	//draw stacked hist
	hs.Draw();
	hs.GetXaxis()->SetTitle("Muon Pull");
	hs.GetYaxis()->SetTitle("Counts");
	
	TLegend *leg = new TLegend(0.1, 0.7, 0.5, 0.9);
	leg->AddEntry(hist1, "Proton", "f"); 
	leg->AddEntry(hist2, "#mu^{+}", "f"); 
	leg->AddEntry(hist3, "#mu^{-}", "f"); 
	leg->AddEntry(hist4, "#pi^{+}", "f"); 
	leg->AddEntry(hist5, "other", "f"); 
	leg->Draw();
	//display the canvas!
	App->Run();

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

