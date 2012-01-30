
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

int inFGD1( TLorentzVector *FrontPosition )
{

	if(ABS(FrontPosition->X())<832.2 && ABS(FrontPosition->Y()-55)<832.2 && (FrontPosition->Z()>123.45&&FrontPosition->Z()<446.95))
			return 1;
	else
			return 0;
}

int inFGD2( TLorentzVector *FrontPosition )
{

	if(ABS(FrontPosition->X())<832.2 && ABS(FrontPosition->Y()-55)<832.2 && (FrontPosition->Z()>1481.45&&FrontPosition->Z()<1807.95) )
			return 1;
	else
			return 0;
}

int noP0Dactivity(UInt_t Detectors )
{ //returns 1 if NO POD activity!
	int i;
	char buffer[10];
	sprintf(buffer,"%d",Detectors);

	for(i=0;i<strlen(buffer);i++)
	{
		if( buffer[i] == '6')
			return 0;
	}
	return 1;
	//detectors has the number 6 in it if goes through POD
	// (see table 1 on "USing the Recon Tree")
}

int noTPC1(UInt_t Detectors)
{ //returns 1 if NO tpc activity!
	int i;
	char buffer[10];
	sprintf(buffer,"%d",Detectors);

	for(i=0;i<strlen(buffer);i++)
	{
		if( buffer[i] == '1')
			return 0;
	}
	return 1;
	//detectors has the number 1 in it if goes through tpc1
	// (see table 1 on "USing the Recon Tree")
}

int posCharge(Int_t NTPCs, TClonesArray* TPC)
{
	//return 1 if all tpcs agree an charge 1 (and if it has any tpc tracks at all)
	if (!NTPCs)
		return 0;
	else{
		Int_t charge(1), hits(0);
		for (int i=0; i<NTPCs; i++)
			if( ((ND::TGlobalReconModule::TTPCObject*) TPC->At(i))->NHits > 18 ){
				charge = charge && (((ND::TGlobalReconModule::TTPCObject*) TPC->At(i))->Charge == 1);
				hits = 1;
			}
		return charge && hits;
	}
}	

int TPCHits(Int_t NTPCs, TClonesArray* TPC, int min = 18, int max = 100){
	int enoughhits(0), NHits;
	for (int i=0; i<NTPCs; i++)
		NHits = ((ND::TGlobalReconModule::TTPCObject*) TPC->At(i))->NHits;
		enoughhits =  NHits>min && NHits<max;
	return enoughhits;
}

int protonPull(Int_t NTPCs, TClonesArray* TPC, double minPull = -3., double maxPull = 15.)
{
//returns true if the average proton pull is between the threshold values, change these values to better ones once we have histograms
	double pull = 0.;
	if (!NTPCs)
		return 0;
	else{
		for (int i=0; i<NTPCs; i++)
			pull += ((ND::TGlobalReconModule::TTPCObject*)TPC->At(i))->PullProton/(double)NTPCs;
		pull = (double) pull;
	}
	// pull seems to have a default value of 0 (presumably if there isn't enough data) so these are being cut
	return  ((pull > minPull) && (pull < maxPull) && (pull != 0));
}

int pionPull(Int_t NTPCs, TClonesArray* TPC, double minPull = 5.)
{
//returns true if the average proton pull is between the threshold values, change these values to better ones once we have histograms
	double pull = 0.;
	if (!NTPCs)
		return 0;
	else{
		for (int i=0; i<NTPCs; i++)
			pull += ((ND::TGlobalReconModule::TTPCObject*)TPC->At(i))->PullPion/(double)NTPCs;
		pull = (double) pull;
	}
	// pull seems to have a default value of 0 (presumably if there isn't enough data) so these are being cut
	return  (pull > minPull) ;
}

int muonPull(Int_t NTPCs, TClonesArray* TPC, double minPull = -10., double maxPull = 5.)
{
	double pull = 0.;
	if(!NTPCs)
		return 0;
	else{ 
	for (int i=0; i<NTPCs; i++)
			pull += ((ND::TGlobalReconModule::TTPCObject*) TPC->At(i))->PullMuon;
		pull/=NTPCs;
	}
	return ((pull < minPull) || (pull > maxPull));
}

int cutNHits(Int_t NHits, Int_t threshold = 105)
{
	//cuts anything above NHits threshold, this is where other interactions peak but NCQES doesn't
	return (NHits < threshold);
}

int inTPC2(UInt_t Detectors )
{ //returns 1 if TPC2 activity!
	int i;
	char buffer[10];
	sprintf(buffer,"%d",Detectors);

	for(i=0;i<strlen(buffer);i++)
	{
		if( buffer[i] == '2')
			return 0;
	}
	return 1;
	//detectors has the number 2 in it if goes through tpc2
	// (see table 1 on "USing the Recon Tree")
}

int inTPC3(UInt_t Detectors)
{ //returns 1 if TPC3 activity!
	int i;
	char buffer[10];
	sprintf(buffer,"%d",Detectors);

	for(i=0;i<strlen(buffer);i++)
	{
		if( buffer[i] == '3')
			return 0;
	}
	return 1;
	//detectors has the number 3 in it if goes through tpc3
	// (see table 1 on "USing the Recon Tree")
}

int consecutiveDetectors(UInt_t Detectors)
{
//returns 1 if a particle travels through an FGD and the proceeding TPC (or no FGDs but another cut will take care of this)
	int i, FGD1(0), FGD2(0), TPC2(0), TPC3(0);
	char buffer[10];
	sprintf(buffer, "%d", Detectors);
	for(i=0; i<strlen(buffer); i++){
		FGD1 += (buffer[i] == '4');
		FGD2 += (buffer[i] == '5');
		TPC2 += (buffer[i] == '2');
		TPC3 += (buffer[i] == '3');
	}
	return ((FGD1 && TPC2) || !FGD1) && ((FGD2 && TPC3) || !FGD2);
}

int cutMomentum(Double_t momentum, Double_t minVal = 75.){
	return momentum > minVal;
}

int cutNECAL(int NECALs){
	return NECALs < 2;
}

int cutNSMRD(int NSMRDs){
	return NSMRDs < 1;
}

int inBeamTime(TLorentzVector *FrontPosition, double beamTimeCut = 100.) {
//returns 1 if the particle corresponded with the beam, 0 if it didn't
        int nBunches = 8;
        bool isInBeamTime(0);
		double vertexTime = FrontPosition->T();
		const double beamTimeArray[8] = {2752.,3333.,3915.,4498.,5080.,5661.,6244.,6826.};
        for (int i = 0; i < nBunches; ++i) {

                if((vertexTime > beamTimeArray[i] - beamTimeCut) && (vertexTime < beamTimeArray[i] + beamTimeCut)) {
                        isInBeamTime = 1;
                        break;
                }
        }
        return isInBeamTime;
}

int inTimeBunch(TLorentzVector *FrontPosition, double beamTimeCut = 100.) {
//returns which time bunch the particle was detected in (0-7) or -1 if it wasn't in any of them
        int nBunches = 8;
        int timeBunch(-1);
		double vertexTime = FrontPosition->T();
		const double beamTimeArray[8] = {2752.,3333.,3915.,4498.,5080.,5661.,6244.,6826.};
        for (int i = 0; i < nBunches; ++i) {

                if((vertexTime > beamTimeArray[i] - beamTimeCut) && (vertexTime < beamTimeArray[i] + beamTimeCut)) {
                        timeBunch = i;
                        break;
                }
        }
        return timeBunch;
}
