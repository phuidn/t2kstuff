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
#include <cuts.h>
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
	cout<<"opening tree"<<endl;
	// Open the TTree we made
	TFile *treefile = new TFile("../../../tree/evetree.root");
	TTree *tree = (TTree*) treefile->Get("newtree");

	//Variables to get from the tree
	UInt_t Detectors;
	UInt_t Status;
	Double_t Quality,FrontMomentum(0), BackMomentum(0);
	Int_t NHits;
	Bool_t IsForward;
	TLorentzVector *FrontPosition(0), *BackPosition(0);
	TVector3 *FrontDirection(0), *BackDirection(0);
	ND::TTrueParticle *TrueParticle(0);
	UInt_t NNCES;
	UInt_t NTOT;
	TString *FName(0);

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
	cout << "Tree->Detectors " << tree->SetBranchAddress("Detectors", &Detectors) << endl;
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
	tree->SetBranchAddress("FName", &FName);
	UInt_t accepted(0), acceptedNCES(0), acceptedNoise(0), initialNCES(0);
	int NCuts = 11,
		correctCut[11] = {0,0,0,0,0,0,0},
		wrongCut[11] = {0,0,0,0,0,0,0};
	NTOT = tree->GetEntries();
	// Loop over the entries in the TTree
	cout<<"looping over " <<NTOT<<" events"<<endl;
	for(unsigned int i = 0; i < NTOT; ++i) {
		if((i+1)%1000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;
		//display status every 1,000 th entry
		// Get an entry for the tree
		tree->GetEntry(i);
		int keep(1), isNCES = TrueParticle->Vertex.ReactionCode.find("Weak[NC],QES;",0)!=-1; //is the particle going to be kept, is it NCES
		initialNCES += isNCES;
		cout << FName << endl;
		//apply cuts here
		//cout<<TrueParticle->Vertex.ReactionCode<<endl;
		//APPLY CUTS HERE!!!
		//This program cuts from our tree, not original data.
		//Currently doesn't output anything, or cut anything
		// but cuts are defined in cuts.C
		keep = keep? noTPC1(Detectors): 0;
		correctCut[0] += keep && isNCES;
		wrongCut[0] += keep && !isNCES;
		keep = keep? noP0Dactivity(Detectors): 0;
		correctCut[1] += keep && isNCES; 
		wrongCut[1] += keep && !isNCES;
		keep = keep? posCharge(NTPCs, TPC): 0;
		correctCut[2] += keep && isNCES; 
		wrongCut[2] += keep && !isNCES;
		keep = keep? consecutiveDetectors(Detectors):0;
		correctCut[3] += keep && isNCES; 
		wrongCut[3] += keep && !isNCES;
		keep = keep? protonPull(NTPCs, TPC):0;
		correctCut[4] += keep && isNCES;
		wrongCut[4] += keep && !isNCES;
		keep = keep? muonPull(NTPCs, TPC):0;
		correctCut[5] += keep && isNCES;
		wrongCut[5] += keep && !isNCES;
		keep = keep? cutNHits(NHits):0;
		correctCut[6] += keep && isNCES;
		wrongCut[6] += keep && !isNCES;	
		keep = keep? cutMomentum(FrontMomentum):0;
		correctCut[7] += keep && isNCES;
		wrongCut[7] += keep && !isNCES;
		keep = keep? cutMomentum(BackMomentum, 130):0;
		correctCut[8] += keep && isNCES;
		wrongCut[8] += keep && !isNCES;
		keep = keep? cutNECAL(NECALs):0;
		correctCut[9] += keep && isNCES;
		wrongCut[9] += keep && !isNCES;
		keep = keep? cutNSMRD(NSMRDs):0;
		correctCut[10] += keep && isNCES;
		wrongCut[10] += keep && !isNCES;
		//after cuts applied, keep will be = 1 if it is to be kept	
	} // End loop over events
	printf("initially: eff = %6.5f, pur = %6.5f\n", (double)initialNCES/(double)NNCES, (double)initialNCES/(double)NTOT);
	for (int n(0); n < NCuts; n++){
		double eff = (double)correctCut[n]/(double)NNCES, pur = (double)correctCut[n]/(double)(correctCut[n]+wrongCut[n]);
		printf("cut%2d:     eff = %6.5f, pur = %6.5f, e*p = %6.5f\n",n,eff, pur, eff*pur);
	}
		
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

