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
#include <classcuts.h>
#include <THStack.h>
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
	cout<<"opening tree"<<endl;
	// Open the TTree we made
	TFile *treefile = new TFile("../../../tree/testtree.root");
	TTree *tree = (TTree*) treefile->Get("newtree");

	//Variables to get from the tree
	UInt_t Detectors(0);
	UInt_t Status(0);
	Double_t Quality,FrontMomentum(0), BackMomentum(0), Length(0), Width(0);
	Int_t NHits(0);
	Bool_t IsForward(0);
	TLorentzVector *FrontPosition(0), *BackPosition(0);
	TVector3 *FrontDirection(0), *BackDirection(0);
	ND::TTrueParticle *TrueParticle(0);
	UInt_t NNCES(0);
	UInt_t NTOT(0);
	TObjString *FOName(0);
	Int_t EventID(0);

	//we dont need these at the moment
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
	cout<<"setting tree branch addresses to variables"<<endl;
	//cout to debug - Tree->Detectors is fine: returns 0
	tree->SetBranchAddress("Detectors", &Detectors);
	tree->SetBranchAddress("FOName",&FOName);
	tree->SetBranchAddress("EventID",&EventID);
	tree->SetBranchAddress("Status", &Status);
	tree->SetBranchAddress("Quality", &Quality);
	tree->SetBranchAddress("NHits", &NHits);
	tree->SetBranchAddress("IsForward", &IsForward);
	tree->SetBranchAddress("Length", &Length);
	tree->SetBranchAddress("Width", &Width);
	tree->SetBranchAddress("FrontPosition", &FrontPosition);
	tree->SetBranchAddress("BackPosition", &BackPosition);
	tree->SetBranchAddress("FrontMomentum", &FrontMomentum);
	tree->SetBranchAddress("BackMomentum", &BackMomentum);
	tree->SetBranchAddress("FrontDirection", &FrontDirection);
	tree->SetBranchAddress("BackDirection", &BackDirection);
	tree->SetBranchAddress("TrueParticle", &TrueParticle);
	//cout to debug - Tree->NNCES doesnt work properly: return value is NOT 0 !
	tree->SetBranchAddress("NNCES", &NNCES);
	tree->SetBranchAddress("NTPCs", &NTPCs);	//it doesn't like these, it might be best to add in individual components of
	tree->SetBranchAddress("NFGDs", &NFGDs);	//them that we want rather than the whole things.
	tree->SetBranchAddress("NECALs", &NECALs);
	tree->SetBranchAddress("NP0Ds", &NP0Ds);
	tree->SetBranchAddress("NSMRDs", &NSMRDs);
	tree->SetBranchAddress("TPC", &TPC);
	tree->SetBranchAddress("FGD", &FGD);
	tree->SetBranchAddress("ECAL", &ECAL);
	tree->SetBranchAddress("P0D", &P0D);
	tree->SetBranchAddress("SMRD", &SMRD);
	UInt_t accepted(0), acceptedNCES(0), acceptedNoise(0), initialNCES(0);
	
	NTOT = tree->GetEntries();
	// Loop over the entries in the TTree
	cout<<"looping over " <<NTOT<<" events"<<endl;
	vector<Cut*> cuts;
	cuts.push_back(new NoTPC1(&Detectors));
	cuts.push_back(new TPCHits(&NTPCs, &TPC, 18, 1000));
	cuts.push_back(new PosCharge(&NTPCs, &TPC));
	cuts.push_back(new ProtonPull(&NTPCs, &TPC));
	cuts.push_back(new MuonPull(&NTPCs, &TPC));
	cuts.push_back(new PionPull(&NTPCs, &TPC));
	cuts.push_back(new TotNHits(&NHits));
	cuts.push_back(new DetectorOrder(&Detectors, &FrontPosition));
	cuts.push_back(new MinMomentum(&FrontMomentum));
	cuts.push_back(new MinMomentum(&BackMomentum, 130));
	cuts.push_back(new CutECALs(&NECALs));
	
	int NCuts = cuts.size();
	int	correctCut[NCuts],
		wrongCut[NCuts];
	memset(correctCut, 0, NCuts*sizeof(int));
	memset(wrongCut, 0, NCuts*sizeof(int));

	//Adding graphhs
	// change title for specific stuff
	THStack hs("hs","Frontmom as a function of reaction");
	//need seperate hists for adding to a stack
	TH1D *hist1 = new TH1D("hist1","Generic Title",100,0,3000);
	hist1->SetFillColor(kRed);
	TH1D *hist2 = new TH1D("hist2","Generic Title",100,0,3000);
	hist2->SetFillColor(kBlue);
	TH1D *hist3 = new TH1D("hist3","Generic Title",100,0,3000);
	hist3->SetFillColor(kMagenta);
	TH1D *hist4 = new TH1D("hist4","Generic Title",100,0,3000);
	hist4->SetFillColor(kCyan);
	TH1D *hist5 = new TH1D("hist5","Generic Title",100,0,3000);
	hist5->SetFillColor(kGreen);
	//TH1D *hist6 = new TH1D("hist6","Generic Title",100,0,15000);
	//hist6->SetFillColor(kBlack);
	//TH1D *hist7 = new TH1D("hist7","Generic Title",100,0,15000);
	//hist7->SetFillColor(kYellow);
	//TH1D *hist8 = new TH1D("hist8","Generic Title",100,0,15000);
	//hist8->SetFillColor(kPink);
	
	for(unsigned int i = 0; i < NTOT; ++i) {
		if((i+1)%1000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;
		//display status every 1,000 th entry
		// Get an entry for the tree
		tree->GetEntry(i);
		int keep(1), j(0), isNCES = TrueParticle->Vertex.ReactionCode.find("Weak[NC],QES;",0)!=-1; //is the particle going to be kept, is it NCES
		initialNCES += isNCES;
		//apply cuts here
		//cout<<TrueParticle->Vertex.ReactionCode<<endl;
		//APPLY CUTS HERE!!!
		//This program cuts from our tree, not original data.
		//Currently doesn't output anything, or cut anything
		// but cuts are defined in cuts.C
		for( ; j<NCuts; j++){
			keep = cuts[j]->apply();
			if(!keep)
				break;
			correctCut[j] += isNCES;
			wrongCut[j] += !isNCES;
		}
		//Horrible Dirty Hist bits
		if(keep)
		{
			Double_t fillval = Length;
			cout << Length << endl;
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
		//after cuts applied, keep will be = 1 if it is to be kept	
	} // End loop over events
	printf("initially: eff = %6.5f, pur = %6.5f\n", (double)initialNCES/(double)NNCES, (double)initialNCES/(double)NTOT);
	for (int n(0); n < NCuts; n++){
		double eff = (double)correctCut[n]/(double)NNCES, pur = (double)correctCut[n]/(double)(correctCut[n]+wrongCut[n]);
		printf("%12s:     eff = %6.5f, pur = %6.5f, e*p = %6.5f\n",cuts[n]->name.c_str(),eff, pur, eff*pur);
	}
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

