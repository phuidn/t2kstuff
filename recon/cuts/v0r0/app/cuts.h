//cut functions
int inFGD1( TLorentzVector *FrontPosition );
int inFGD2( TLorentzVector *FrontPosition );
int noPODactivity(UInt_t Detectors );
int noTPC1(UInt_t Detectors);
int inTPC2(UInt_t Detectors );
int inTPC3(UInt_t Detectors );
int inBeamTime(TLorentzVector *FrontPosition, double beamTimeCut = 100.);
int inTimeBunch(TLorentzVector *FrontPosition, double beamTimeCut = 100.);

