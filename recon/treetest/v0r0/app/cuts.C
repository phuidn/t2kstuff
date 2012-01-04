
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

int noPODactivity(ND::TGlobalReconModule::TGlobalPID *gTrack )
{ //returns 1 if NO POD activity!
	//trying to filter using Detector numbers!
	UInt_t Detectors = gTrack->Detectors;
	int i;
	char buffer[10];
	sprintf(buffer,"%d",Detectors);

	//std::cout << "detectors= " << Detectors;
	//std::cout << "\tbuffer= " << buffer;

	for(i=0;i<strlen(buffer);i++)
	{
		if( buffer[i] == '6')
		{
			//std::cout<<"\tPOD noooo! reject!"<<std::endl;
			return 0;
		}
	}
	//std::cout << std::endl;
	return 1;
	//i think this works but please check!
	//detectors has the number 6 in it if goes through POD
	// (see table 1 on "USing the Recon Tree")
}

int noTPC1(ND::TGlobalReconModule::TGlobalPID *gTrack )
{ //returns 1 if NO tpc activity!
	//trying to filter using Detector numbers!
	UInt_t Detectors = gTrack->Detectors;
	int i;
	char buffer[10];
	sprintf(buffer,"%d",Detectors);

	//std::cout << "detectors= " << Detectors;
	//std::cout << "\tbuffer= " << buffer;

	for(i=0;i<strlen(buffer);i++)
	{
		if( buffer[i] == '1')
		{
			//std::cout<<"\tTPC1 noooo! reject!"<<std::endl;
			return 0;
		}
	}
	//std::cout << std::endl;
	return 1;
	//i think this works but please check!
	//detectors has the number 1 in it if goes through tpc1
	// (see table 1 on "USing the Recon Tree")
}

int inTPC2(ND::TGlobalReconModule::TGlobalPID *gTrack )
{ //returns 1 if TPC2 activity!
	//trying to filter using Detector numbers!
	UInt_t Detectors = gTrack->Detectors;
	int i;
	char buffer[10];
	sprintf(buffer,"%d",Detectors);

	//std::cout << "detectors= " << Detectors;
	//std::cout << "\tbuffer= " << buffer;

	for(i=0;i<strlen(buffer);i++)
	{
		if( buffer[i] == '2')
		{
			//std::cout<<"\tWent through tpc2, keep!"<<std::endl;
			return 0;
		}
	}
	//std::cout << std::endl;
	return 1;
	//i think this works but please check!
	//detectors has the number 2 in it if goes through tpc2
	// (see table 1 on "USing the Recon Tree")
}

int inTPC3(ND::TGlobalReconModule::TGlobalPID *gTrack )
{ //returns 1 if TPC3 activity!
	//trying to filter using Detector numbers!
	UInt_t Detectors = gTrack->Detectors;
	int i;
	char buffer[10];
	sprintf(buffer,"%d",Detectors);

	//std::cout << "detectors= " << Detectors;//just checking if converted
	//std::cout << "\tbuffer= " << buffer;	// from UInt_t to char string proper

	for(i=0;i<strlen(buffer);i++)
	{
		if( buffer[i] == '3')
		{
			//std::cout<<"\tWent through tpc3, keep!"<<std::endl;
			return 0;
		}
	}
	//std::cout << std::endl;
	return 1;
	//i think this works but please check!
	//detectors has the number 3 in it if goes through tpc3
	// (see table 1 on "USing the Recon Tree")
}


int inBeamTime(TLorentzVector *FrontPosition, double beamTimeCut = 100.) {

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

