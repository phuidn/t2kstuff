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

	//Making canvas and application - needed for standalone programs
	TApplication *App = new TApplication("Application",(Int_t*)&argc, argv);
	TCanvas *canvas = new TCanvas("canvas", "canvas", 640, 640);
	// Set up ROOT as we require.
	SetupROOT();


	Int_t j;
	double avProPull;


	// Open the TTree we made 
	//NOTE: MUST BE 3 DIRECTORIES ABOVE THE "recon" directory!!! (relative path)
	TFile *treefile = new TFile("../../../tree/evetree.root");
	TTree *tree = (TTree*) treefile->Get("newtree");

	//Variables to get from the tree
	UInt_t Detectors;
	UInt_t Status;
	Double_t Quality;
	Int_t NHits;
	Bool_t IsForward;
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
	tree->SetBranchAddress("SMRD", &SMRD);

	//Counters
	Int_t accepted(0), acceptedNCES(0), acceptedNoise(0);

	//Adding graphhs
	// change title for specific stuff
	THStack hs("hs","Frontmom as a function of reaction");
	//need seperate hists for adding to a stack
	TH1D *hist1 = new TH1D("hist1","Generic Title",200,-60, 100);
	hist1->SetFillColor(kRed);
	TH1D *hist2 = new TH1D("hist2","Generic Title",200,-60, 100);
	hist2->SetFillColor(kBlue);
	TH1D *hist3 = new TH1D("hist3","Generic Title",200,-60, 100);
	hist3->SetFillColor(kMagenta);
	TH1D *hist4 = new TH1D("hist4","Generic Title",200,-60, 100);
	hist4->SetFillColor(kCyan);
	TH1D *hist5 = new TH1D("hist5","Generic Title",200,-60, 100);
	hist5->SetFillColor(kGreen);
	//TH1D *hist6 = new TH1D("hist6","Generic Title",200,0,1500);
	//hist6->SetFillColor(kBlack);
	//TH1D *hist7 = new TH1D("hist7","Generic Title",200,0,1500);
	//hist7->SetFillColor(kYellow);
	//TH1D *hist8 = new TH1D("hist8","Generic Title",200,0,1500);
	//hist8->SetFillColor(kPink);


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
		keep = keep? noTPC1(Detectors): 0;
		keep = keep? noP0Dactivity(Detectors): 0;
		keep = keep? posCharge(NTPCs, TPC): 0;
		keep = keep? consecutiveDetectors(Detectors):0;
		keep = keep? muonPull(NTPCs, TPC):0;
		//looping over the number of TPCs particle passed through
		//to get average proton pull
		//looping over the number of TPCs particle passed through
				//to get average proton pull
		for(j=0,avProPull=0;j<NP0Ds;j++)
		{
			avProPull += ((ND::TGlobalReconModule::TTPCObject*)TPC->At(j))->dEdxexpProton/(double)NTPCs;
		}
		cout << avProPull << endl;	
		Double_t fillval = (Double_t)avProPull;
		
		//this is for filtering by particle type
	//	if(avProPull!=0 && keep)
	//	{
	//		if(TrueParticle->PDG == 2212)
	//		{//then its a proton - yay!
	//			hist1->Fill((Double_t)avProPull);
	//		}
	//		else if(TrueParticle->PDG == 211)
	//		{// pi+
	//			hist2->Fill((Double_t)avProPull);
	//		}
	//		else if(TrueParticle->PDG == -211)
	//		{// pi-
	//			hist3->Fill((Double_t)avProPull);
	//		}
	//		else if(TrueParticle->PDG == -11)
	//		{//e+
	//			hist4->Fill((Double_t)avProPull);
	//		}
	//		else if(TrueParticle->PDG == 11)
	//		{//e-
	//			hist5->Fill((Double_t)avProPull);
	//		}
	//		else if(TrueParticle->PDG == 13)
	//		{//mu-
	//			hist6->Fill((Double_t)avProPull);
	//		}
	//		else if(TrueParticle->PDG == -13)
	//		{//mu+
	//			hist7->Fill((Double_t)avProPull);
	//		}
	//		else
	//			hist8->Fill((Double_t)avProPull);
	//	}

//this is for reaction type, commented out as I want particle type
		if(keep)
		{
			accepted++;
			if(TrueParticle->Vertex.ReactionCode.find("Weak[NC],QES;",0)!=-1)
			{	//add to QES graph
				acceptedNCES++;
				hist1->Fill( fillval );
			//	cout << "NCQES," << FOName->GetString() << "," << EventID << endl;
			}
			else if(TrueParticle->Vertex.ReactionCode.find(",RES;",0)!=-1)
			{	//RES is noise
				acceptedNoise++;
				hist2->Fill( fillval );
			//	cout << "RES," << FOName->GetString() << "," << EventID << endl;
			}
			else if(TrueParticle->Vertex.ReactionCode.find(",DIS;",0)!=-1)
			{	//DIS is noise
				acceptedNoise++;
				hist3->Fill( fillval );
			//	cout << "DIS," << FOName->GetString() << "," << EventID << endl;
			}
			else if(TrueParticle->Vertex.ReactionCode.find("Weak[CC],QES;",0)!=-1)
			{	//CCQES is noise
				acceptedNoise++;
				hist4->Fill( fillval );
			//	cout << "CCQES," << FOName->GetString() << "," << EventID << endl;
			}
			else
			{	//other stuff is noise
				acceptedNoise++;
				hist5->Fill( fillval );
			//	cout << "OTHER," << FOName->GetString() << "," << EventID << endl;
			}
		}
	} // End loop over events


	//add QES and Non-QES to TStack
	hs.Add(hist1);
	hs.Add(hist2);
	hs.Add(hist3);
	hs.Add(hist4);
	hs.Add(hist5);
	//hs.Add(hist6);
	//hs.Add(hist7);
	//hs.Add(hist8);
	//draw stacked hist
	hs.Draw();

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

