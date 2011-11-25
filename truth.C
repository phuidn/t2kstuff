// Prototype:
	//	Should filter:
	// 					only protons
	//					in fdg
	//					final state

	// and do an MOMENTUM!! histogram.

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

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
#include <TH1D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include "TGRooTrackerVtx.hxx"

void SetupROOT();
void analysis();

int main(int argc, char *argv[])
{
    TApplication *a = new TApplication("app", &argc, argv);
	analysis();
    a->Run();
    return 0;
}



//---------------------------------------------------------------------------//
//Main Method
//---------------------------------------------------------------------------//
void analysis(){

	//Setup variables needed for plotting n shit
	Int_t	nbinsx	=	100;
	Double_t	xmin	=	0.0;
	Double_t	xmax	=	50.0;
	Int_t	nbinsy	=	100;
	Double_t	ymin	=	0.0;
	Double_t	ymax	=	50.0;

	Double_t	stdHepPx;
	Double_t	neumom[4];//using these for px py pz and ptot for neutrinos
	Double_t	promom[4];//and protons, need to record to get angle
	Double_t	angle;

	int proton=0;
	int neutrino=0;

	//Make a canvas
	Double_t w = 800;
	Double_t h = 600;
	TCanvas * c1 = new TCanvas("c", "c", w, h);
	//c->SetWindowSize(w + (w - c->GetWw()), h + (h - c->GetWh()));

	// Set up ROOT as we require.
	SetupROOT();

	// Get list of files to run over. 
	TString fileName("prod4_analysis.list");
	std::ifstream inputFile(fileName.Data(), std::ios::in);

	// Declare a TChain for the GRooTrackerVtx module
	TChain *gGenVtx = new TChain("TruthDir/GRooTrackerVtx");

	// Check if the file exists.
	if (!inputFile.is_open()){
	std::cout << "ERROR: File prod4 files not found!" << std::endl;
		std::cout << " - This file should contain a list of all data files to be processed." << std::endl;
		return;
	}
	else{
		std::string curFileName;

		// Add the input files to the TChains.
		while(getline(inputFile,curFileName)){
			gGenVtx->Add(curFileName.c_str());
		}
	}

	std::cout << "Got input file(s)." << std::endl;

	//Setup access to the TruthDir Tree
	int NVtx(0);  // This variable counts the number of vertices stored per event
        // Declare a TClonesArray to hold objects of type ND::GRooTrackerVtx
 	TClonesArray *VtxArray = new TClonesArray("ND::GRooTrackerVtx",50);
        // Associate the right branch in the TTree to the right local variable
	gGenVtx->SetBranchAddress("Vtx",&VtxArray);
        gGenVtx->SetBranchAddress("NVtx",&NVtx);

	//Setup section!!
	TH1D *myplot = new TH1D("myplot","Angle between final state proton and initial muon neutrinos for QES detected in FGDs",100,0.0,3.5);
	//end setup


	// Loop over the entries in the TChain.
	for(unsigned int i = 0; i < gGenVtx->GetEntries() ; ++i)
	//for(unsigned int i = 0; i < 10000 ; ++i)
	{
		if((i+1)%10000 == 0) std::cout << "Processing event: " << (i+1) << std::endl;

		// Get an entry for the TruthDir/GRooTrackVtx tree
		gGenVtx->GetEntry(i);	
		ND::GRooTrackerVtx *vtx = NULL;
		//DEBUG ONLY
		//std::cout << "NVtx = " << NVtx << std::endl;

		// Loop over vertex array
		for (int j=0; j<NVtx; j++)
		{
			// Get a specific vertex from the TClonesArray
			vtx = (ND::GRooTrackerVtx*)VtxArray->At(j);
			if (vtx->EvtCode->String().Contains("QES"))
			{	/*Must be in either FDG!*/
				if(	vtx->EvtVtx[0]>-832.2 && vtx->EvtVtx[0]<832.2
				&&	vtx->EvtVtx[1]>-777.2 && vtx->EvtVtx[1]<887.2
				&& (	vtx->EvtVtx[2]>123.45 && vtx->EvtVtx[2]<446.95
				||		vtx->EvtVtx[2]>1481.45 && vtx->EvtVtx[2]<1807.95))
				{
					for (int k=0 ; k < vtx->StdHepN ; k++)
					{	/*only if a final state proton*/
						if(vtx->StdHepPdg[k] == 2212 && vtx->StdHepStatus[k] == 1)
						{
							promom[0] = vtx->StdHepP4[k][0];
							promom[1] = vtx->StdHepP4[k][1];
							promom[2] = vtx->StdHepP4[k][2];
							promom[3] = sqrt( promom[0]*promom[0]+promom[1]*promom[1]+promom[2]*promom[2] );
							proton=1;
						}
						//only if final state muon neutrino
						if(vtx->StdHepPdg[k] == 14 && vtx->StdHepStatus[k] == 0)
						{
							neumom[0] = vtx->StdHepP4[k][0];
							neumom[1] = vtx->StdHepP4[k][1];
							neumom[2] = vtx->StdHepP4[k][2];
							neumom[3] = sqrt( neumom[0]*neumom[0]+neumom[1]*neumom[1]+neumom[2]*neumom[2] );
							neutrino=1;	
						}
						if(proton && neutrino)
						{
							angle=acos( (promom[0]*neumom[0]+promom[1]*neumom[1]+promom[2]*neumom[2]) / (promom[3]*neumom[3])  );
							myplot->Fill(angle);
						}
					}
					proton=0;
					neutrino=0;
				}
			}	
		}

	} // End loop over events

	myplot->GetXaxis()->SetTitle("z");
	myplot->GetYaxis()->SetTitle("y");
	myplot->Draw();
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
