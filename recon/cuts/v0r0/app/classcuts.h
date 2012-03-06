#include <TROOT.h>
#include <TSystem.h>
#include <TLorentzVector.h>
#include <string>
#include <TClonesArray.h>
class Cut {
	public: 
		virtual int apply() = 0;	
		std::string name;
};

class InFGD1 : public Cut {
	public: 
		InFGD1( TLorentzVector **FrontPosition ){
			position = FrontPosition;
			name = "InFGD1";
		}
		virtual int apply();
	private:
		TLorentzVector **position;
};

class InFGD2 : public Cut{
	public:
		InFGD2(TLorentzVector **FrontPosition ){
			position = FrontPosition;
			name = "InFGD2";
		}
		virtual int apply();
	private:
		TLorentzVector **position;
};

class NoTPC1 : public Cut {
	public:
		NoTPC1(UInt_t *Detectors){
			this->Detectors = Detectors;
			name = "NoTPC1";
		}
		virtual int apply();
	private:
		UInt_t *Detectors;
};

class PosCharge : public Cut {
	public:
		PosCharge( Int_t *NTPCs, TClonesArray **TPC){
			this->TPC = TPC;
			this->NTPCs = NTPCs;
				name = "PosCharge";
		}	
		virtual int apply();
	private:
		TClonesArray **TPC;
		Int_t *NTPCs;
};

class TPCHits : public Cut {
	public:
		TPCHits(Int_t *NTPCs, TClonesArray **TPC, int min = 18, int max = 100){
			this->NTPCs = NTPCs;
			this->TPC = TPC;
			this->min = min;
			this->max = max;
			name = "TPCHits";
		}
		virtual int apply();
	private:
		Int_t *NTPCs;
		TClonesArray **TPC;
		int min;
		int max;
};

class ProtonPull : public Cut {
	public:
		ProtonPull(Int_t *NTPCs, TClonesArray** TPC, double minPull = -1.5, double maxPull = 15.){
			this->NTPCs = NTPCs;
			this->TPC = TPC;
			this-> minPull = minPull;
			this->maxPull = maxPull;
			name = "ProtonPull";
		}
		virtual int apply();
	private:
		Int_t *NTPCs;
		TClonesArray **TPC;
		double minPull;
		double maxPull;
};

class PionPull : public Cut {
	public:
		PionPull(Int_t *NTPCs, TClonesArray** TPC, double minPull = 5.){
			this->NTPCs = NTPCs;
			this->TPC = TPC;
			this-> minPull = minPull;
			name = "PionPull";
		}
		virtual int apply();
	private:	
		Int_t *NTPCs;
		TClonesArray **TPC;
		double minPull;
};


class MuonPull : public Cut {
	public:
		MuonPull(Int_t *NTPCs, TClonesArray** TPC, double minPull = -10., double maxPull = 5.){
			this->NTPCs = NTPCs;
			this->TPC = TPC;
			this-> minPull = minPull;
			this->maxPull = maxPull;
			name = "MuonPull";
		}
		virtual int apply();
	private:
		Int_t *NTPCs;
		TClonesArray **TPC;
		double minPull;
		double maxPull;
};

class TotNHits : public Cut {
	public:
		TotNHits(Int_t *NHits, Int_t threshold = 105){
			this->NHits = NHits;
			this->threshold = threshold;
			name = "TotNHits";
		}
		virtual int apply();
	private:
		Int_t* NHits;
		Int_t threshold;
};

class DetectorOrder : public Cut {
	public:
		DetectorOrder(UInt_t *Detectors, TLorentzVector **FrontPosition){
			this->Detectors = Detectors;
			this->FrontPosition = FrontPosition;
			name = "DetectorOrder";
		}
		virtual int apply();
	private:
		UInt_t *Detectors;
		TLorentzVector **FrontPosition;
};

class MinMomentum : public Cut {
	public:
		MinMomentum(Double_t *momentum, Double_t min = 75.){
			this->momentum = momentum;
			this->min = min;
			name = "MinMomentum";
		}
		virtual int apply();
	private:
		Double_t *momentum;
		Double_t min;
};

class CutECALs : public Cut {
	public:
		CutECALs(int *NECALs){
			this->NECALs = NECALs;
			name = "CutECALs";
		}
		virtual int apply();
	private:
		int *NECALs;
};
