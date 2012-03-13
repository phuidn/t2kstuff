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
#include <math.h>

TCanvas * makegraph()
{
	TCanvas	*c1 = new TCanvas();

	Double_t qsq[5]={0.125,0.375,0.625,0.875,1.125};//X-axis!
	Double_t crosssection[5]={3.32,1.78,0.998,0.601,0.383};
	Double_t xer[5]={0.125,0.125,0.125,0.125,0.125};
	Double_t pfluxerr[5]={4.2,4.8,5.1,4.5,6.3};
	Double_t pmaerr[5]={4.9,11.3,16.2,21.0,20.0};
	Double_t pstaterr[5]={0.02,0.016,0.02,0.03,0.04};
	Double_t fluxerr[5];
	Double_t maerr[5];
	Double_t staterr[5];
	for(int i=0; i<5; i++) fluxerr[i]=pfluxerr[i]*crosssection[i]*0.01;
	for(int i=0; i<5; i++) maerr[i]=pmaerr[i]*crosssection[i]*0.01;
	for(int i=0; i<5; i++) staterr[i]=pstaterr[i]*crosssection[i];

	//sum error in quadrature
	Double_t toterr[5];
	for(int i=0; i<5; i++) toterr[i]=sqrt(	fluxerr[i]*fluxerr[i] /*+ staterr[i]*staterr[i]*/ + maerr[i]*maerr[i]	);

	TGraphErrors *gr = new TGraphErrors(5,qsq,crosssection,xer,toterr);
	gr->Draw("AP");

gr->SetFillColor(2);
   gr->SetFillStyle(3001);
	gr->GetXaxis()->SetTitle("Q^{2}");
	gr->GetYaxis()->SetTitle("#frac{d#sigma}{dQ^{2}}");
   gr->Draw("a2");
//   gr->Draw("p");

	TGraphErrors *gstaterr = new TGraphErrors(5,qsq,crosssection,xer,staterr);
	gstaterr->SetFillColor(4);
	gstaterr->SetFillStyle(3001);
	gstaterr->Draw("p");




//	TGraphErrors *gr1 = new TGraphErrors(5,qsq,crosssection,xer,staterr);
//	gr1->SetMarkerStyle(1);
//	TGraphErrors *gr2 = new TGraphErrors(5,qsq,crosssection,xer,fluxerr);
//	gr2->SetMarkerStyle(1);
//	TGraphErrors *gr3 = new TGraphErrors(5,qsq,crosssection,xer,maerr);
//	gr3->SetMarkerStyle(1);
//
//	TMultiGraph *g = new TMultiGraph();
//	g->Add(gr1);
//	g->Add(gr2);
//	g->Draw("AP");
//	g->SetTitle("Cross-Section Errors");
//	g->GetXaxis()->SetTitle("Q^{2}");
//	g->GetYaxis()->SetTitle("#frac{d#sigma}{dQ^{2}}");
//
//	g->Draw("AP");
	return c1;
}	

	



int main(int argc, char *argv[])
{
	TApplication *a = new TApplication("app", &argc, argv);
	TCanvas *c1 = makegraph();
	a->Run();
	return 0;
}
