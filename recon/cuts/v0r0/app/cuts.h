//cut functions
int inFGD1( TLorentzVector *FrontPosition );
int inFGD2( TLorentzVector *FrontPosition );
int noP0Dactivity(UInt_t Detectors );
int noTPC1(UInt_t Detectors);
int inTPC2(UInt_t Detectors );
int inTPC3(UInt_t Detectors );
int muonPull(Int_t NTPCs, TClonesArray* TPC, double minPull = -0.5, double maxPull = 0.5);
int protonPull(Int_t NTPCs, TClonesArray* TPC, double minPull = -0.5, double maxPull = 0.5);
int cutNHits(Int_t NHits, Int_t threshold = 105);
int posCharge(Int_t NTPCs, TClonesArray* TPC);
int inBeamTime(TLorentzVector *FrontPosition, double beamTimeCut = 100.);
int inTimeBunch(TLorentzVector *FrontPosition, double beamTimeCut = 100.);
int consecutiveDetectors(UInt_t Detectors);
