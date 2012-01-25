// Example program.
// This program will loop over P0D hits and make histograms of the number
// of pulses.
//
// Once you have compiled this program you can execute it by doing something like
// ../Linux-x86_64/EventFilter.exe <some file>

// Include to get Event Loop.
#include <nd280EventLoop.hxx>

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
		ifstream ifile;
 		ifile.open("EventStripList.dat");
		if (ifile.fail()) {	
			std::cout << " EventStripList.dat file not found " << std::endl;
			exit(1);
		}
		int num, run, subrun;
		std::string code;
		while (!ifile.eof()) {
			ifile >> run >> subrun >> num;
			std::cout << "->Get event (" << run << "," << subrun << "," << num << ")" << std::endl;
		        EventList.push_back(num);
		}
		ifile.close();
		
        }

        bool operator () (ND::TND280Event& event) {
	    int EventID = event.GetEventId();
	    std::vector<int>::iterator vit = std::find(EventList.begin(), EventList.end(), EventID);
	    if (vit != EventList.end()) { std::cout << " Writing Event " << EventID << std::endl; return true; } 
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

