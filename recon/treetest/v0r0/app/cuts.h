//cut functions
int inFGD1( TLorentzVector *FrontPosition );
int inFGD2( TLorentzVector *FrontPosition );
int noPODactivity(ND::TGlobalReconModule::TGlobalPID *gTrack );
int noTPC1(ND::TGlobalReconModule::TGlobalPID *gTrack );
int inTPC2(ND::TGlobalReconModule::TGlobalPID *gTrack );
int inTPC3(ND::TGlobalReconModule::TGlobalPID *gTrack );
int inBeamTime(TLorentzVector *FrontPosition, double beamTimeCut = 100.);
