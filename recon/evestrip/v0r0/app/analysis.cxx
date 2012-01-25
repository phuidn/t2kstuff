//Callum Lister (University of Warwick)
//Script to extract information about anti-numu CC events

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
#include <TVector3.h>
#include <TLorentzVector.h>

#include "TTruthVerticesModule.hxx"
#include "TGlobalReconModule.hxx"
#include "TTrackerReconModule.hxx"

//void SetupROOT();
bool IsInBeamTime(const double[], double, double);
double GetTheta(double, double, double);
int ConvertParentPDG(int);
int ConvertPDG(int);
bool IsInVolume(TVector3, TVector3, TVector3);
bool IsInFiducialFGD1(TVector3);
bool IsInFiducialFGD1(TLorentzVector);
bool IsInFiducialFGD2(TVector3);
bool IsInFiducialFGD2(TLorentzVector);
bool IsInDetector(unsigned long, std::string);

void ParseFileName( std::string FileName, int &run, int &subrun) {
        std::vector<std::string>token;
        std::istringstream iss(FileName);
        std::string tokenstring;
        while (getline(iss,tokenstring,'_')) {
         token.push_back(tokenstring);
        }

        std::vector<std::string>token2;
        std::string interest = token[3];
        std::istringstream iss2(interest);
        while (getline(iss2,tokenstring,'-')) {
         token2.push_back(tokenstring);
        }

        run=atoi(token2[0].c_str());
        subrun=atoi(token2[1].c_str());
}


//---------------------------------------------------------------------------//
//																Main Method.															 //
//---------------------------------------------------------------------------//
int main(){

	// Set up ROOT as we require.
	// SetupROOT();

        // Get list of files to run over. 
        // This should be located in the same directory as the data files.
        TString fileName("oaanalysis_files.list");
        std::ifstream inputFile(fileName.Data());

	// TChain for each subdetector.
	TChain *gRecon = new TChain("ReconDir/Global");
        TChain *gGenVtx = new TChain("TruthDir/Vertices");

	// Check if the file exists.
	if (!inputFile.is_open()){
		std::cout << "ERROR: File prod4C.analysis not found!" << std::endl;
		std::cout << " - This file should contain a list of all data files to be processed." << std::endl;
		return 0;
	}
	else{
		std::string curFileName;

		// Add the input files to the TChains.
		while(getline(inputFile,curFileName)){
			gRecon->Add(curFileName.c_str());
			gGenVtx->Add(curFileName.c_str());
		}
	}

	std::cout << "Got input file(s)." << std::endl;

	// Setup access to the Global Tree.
	int NPIDs(0), NVertices(0), EventID(0), NDelayedClusters(0), NFgdTimeBins(0);
	TClonesArray *globalPIDs = new TClonesArray("ND::TGlobalReconModule::TGlobalPID", 20);
	TClonesArray *globalVertices = new TClonesArray("ND::TGlobalReconModule::TGlobalVertex", 10);
	gRecon->SetBranchAddress("NPIDs", &NPIDs);
	gRecon->SetBranchAddress("NVertices",&NVertices);
	gRecon->SetBranchAddress("PIDs", &globalPIDs);
	gRecon->SetBranchAddress("Vertices", &globalVertices);
	gRecon->SetBranchAddress("EventID", &EventID);
	gRecon->SetBranchAddress("NDelayedClusters", &NDelayedClusters);
	gRecon->SetBranchAddress("NFgdTimeBins", &NFgdTimeBins);

        //Setup access to the TruthDir Tree
        int NVtxFGD1(0), NVtxFGD2(0);
        // Declare a TClonesArray to hold objects of type ND::GRooTrackerVtx
        TClonesArray *VtxFGD1 = new TClonesArray("ND::TTruthVerticesModule::TTruthVertex",50);
        TClonesArray *VtxFGD2 = new TClonesArray("ND::TTruthVerticesModule::TTruthVertex",50);
        // Associate the right branch in the TTree to the right local variable
        gGenVtx->SetBranchAddress("VtxFGD2",&VtxFGD2);
        gGenVtx->SetBranchAddress("NVtxFGD2",&NVtxFGD2);
        gGenVtx->SetBranchAddress("VtxFGD1",&VtxFGD1);
        gGenVtx->SetBranchAddress("NVtxFGD1",&NVtxFGD1);

	//Set up output tree and variables
	int isNuE(0), isAntiNuE(0), isNuMu(0), isAntiNuMu(0), isCC(0), isNC(0), isQES(0), isCoh(0), isDIS(0), isRES(0);

	int signalNCQE(-1), signalCC(-1), isInBeamTime(-1);
	int trueParticle(-99), parentParticle(-99), nHits(0), nConstituents(0), nDOF(0), charge(0);
	double xPosition(0.), yPosition(0.), zPosition(0.), xDirection(0.), yDirection(0.);
        double zDirection(0.), theta(0.), vertexTime(0.), chi2(0.), eDeposit(0.), momentum(0.);
	double pullElec(-100.), pullMuon(100.), pullPion(-100.), pullProton(-100.), absPullElec(-1.), absPullMuon(-1.),
		   absPullPion(-1.), absPullProton(-1.), trackOrShower(99.), ecalEMEnergy(-1.), minVertexDistance(999.);
	int numTPCHits(0), numECALHits(0), numOtherPosTracks(0), numOtherTracks(0), tpcNumber(0), fgdNumber(0);
        int passedFidCut(0), passedTimeCut(0), RunNumber(0), SubrunNumber(0), NInTime(0), Signal(0);
	int iTarget(0);

	TFile file("histo.root","RECREATE");

	TTree *fTree1 = new TTree("EventMiniDST","EventMiniDST");
	fTree1->Branch("IsNuE", &isNuE, "isNuE/I");
	fTree1->Branch("IsAntiNuE", &isAntiNuE, "isAntiNuE/I");
	fTree1->Branch("IsNuMu", &isNuMu, "isNuMu/I");
	fTree1->Branch("IsAntiNuMu", &isAntiNuMu, "isAntiNuMu/I");
	fTree1->Branch("IsCC", &isCC, "isCC/I");
	fTree1->Branch("IsNC", &isNC, "isNC/I");
	fTree1->Branch("IsQES", &isQES, "isQES/I");
	fTree1->Branch("IsCoh", &isCoh, "isCoh/I");
	fTree1->Branch("IsDIS", &isDIS, "isDIS/I");
	fTree1->Branch("IsRES", &isRES, "isRES/I");
	fTree1->Branch("ITarget", &iTarget, "iTarget/I");
	fTree1->Branch("Signal", &Signal, "Signal/I");
	fTree1->Branch("SignalNCQE", &signalNCQE, "signalNCQE/I");
	fTree1->Branch("SignalCC", &signalCC, "signalCC/I");
	fTree1->Branch("TrueParticle", &trueParticle, "trueParticle/I");
	fTree1->Branch("ParentParticle", &parentParticle, "parentParticle/I");
	fTree1->Branch("NPIDs", &NPIDs);
	fTree1->Branch("TPCNumber", &tpcNumber, "tpcNumber/I");
	fTree1->Branch("FGDNumber", &fgdNumber, "fgdNumber/I");
	fTree1->Branch("NVertices",&NVertices);
	fTree1->Branch("RunNumber",&RunNumber);
	fTree1->Branch("SubrunNumber",&SubrunNumber);
	fTree1->Branch("EventID", &EventID);
	fTree1->Branch("NDelayedClusters", &NDelayedClusters);
	fTree1->Branch("NFgdTimeBins", &NFgdTimeBins);
	fTree1->Branch("XPosition", &xPosition, "xPosition/D");
	fTree1->Branch("YPosition", &yPosition, "yPosition/D");
	fTree1->Branch("ZPosition", &zPosition, "zPosition/D");
	fTree1->Branch("XDirection", &xDirection, "xDirection/D");
	fTree1->Branch("YDirection", &yDirection, "yDirection/D");
	fTree1->Branch("ZDirection", &zDirection, "zDirection/D");
	fTree1->Branch("Theta", &theta, "theta/D");
	fTree1->Branch("VertexTime", &vertexTime, "vertexTime/D");
	fTree1->Branch("IsInBeamTime", &isInBeamTime, "isInBeamTime/I");
	fTree1->Branch("Chi2", &chi2, "chi2/D");
	fTree1->Branch("NDOF", &nDOF, "nDOF/I");
	fTree1->Branch("NHits", &nHits, "nHits/I");
	fTree1->Branch("NConstituents", &nConstituents, "nConstituents/I");
	fTree1->Branch("Charge", &charge, "charge/I");
	fTree1->Branch("EDeposit", &eDeposit, "eDeposit/D");
	fTree1->Branch("Momentum", &momentum, "momentum/D");
	fTree1->Branch("MinVertexDistance", &minVertexDistance, "minVertexDistance/D");
	fTree1->Branch("PullElec", &pullElec, "pullElec/D");
	fTree1->Branch("PullMuon", &pullMuon, "pullMuon/D");
	fTree1->Branch("PullPion", &pullPion, "pullPion/D");
	fTree1->Branch("PullProton", &pullProton, "pullProton/D");
	fTree1->Branch("AbsPullElec", &absPullElec, "absPullElec/D");
	fTree1->Branch("AbsPullMuon", &absPullMuon, "absPullMuon/D");
	fTree1->Branch("AbsPullPion", &absPullPion, "absPullPion/D");
	fTree1->Branch("AbsPullProton", &absPullProton, "absPullProton/D");
	fTree1->Branch("NumTPCHits", &numTPCHits, "numTPCHits/I");
	fTree1->Branch("NumECALHits", &numECALHits, "numECALHits/I");
	fTree1->Branch("NumOtherPosTracks", &numOtherPosTracks, "numOtherPosTracks/I");
	fTree1->Branch("NumOtherTracks", &numOtherTracks, "numOtherTracks/I");
	fTree1->Branch("TrackOrShower", &trackOrShower, "trackOrShower/D");
	fTree1->Branch("EMEnergy", &ecalEMEnergy, "ecalEMEnergy/D");
	fTree1->Branch("FidCut",&passedFidCut,"passedFidCut/I");
	fTree1->Branch("TimeCut",&passedTimeCut,"passedTimeCut/I");
	fTree1->Branch("NInTime",&NInTime,"NInTime/I");

        int NBins=11;
        TH1F *hsig = new TH1F("hsig","N signal",NBins,0.,NBins*1.0);
        TH1F *hbg = new TH1F("hbg","N background",NBins,0.,NBins*1.0);
        TH1F *hbgCCQE =  new TH1F("hbgCCQE","N CCQE",NBins,0.,NBins*1.0);
        TH1F *hbgCCRES = new TH1F("hbgCCRES","N CCRES",NBins,0.,NBins*1.0);
        TH1F *hbgNCRES = new TH1F("hbgNCRES","N NCRES",NBins,0.,NBins*1.0);
        TH1F *hbgCCDIS = new TH1F("hbgCCDIS","N CCDIS",NBins,0.,NBins*1.0);
        TH1F *hbgNCDIS = new TH1F("hbgNCDIS","N NCDIS",NBins,0.,NBins*1.0);
	TH1F *hBeam = new TH1F("hBeam","hBeam",1000,2000.,7000.);
	TH1F *hsigBeam = new TH1F("hsigBeam","hsigBeam",500,-4000.,4000.);
	TH1F *hbgBeam = new TH1F("hbgBeam","hbgBeam",500,-4000.,4000.);

	//constants and variables
	const int fECalNHits(10);
	const double beamTimeArray[8] = {2752.,3333.,3915.,4498.,5080.,5661.,6244.,6826.}, beamTimeCut(100.);
        ofstream sigfile;
        sigfile.open("sig_event_data.dat");

        std::string oldName = "aaa";
//        for(unsigned int i = 0; i < gRecon->GetEntries(); ++i) {
    	for(unsigned int i = 0; i < 500000; ++i) {
		if((i+1)%10000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;
		//reset variables to strange numbers so know if anything's going wrong!
                std::string name = ((TFile*)gRecon->GetFile())->GetName();
		if (name.compare(oldName) != 0) {
                   ParseFileName(name,RunNumber,SubrunNumber);
                   oldName = name;
                }
		signalNCQE = -1;
		signalCC = -1;
		trueParticle = -99;
		parentParticle = -99;
		xPosition = -99.;
		yPosition = -99.;
		zPosition = -99.;
		xDirection = -99.;
		yDirection = -99.;
		zDirection = -99.;
		theta = -99.;
		vertexTime = -99.;
		chi2 = -99.;
		nDOF = 0;
		nHits = 0;
		nConstituents = 0;
		charge = -99;
		eDeposit = -99.;
		momentum = -99.;
		minVertexDistance = -99.;
		pullElec = -99.;
		pullMuon = -99.;
		absPullElec = -99.;
		absPullMuon = -99.;
		pullPion = -99.;
		pullProton = -99.;
		absPullPion = -99.;
		absPullProton = -99.;
		numTPCHits = 0;
		numECALHits = 0;
		trackOrShower = 99.;
		tpcNumber = 0;
		fgdNumber = 0;
		passedTimeCut = 0;
		passedFidCut = 0;
		NInTime = 0;

		isNuE = 0;
		isAntiNuE = 0;
		isNuMu = 0;
		isAntiNuMu = 0;
		isCC = 0;
		isNC = 0;
		isQES = 0;
		isCoh = 0;
		isDIS = 0;
		isRES = 0;
	        iTarget = 0;

		gRecon->GetEntry(i);
                gGenVtx->GetEntry(i);
                ND::TTruthVerticesModule::TTruthVertex *vtx = NULL;
                int isSignal=0;
                for (int j=0; j<NVtxFGD1; j++) {
                 vtx = (ND::TTruthVerticesModule::TTruthVertex*)VtxFGD1->At(j);
		 std::string ReactionCode = vtx->ReactionCode;	

                 if ( (ReactionCode.find("Weak[NC]")!=std::string::npos) &&
                      (ReactionCode.find("QES")!=std::string::npos) &&
                      (ReactionCode.find("N:2212")!=std::string::npos)) {
                  isSignal=1;
 		  iTarget = 2212;
                 } 
                 if ( (ReactionCode.find("Weak[NC]")!=std::string::npos) &&
                      (ReactionCode.find("QES")!=std::string::npos) &&
                      (ReactionCode.find("N:2112")!=std::string::npos)) {
 		  iTarget = 2112;
                 } 
                } 

                for (int j=0; j<NVtxFGD2; j++) {
                 vtx = (ND::TTruthVerticesModule::TTruthVertex*)VtxFGD2->At(j);
		 std::string ReactionCode = vtx->ReactionCode;
                 if ( (ReactionCode.find("Weak[NC]")!=std::string::npos) &&
                      (ReactionCode.find("QES")!=std::string::npos)  &&
                      (ReactionCode.find("N:2212")!=std::string::npos)) {
		  std::cout << ReactionCode.c_str() << std::endl;
                  isSignal=1;
 		  iTarget = 2212;
                 }
                 if ( (ReactionCode.find("Weak[NC]")!=std::string::npos) &&
                      (ReactionCode.find("QES")!=std::string::npos) &&
                      (ReactionCode.find("N:2112")!=std::string::npos)) {
 		  iTarget = 2112;
                 } 
                } 
		Signal=isSignal;
                float iFill=0.5;
                if (isSignal>0) { 
                 hsig->Fill(iFill); 
		 sigfile << RunNumber << " " << SubrunNumber << " " << EventID << std::endl;
                } else {
		 hbg->Fill(iFill);
		 hbgNCRES->Fill(iFill); 
		 hbgNCDIS->Fill(iFill);
		 hbgCCQE->Fill(iFill); 
		 hbgCCRES->Fill(iFill);
		 hbgCCDIS->Fill(iFill);
                }


//
//		gGenVtx->GetEntry(1646);
//                std::cout << " Vertex in (F1,F2,P,DS,TPC) : " << NVtxFGD1 << "," << NVtxFGD2 << "," << NVtxPOD << "," << NVtxDsECal << "," << NVtxTPC << std::endl;
//                ND::TTruthVerticesModule::TTruthVertex vtx;
//                for (int j=0; j<NVtxFGD2; j++) {
//                 vtx = (ND::TTruthVerticesModule::TTruthVertex)VtxFGD->At(j);
//		 std::string ReactionCode = vtx.ReactionCode;
//		 TLorentzVector vec = vtx.MomNu;
//		 TLorentzVector vpos = vtx.Vertex;
//		 std::cout << "Event " << EventID << " Reaction Code " << ReactionCode.c_str() << endl;
//               std::cout << "Neutrino Energy : " << vec.E() << std::endl;
//		 std::cout << "Vertex Position : (" << vpos.X() << "," << vpos.Y() << "," << vpos.Z() << ")" << std::endl;
//     
//                }


		//Skip event if no PIDs are found
		if(NPIDs == 0) continue;
                iFill=1.5;
                if (isSignal>0) { 
                 hsig->Fill(iFill); 
                } else {
		 hbg->Fill(iFill);
		 hbgNCRES->Fill(iFill); 
		 hbgNCDIS->Fill(iFill);
		 hbgCCQE->Fill(iFill); 
		 hbgCCRES->Fill(iFill);
		 hbgCCDIS->Fill(iFill);
                }

		minVertexDistance = 999.;

		// Work out how many PIDs are found and where
		int inFGD(0),inTPC(0),inEcal(0),inTPC1(0);
		int inFGD1(0),inFGD2(0);
		int iAccept(0),iReject(0);
                inFGD=0; inTPC=0; inEcal=0; inTPC1=0; inFGD1=0; inFGD2=0; iAccept=0; iReject=0;
		for(int j = 0; j < NPIDs; ++j){
			inFGD=0; inTPC=0; inEcal=0; 
			ND::TGlobalReconModule::TGlobalPID *gTrack = (ND::TGlobalReconModule::TGlobalPID*)globalPIDs->At(j);
			TLorentzVector pos = gTrack->FrontPosition;
                        hBeam->Fill(pos.T());
			if (IsInDetector(gTrack->Detectors,"TPC1")) inTPC1=1;
            	  	if (IsInDetector(gTrack->Detectors,"TPC2") ||
					IsInDetector(gTrack->Detectors,"TPC3")) inTPC=1;
			if (IsInDetector(gTrack->Detectors,"FGD1")||IsInDetector(gTrack->Detectors,"FGD2")) inFGD=1;
                        if (IsInDetector(gTrack->Detectors,"DsECal")||IsInDetector(gTrack->Detectors,"PECal")||
                            IsInDetector(gTrack->Detectors,"TECal")) inEcal=1;
                        if (inFGD>=1&&inTPC1==0) {
                         iAccept++; 
                        } else {
                         iReject++; 
                        } 
		}

		// Check that we have at least one accepted event
		if(iAccept==0) continue;

                // Work out how many PIDs are found and where
                int inTPC2(0),inTPC3(0),inP0D(0);
		inFGD1=0; inFGD2=0; inTPC2=0; inTPC3=0; inP0D=0;
                for(int j = 0; j < NPIDs; ++j){
                        ND::TGlobalReconModule::TGlobalPID *gTrack = (ND::TGlobalReconModule::TGlobalPID*)(*globalPIDs)[j];
                        if (IsInDetector(gTrack->Detectors,"TPC2")) inTPC2++;
                        if (IsInDetector(gTrack->Detectors,"TPC3")) inTPC3++;
                        if (IsInDetector(gTrack->Detectors,"FGD1")) inFGD1++;
                        if (IsInDetector(gTrack->Detectors,"FGD2")) inFGD2++;
                        if (IsInDetector(gTrack->Detectors,"P0D")) inP0D++;
                }
                int CandEvent=0;
                if (inFGD1==1&&inTPC2==1) CandEvent++;
                if (inFGD2==1&&inTPC3==1&&inTPC2==0) CandEvent++;

                if (CandEvent==0) continue;

                // Choose the most proton-like track as "the" track. This will have the largest muon pull
		int iProtonCand(-1);
                float maxMuPull(-10.0);
                iProtonCand=-1;
                maxMuPull=-10.;
                for(int j = 0; j < NPIDs; ++j){
                 ND::TGlobalReconModule::TGlobalPID *gTrack = (ND::TGlobalReconModule::TGlobalPID*)(*globalPIDs)[j];
		 // Now need to open up the track and look for the TPC object
                 TClonesArray *TPCObjects = new TClonesArray("ND::TGlobalReconModule::TTPCObject",gTrack->NTPCs);
                 TPCObjects = gTrack->TPC;
                 //Find number of TPC hits and cut if less than required
                 ND::TGlobalReconModule::TTPCObject *tpcTrack;
                 if (gTrack->NTPCs==0) break;
		 for(int k = 0; k < gTrack->NTPCs; ++k) {
                  tpcTrack = (ND::TGlobalReconModule::TTPCObject*)(*TPCObjects)[k];
                  if (tpcTrack->PullMuon>maxMuPull) {
                   maxMuPull = tpcTrack->PullMuon;
                   iProtonCand = j;
                  }
		 }
                }

                if (iProtonCand<0) continue;

		ND::TGlobalReconModule::TGlobalPID *CandTrack = (ND::TGlobalReconModule::TGlobalPID*)(*globalPIDs)[iProtonCand];
                //Get PDG code of proton candidate
		ND::TTrueParticle *tpart = &CandTrack->TrueParticle;
                trueParticle = tpart->PDG;
                std::string evtCode = CandTrack->TrueParticle.Vertex.ReactionCode;

                if (evtCode.find("nu:12")!=std::string::npos) isNuE=1;
                if (evtCode.find("nu:-12")!=std::string::npos) isAntiNuE=1;
                if (evtCode.find("nu:14")!=std::string::npos) isNuMu=1;
                if (evtCode.find("nu:-14")!=std::string::npos) isAntiNuMu=1;
                if (evtCode.find("Weak[CC]")!=std::string::npos) isCC=1;
                if (evtCode.find("Weak[NC]")!=std::string::npos) isNC=1;
                if (evtCode.find("QES")!=std::string::npos) isQES=1;
                if (evtCode.find("COH")!=std::string::npos) isCoh=1;
                if (evtCode.find("DIS")!=std::string::npos) isDIS=1;
                if (evtCode.find("RES")!=std::string::npos) isRES=1;

                parentParticle = CandTrack->TrueParticle.Vertex.PDG;
                parentParticle = ConvertParentPDG(parentParticle);
                if(isNC>0 && isQES>0) {signalNCQE = 1;}
                else {signalNCQE = 0;}

		iFill=2.5;
                if (isSignal>0) {
                 hsig->Fill(iFill);
                } else {
                 hbg->Fill(iFill);
                 if (isNC>0 && isRES>0) { hbgNCRES->Fill(iFill); }
                 if (isNC>0 && isDIS>0) { hbgNCDIS->Fill(iFill); }
                 if (isCC>0 && isQES>0) { hbgCCQE->Fill(iFill); }
                 if (isCC>0 && isRES>0) { hbgCCRES->Fill(iFill); }
                 if (isCC>0 && isDIS>0) { hbgCCDIS->Fill(iFill); }
                }

		//If vertex is in FGD1, require a track in TPC2 AND must not have a track in TPC1
                unsigned long Detector = CandTrack->Detectors;
		TLorentzVector vertexPos = CandTrack->FrontPosition;
                if(IsInFiducialFGD1(vertexPos)) {
                        if(IsInDetector(Detector,"TPC1")) continue;
                        if(!IsInDetector(Detector,"TPC2")) continue;
                        fgdNumber = 1;
                        tpcNumber = 2;
                }       //If vertex is in FGD2, require a track in TPC3, AND must not have a track in TPC2
                else if(IsInFiducialFGD2(vertexPos)) {
                        if(IsInDetector(Detector,"TPC2")) continue;
                        if(!IsInDetector(Detector,"TPC3")) continue;
                        fgdNumber = 2;
                        tpcNumber = 3;
                }
                else continue;

		iFill=3.5;
                if (isSignal>0) {
                 hsig->Fill(iFill);
                } else {
                 hbg->Fill(iFill);
                 if (isNC>0 && isRES>0) { hbgNCRES->Fill(iFill); }
                 if (isNC>0 && isDIS>0) { hbgNCDIS->Fill(iFill); }
                 if (isCC>0 && isQES>0) { hbgCCQE->Fill(iFill); }
                 if (isCC>0 && isRES>0) { hbgCCRES->Fill(iFill); }
                 if (isCC>0 && isDIS>0) { hbgCCDIS->Fill(iFill); }
                }

		xPosition = vertexPos.X();
		yPosition = vertexPos.Y();
		zPosition = vertexPos.Z();
		vertexTime = vertexPos.T();

		TVector3 direction = CandTrack->FrontDirection;
		xDirection = direction.X();
		yDirection = direction.Y();
		zDirection = direction.Z();
		theta = GetTheta(xDirection,yDirection,zDirection);

		chi2 = CandTrack->Chi2;
		nDOF = CandTrack->NDOF;
		nConstituents = CandTrack->NConstituents;
		nHits = CandTrack->NHits;
		charge = CandTrack->Charge;
		eDeposit = CandTrack->EDeposit;
		momentum = CandTrack->FrontMomentum;

		//Check if vertex is in beam time
		isInBeamTime = IsInBeamTime(beamTimeArray,beamTimeCut,vertexTime);
		if (isInBeamTime) passedTimeCut=1;
		iFill=4.5;
                if (isSignal>0) {
                 hsig->Fill(iFill);
                } else {
                 hbg->Fill(iFill);
                 if (isNC>0 && isRES>0) { hbgNCRES->Fill(iFill); }
                 if (isNC>0 && isDIS>0) { hbgNCDIS->Fill(iFill); }
                 if (isCC>0 && isQES>0) { hbgCCQE->Fill(iFill); }
                 if (isCC>0 && isRES>0) { hbgCCRES->Fill(iFill); }
                 if (isCC>0 && isDIS>0) { hbgCCDIS->Fill(iFill); }
                }

		//Check that there is no other PID within 100 ns of this one in the track
                for(int j = 0; j < NPIDs; ++j){
                 ND::TGlobalReconModule::TGlobalPID *gTrack = (ND::TGlobalReconModule::TGlobalPID*)(*globalPIDs)[j];
		 TLorentzVector CandPos = gTrack->FrontPosition;
                 if (j!=iProtonCand) {
		  if (signalNCQE>0) {
                   hsigBeam->Fill(TMath::Abs(CandPos.T()-vertexTime));
                  } else {
                   hbgBeam->Fill(TMath::Abs(CandPos.T()-vertexTime));
                  }
		  if (TMath::Abs(CandPos.T()-vertexTime)<200) NInTime++;
                 }
                }
         

		//Check that we have a positive particle
		//if(leptonTrack->Charge == -1) continue;

		//Track quality cut - do not implement yet
		//if(leptonTrack->Quality > a_number ) continue;

		// Now need to open up the track and look for the TPC object
		TClonesArray *TPCObjects = new TClonesArray("ND::TGlobalReconModule::TTPCObject",CandTrack->NTPCs);
		TPCObjects = CandTrack->TPC;

		//Find number of TPC hits and cut if less than required
		ND::TGlobalReconModule::TTPCObject *tpcTrack = NULL;
		for(int k = 0; k < CandTrack->NTPCs; ++k) {
			tpcTrack = (ND::TGlobalReconModule::TTPCObject*)(*TPCObjects)[k];
			if(tpcTrack->Detector == tpcNumber) {
				numTPCHits = tpcTrack->NHits;
				break;
			}
		}

                TClonesArray *ECALComp = new TClonesArray("ND::TGlobalReconModule::TECALObject",CandTrack->NECALs);
                ECALComp = CandTrack->ECAL;

                //This veto only cuts on any objects that have enough hits in the ECAL. The default is to pass the cut; if there
                //are enough hits, then veto events with a low enough trShVal.
                trackOrShower = 99.;
                ecalEMEnergy = -1.;
                if(CandTrack->NECALs != 0){
                        ND::TGlobalReconModule::TECALObject *tempECAL = (ND::TGlobalReconModule::TECALObject*)(*ECALComp)[0];
                        if(tempECAL != NULL) {
                         numECALHits = tempECAL->NHits;
                         //trackOrShower = tempECAL->TrShVal;
                         if(tempECAL->NHits >= fECalNHits) {
                                 trackOrShower = tempECAL->TrShVal;
                                 ecalEMEnergy = tempECAL->EMEnergy;
                         }
                        }
                }

		// Now get the pull information from the TPC track.
		pullElec = tpcTrack->PullEle;
		absPullElec = fabs(pullElec);
		pullMuon = tpcTrack->PullMuon;
		absPullMuon = fabs(pullMuon);
		pullPion = tpcTrack->PullPion;
		absPullPion = fabs(pullPion);
		pullProton = tpcTrack->PullProton;
		absPullProton = fabs(pullProton);

		fTree1->Fill();
	} // End loop over events

	file.Write();
	sigfile.close();
	return 1;

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

//---------------------------------------------------------------------------//
//					Method to see if the particle went through detector <name>			 //
//---------------------------------------------------------------------------//

// <name> = TPC1, TPC2, TPC3, FGD1, FGD2, DsECal, TECal, PECal, P0D or SMRD
bool IsInDetector(unsigned long detList, std::string name){

	std::string search = "x";
        std::string detString;
        std::stringstream detStrStream;
        detStrStream << detList;
        detString = detStrStream.str();
       
	if (name.compare("TPC1")==0) search = "1";
	else if (name.compare("TPC2")==0) search = "2";
	else if (name.compare("TPC3")==0) search = "3";
	else if (name.compare("FGD1")==0) search = "4";
	else if (name.compare("FGD2")==0) search = "5";
	else if (name.compare("DsECal")==0) search = "7";
	else if (name.compare("TECal")==0) search = "9";
	else if (name.compare("PECal")==0) search = "9";
	else if (name.compare("P0D")==0) search = "6";
	else if (name.compare("SMRD")==0) search = "8";

	int found = detString.find(search);
        if (found!=std::string::npos) return true;
        return false;
}

//---------------------------------------------------------------------------//
//						Methods to check if vertex is in FGD Fiducial Volumes					 //
//---------------------------------------------------------------------------//
bool IsInVolume(TVector3 pos, TVector3 minpos, TVector3 maxpos){        

	if(pos[0] >= minpos[0] && 
			pos[1] >= minpos[1] && 
			pos[2] >= minpos[2] && 
			pos[0] <= maxpos[0] && 
			pos[1] <= maxpos[1] && 
			pos[2] <= maxpos[2])   
		return true;            
	else return false;               
}              

bool IsInFiducialFGD1(TVector3 pos){
	TVector3 fFGD1Min = TVector3(-832.2, -777.2, 123.45);
	TVector3 fFGD1Max = TVector3(832.2, 887.2, 446.95);

	return IsInVolume(pos,fFGD1Min,fFGD1Max);
}

bool IsInFiducialFGD1(TLorentzVector pos){
	return IsInFiducialFGD1(pos.Vect());
}

bool IsInFiducialFGD2(TVector3 pos){
	TVector3 fFGD2Min = TVector3(-832.2, -777.2, 1481.45);
	TVector3 fFGD2Max = TVector3(832.2, 887.2, 1807.95);

	return IsInVolume(pos,fFGD2Min,fFGD2Max);
}

bool IsInFiducialFGD2(TLorentzVector pos){
	return IsInFiducialFGD2(pos.Vect());
}

// Convert PDG Code for common particles to a more easily plotted number.
// -3        -2        -1        0         1         2         3         4
// pi-    mu-        e-        ?         e+         mu+     pi+     p+
int ConvertPDG(int PDGCode){
	int particle(0);

	switch (PDGCode){
		case 11: // e-
			particle = -1;
			break;
		case -11: // e+
			particle = 1;
			break;
		case 13: // mu -
			particle = -2;
			break;
		case -13: // mu +
			particle = 2;
			break;
		case 211: // pi +
			particle = 3;
			break;
		case -211: // pi -
			particle = -3;
			break;
		case 2212: // p+
			particle = 4;
			break;
		default : // Anything else
			particle = 0;
			break;
	}
	return particle;
}

int ConvertParentPDG(int PDGCode){
	int particle(0);

	switch (PDGCode){
		case 12: // nue
			particle = 1;
			break;
		case -12: // nuebar
			particle = -1;
			break;
		case 14: // numu
			particle = 2;
			break;
		case -14: // numubar
			particle = -2;
			break;
		default : // Anything else
			particle = 0;
			break;
	}
	return particle;
}

//----------------------------------------------------

double GetTheta(double x, double y, double z){
	double radius = TMath::Sqrt(x*x+y*y+z*z);

	double theta = TMath::ACos(z/radius)*TMath::RadToDeg();

	return theta;
}

//-----------------------------------------------------
/*//pseudo vertex-activity function
  void processActivity()
  {
// Get the first two hits from each track, and sum their charges to
// get an "activity"
TClonesArray* hits = new TClonesArray("ND::TGlobalReconModule::TGlobalHit", 4);
ND::TGlobalReconModule::TGlobalHit* hit;
// muon
hits = rg_muon_->HitsSaved;
hit = (ND::TGlobalReconModule::TGlobalHit*)(*hits)[0];
activity_ += hit->Charge;
hit = (ND::TGlobalReconModule::TGlobalHit*)(*hits)[1];
activity_ += hit->Charge;
// pion
hits = rg_pion_->HitsSaved;
hit = (ND::TGlobalReconModule::TGlobalHit*)(*hits)[0];
activity_ += hit->Charge;
hit = (ND::TGlobalReconModule::TGlobalHit*)(*hits)[1];
activity_ += hit->Charge;

this->fill("h_rg_vtx_activity", activity_);
} */

bool IsInBeamTime(const double beamTimeArray[], double beamTimeCut, double vertexTime) {

	int nBunches = 8;
	bool isInBeamTime(0);

	for (int i = 0; i < nBunches; ++i) {

		if((vertexTime > beamTimeArray[i] - beamTimeCut) && (vertexTime < beamTimeArray[i] + beamTimeCut)) {
			isInBeamTime = 1;
			break;
		}
	}
	return isInBeamTime;
}
