// Example program.
// This program will loop over P0D hits and make histograms of the number
// of pulses.
//
// Once you have compiled this program you can execute it by doing something like
// ../Linux-x86_64/checkP0DHits.exe <some file>
//   ie
// ../Linux-x86_64/checkP0DHits.exe /<path to file>/oa_nt_beam_90211000-0100_y6pjkx5v5p77_reco_000_prod004basket201011water.root

// Include to get Event Loop.
#include <nd280EventLoop.hxx>
#include "TG4PrimaryVertex.hxx"

// Includes for ROOT classes
#include <TH1F.h>
#include <TPad.h>
#include <vector>
#include <iostream>
#include <fstream>

class TMyEventLoop: public ND::TND280EventLoopFunction {
    public:
        TMyEventLoop() {}
        virtual ~TMyEventLoop() {}

        void Initialize() {
/*
		ifstream ifile;
 		ifile.open("EventStripList.dat");
		if (ifile.fail()) {	
			std::cout << " EventStripList.dat file not found " << std::endl;
			exit(1);
		}
		int num, run, subrun;
		while (!ifile.eof()) {
			ifile >> run >> subrun >> num;
		        EventList.push_back(num);
		}
		ifile.close();
*/
		
        }

        bool operator () (ND::TND280Event& event) {
	    std::cout << "Event " << event.GetEventId() << std::endl;
	    ND::THandle<ND::TG4PrimaryVertexContainer> g4PrimVertex00 = event.Get<ND::TG4PrimaryVertexContainer>("truth/G4PrimVertex00");
	    int i=0;
	    for(std::vector<ND::TG4PrimaryVertex>::const_iterator vertexIter = g4PrimVertex00->begin(); vertexIter != g4PrimVertex00->end(); ++vertexIter) {
              i++;
              TLorentzVector vertexPosition = vertexIter->GetPosition();
              std::string Generator = vertexIter->GetGeneratorName();
              std::string ReactionCode = vertexIter->GetReaction();
	      std::cout << "Vertex " << i << " : " << ReactionCode.c_str() << " Gen " << Generator.c_str() << std::endl;
            }
 	    std::cout << "====" << std::endl;
	    return false;
        }

        void Finalize(ND::TND280Output * const file) {
        }

    private:
	std::vector<int>EventList;
};

int main(int argc, char **argv) {
    TMyEventLoop userCode;
    nd280EventLoop(argc,argv,userCode);
}

