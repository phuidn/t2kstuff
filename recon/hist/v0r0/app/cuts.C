
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

int noPODactivity(UInt_t Detectors )
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
