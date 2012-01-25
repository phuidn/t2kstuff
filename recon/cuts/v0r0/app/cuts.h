//cut functions
int inFGD1( TLorentzVector *FrontPosition );
int inFGD2( TLorentzVector *FrontPosition );
int noP0Dactivity(UInt_t Detectors );
int noTPC1(UInt_t Detectors);
int inTPC2(UInt_t Detectors );
int inTPC3(UInt_t Detectors );
int muonPull(Int_t NTPCs, TClonesArray* TPC, double minPull = -10., double maxPull = 5.);
int protonPull(Int_t NTPCs, TClonesArray* TPC, double minPull = -3., double maxPull = 15.);
int pionPull(Int_t NTPCs, TClonesArray* TPC, double minPull = 5.);
int TPCHits(Int_t NTPCs, TClonesArray* TPC, int min = 18, int max = 100);
int cutNHits(Int_t NHits, Int_t threshold = 105);
int posCharge(Int_t NTPCs, TClonesArray* TPC);
int cutMomentum(Double_t momentum, Double_t minVal = 75.);
int cutNECAL(int NECALs);
int cutNSMRD(int NSMRDs);
int inBeamTime(TLorentzVector *FrontPosition, double beamTimeCut = 100.);
int inTimeBunch(TLorentzVector *FrontPosition, double beamTimeCut = 100.);
int consecutiveDetectors(UInt_t Detectors);
