#define XyPlot_cxx
//#include "XyPlot.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TApplication.h>

TCanvas * makegraph()
{
	TCanvas	*c1 = new TCanvas();

	Double_t qsq[5]={60.,180.,300.,420.,540.};//X-axis!
	Double_t crosssection[5]={20.,50.,30.,20.,10.}; //y axis
	Double_t xer[5]={60.,60.,60.,60.,60.};
	Double_t staterr[5]={1.,1.,1.,1.,1.};
	Double_t fluxerr[5]={3.,3.,3.,3.,3.};

	TGraphErrors *gr1 = new TGraphErrors(5,qsq,crosssection,xer,staterr);
	gr1->SetMarkerStyle(1);
	TGraphErrors *gr2 = new TGraphErrors(5,qsq,crosssection,xer,fluxerr);
	gr2->SetMarkerStyle(1);

	TMultiGraph *g = new TMultiGraph();
	g->Add(gr1);
	g->Add(gr2);
	g->Draw("AP");
	g->SetTitle("Cross-Section Errors");
	g->GetXaxis()->SetTitle("Q^{2}");
	g->GetYaxis()->SetTitle("#frac{d#sigma}{dQ^{2}}");

	g->Draw("AP");
	return c1;
}	

	



int main(int argc, char *argv[])
{
	TApplication *a = new TApplication("app", &argc, argv);
	TCanvas *c1 = makegraph();
	a->Run();
	return 0;
}
