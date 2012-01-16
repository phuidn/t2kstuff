//cut functions
int inFGD1( TLorentzVector *FrontPosition );
int inFGD2( TLorentzVector *FrontPosition );
int noP0Dactivity(UInt_t Detectors );
int noTPC1(UInt_t Detectors);
int inTPC2(UInt_t Detectors );
int inTPC3(UInt_t Detectors );
int posCharge(Int_t NTPCs, TClonesArray* TPC);
int inBeamTime(TLorentzVector *FrontPosition, double beamTimeCut = 100.);
int inTimeBunch(TLorentzVector *FrontPosition, double beamTimeCut = 100.);

