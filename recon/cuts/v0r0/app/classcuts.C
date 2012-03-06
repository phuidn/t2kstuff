#include "classcuts.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <TSystem.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TGlobalReconModule.hxx>
#include <TGlobalBaseObjects.hxx>
#include <TGRooTrackerVtx.hxx>
#include <TTruthVerticesModule.hxx>
#include <TTrueVertex.hxx>
#include <TTree.h>
#define ABS(x) (x>0?x:-x)
using namespace std;

int InFGD1 :: apply(){
	return ABS((*position)->X())<832.2 && ABS((*position)->Y()-55)<832.2 && ((*position)->Z()>123.45&&(*position)->Z()<446.95);
}

int InFGD2 :: apply(){
	return ABS((*position)->X())<832.2 && ABS((*position)->Y()-55)<832.2 && ((*position)->Z()>1481.45&&(*position)->Z()<1807.95);
}

int NoTPC1 :: apply(){	
	int i;
	char buffer[10];
	sprintf(buffer,"%d",*Detectors);
	for(i=0;i<strlen(buffer);i++)
	{
		if( buffer[i] == '1')
			return 0;
	}
	return 1;
}

int PosCharge :: apply(){
	Int_t charge(1), hits(0);
	for (int i=0; i<*NTPCs; i++)
		if( ((ND::TGlobalReconModule::TTPCObject*) (*TPC)->At(i))->NHits > 18 ){
			charge = charge && (((ND::TGlobalReconModule::TTPCObject*) (*TPC)->At(i))->Charge == 1);
			hits = 1;
		}
	return charge && hits;
}

int TPCHits :: apply(){
	int enoughhits(0), NHits;
	for (int i=0; i<*NTPCs; i++)
		NHits = ((ND::TGlobalReconModule::TTPCObject*) (*TPC)->At(i))->NHits;
		enoughhits =  NHits>min && NHits<max;
	return enoughhits;
}

int ProtonPull :: apply(){
	double pull = 0.;
	for (int i=0; i<*NTPCs; i++)
		pull += ((ND::TGlobalReconModule::TTPCObject*)(*TPC)->At(i))->PullProton/(double)*NTPCs;
	// pull seems to have a default value of 0 (presumably if there isn't enough data) so these are being cut
	return  ((pull > minPull) && (pull < maxPull) && (pull != 0));
}

int PionPull :: apply(){
	double pull = 0.;
	for (int i=0; i<*NTPCs; i++)
		if(((ND::TGlobalReconModule::TTPCObject*)(*TPC)->At(i))->NHits > 18)
			pull += ((ND::TGlobalReconModule::TTPCObject*)(*TPC)->At(i))->PullPion;
		else
			*NTPCs--;
	pull/=(double)*NTPCs;
	return  (pull > minPull);
}

int MuonPull :: apply(){
	double pull = 0.;
	for (int i=0; i<*NTPCs; i++)
		pull += ((ND::TGlobalReconModule::TTPCObject*)(*TPC)->At(i))->PullMuon/(double)*NTPCs;
	return  ((pull < minPull) || (pull > maxPull));
}

int TotNHits :: apply(){
	return (*NHits < threshold);
}

int DetectorOrder :: apply(){
	int i, startFGD1(0), startFGD2(0), TPC2(0), TPC3(0);
	char buffer[10];
	InFGD1 *inFGD1 = new InFGD1(FrontPosition);
	InFGD2 *inFGD2 = new InFGD2(FrontPosition);
	startFGD1 = inFGD1->apply();
	startFGD2 = inFGD2->apply();
	sprintf(buffer, "%d", *Detectors);
	for(i=0; i<strlen(buffer); i++){
		TPC2 += (buffer[i] == '2');
		TPC3 += (buffer[i] == '3');
	}
	delete inFGD1;
	delete inFGD2;
	return (startFGD1 && TPC2) || (startFGD2 && TPC3); 
}

int MinMomentum :: apply() {	
	return *momentum > min;
}

int CutECALs :: apply(){
	return *NECALs < 2;	
}
