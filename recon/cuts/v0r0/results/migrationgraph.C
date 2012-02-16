#define XyPlot_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TApplication.h>
#include <THStack.h>

using namespace std;


void makemygraph()
{


	Float_t bins[] = {0,0.15, 0.28, 0.40, 0.70, 4};
	Double_t errors[] = {45770,59622,55358,95147,52519};
	
	TH1D *graph = new TH1D("graph","Comparison of truth and corrected reconstructed energies",5,bins);
	graph->SetBinContent(1,765129);
	graph->SetBinContent(2,1298340);
	graph->SetBinContent(3,1119272);
	graph->SetBinContent(4,3306472);
	graph->SetBinContent(5,1007428);
	graph->SetLineColor(kRed);
	graph->SetError(errors);
	graph->Draw("E1");
	
	//For hist plot
	TH1D *hist = new TH1D("hist","Comparison of truth and corrected reconstructed energies",5,bins);
	hist->SetBinContent(1,769378);
	hist->SetBinContent(2,1147222);
	hist->SetBinContent(3,1494948);
	hist->SetBinContent(4,3069298);
	hist->SetBinContent(5,1015798);
	hist->SetLineColor(kGreen);
	hist->Draw("same");

}

int main(int argc, char *argv[])
{
	TApplication *a = new TApplication("app", &argc, argv);
	TCanvas *canvas = new TCanvas("canvas", "canvas", 640, 640);
	makemygraph();
	a->Run();
	return 0;
}

