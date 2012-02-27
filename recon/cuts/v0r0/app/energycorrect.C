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
#include <TSVDUnfold.h>
#include <classcuts.h>
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
	TApplication *App = new TApplication("Application",(Int_t*)&argc, argv);
	TCanvas *canvas = new TCanvas("canvas", "canvas", 640, 640);
	cout<<"opening tree"<<endl;
	// Open the TTree we made
	TFile *treefile = new TFile("../../../tree/magnet3xwindow.root");
	TTree *tree = (TTree*) treefile->Get("newtree");

	//Variables to get from the tree
	UInt_t Detectors(0);
	UInt_t Status(0);
	Double_t Quality,FrontMomentum(0), BackMomentum(0);
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
	int	NCEScount[NCuts],
		totCount[NCuts],
		CCQEScount[NCuts],
		CCREScount[NCuts],
		NCREScount[NCuts],
		DIScount[NCuts],
		otherCount[NCuts];
	memset(NCEScount, 0, NCuts*sizeof(int));
	memset(CCQEScount, 0, NCuts*sizeof(int));
	memset(CCREScount, 0, NCuts*sizeof(int));
	memset(NCREScount, 0, NCuts*sizeof(int));
	memset(DIScount, 0, NCuts*sizeof(int));
	memset(otherCount, 0, NCuts*sizeof(int));
	memset(totCount, 0, NCuts*sizeof(int));
	
	NTOT = tree->GetEntries();
	for(unsigned int i = 0; i < NTOT/2; ++i) {
		if((i+1)%1000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;
		//display status every 1,000 th entry
		// Get an entry for the tree
		tree->GetEntry(i);
		int keep(1), j(0), isNCES = TrueParticle->Vertex.ReactionCode.find("Weak[NC],QES;",0)!=-1;

		initialNCES += isNCES;
		//apply cuts here
		for( ; j<NCuts; j++){
			keep = cuts[j]->apply();
			if(!keep)
				break;
			totCount[j]++;
			NCEScount[j] += isNCES;
			if (!isNCES){
				CCQEScount[j] += TrueParticle->Vertex.ReactionCode.find("Weak[CC],QES;",0)!=-1;
				CCREScount[j]  += TrueParticle->Vertex.ReactionCode.find("Weak[CC],RES;",0)!=-1;
				NCREScount[j]  += TrueParticle->Vertex.ReactionCode.find("Weak[NC],RES;",0)!=-1;
				DIScount[j]  += TrueParticle->Vertex.ReactionCode.find("DIS;",0)!=-1;	
			}
		}
		//after cuts applied, keep will be = 1 if it is to be kept	
	} // End loop over events
	printf("initially: eff = %6.5f, pur = %6.5f\n", (double)initialNCES/(double)NNCES, 2.*(double)initialNCES/(double)NTOT);
	for (int n(0); n < NCuts; n++){
		double eff = (double)NCEScount[n]/(double)NNCES, pur = (double)NCEScount[n]/(double)totCount[n];
		printf("%12s:     eff = %6.5f, pur = %6.5f, e*p = %6.5f\n",cuts[n]->name.c_str(),eff, pur, eff*pur);
	}
	int nbins = 5;
	double bounds[6]={0.,0.224,0.448,0.672,0.896,1.12};
	TH1D *truth = new TH1D("truthhist", "Title", nbins, bounds),
		*recon = new TH1D("reconhist", "Title", nbins, bounds);
	for(unsigned int i = NTOT/2; i < NTOT; ++i) {
		tree->GetEntry(i);
		int keep(1), j(0);

		for( ; j<NCuts; j++){
			keep = cuts[j]->apply();
			if(!keep)
				break;
		}
		if(keep){
			recon->Fill(FrontMomentum*FrontMomentum/(2.*938.));	
			TLorentzVector v = TrueParticle->InitMom;
			Double_t truth_mom = sqrt(v.X()*v.X()+v.Y()*v.Y()+v.Z()*v.Z());
			truth->Fill(truth_mom*truth_mom/(2.*938.));
		}

	}
	
	TSVDUnfold *unf = new TSVDUnfold(datahist,reconhist,truthhist,matrixhist);
	TH1D unfolded = unf->Unfold(2.);
	TH2D unfcov = unf->GetAdetCovMatrix(5000, 32);
	cout << "truth count = " << truedatahist->GetEntries() << ", unfolded count = " << unfolded->GetEntries() << endl;
//	unfcov->Draw("COLZ");
	for(int k(1); k<nbins+1; k++){
		unfolded->SetBinError(k,sqrt(unfcov->GetBinContent(k,k)));
		cout << unfolded->GetBinContent(k) << "	";
	}
	unfolded->Draw("E1");
	truedatahist->Draw("same");
	cout << endl;
	App->Run();



	cout << "Background components:" << endl;
	printf("%6.5f%% CCQES\n", (double)CCQEScount[NCuts-1]/((double)totCount[NCuts-1] - (double)NCEScount[NCuts-1]));
	printf("%6.5f%% NCRES\n", (double)NCREScount[NCuts-1]/((double)totCount[NCuts-1] - (double)NCEScount[NCuts-1]));
	printf("%6.5f%% CCRES\n", (double)CCREScount[NCuts-1]/((double)totCount[NCuts-1] - (double)NCEScount[NCuts-1]));
	printf("%6.5f%% DIS\n", (double)DIScount[NCuts-1]/((double)totCount[NCuts-1] - (double)NCEScount[NCuts-1]));
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

