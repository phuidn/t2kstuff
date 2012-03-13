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
	// OUR DATA	
	Double_t qsq[5]={0.125,0.375,0.625,0.875,1.125};//X-axis!
	Double_t crosssection[5]={3.32,1.78,0.998,0.601,0.383};
	Double_t xer[5]={0.125,0.125,0.125,0.125,0.125};
	Double_t pfluxerr[5]={4.2,4.8,5.1,4.5,6.3};
	Double_t pmaerr[5]={4.9,11.3,16.2,21.0,20.0};
	Double_t pstaterr[5]={0.02,0.02,0.02,0.03,0.05};
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

	//SCIBOONE
/*	double sciqsq[6] = {0.24,0.294,0.347,0.401,0.454,0.508};
	double scicsc[6] = {1.26,0.59,0.35,0.17,0.13,0.05};
	double scixerh[6] = {0.0268,0.0268,0.0268,0.0268,0.0268,0.0268};
	double scixerl[6] = {0.0268,0.0268,0.0268,0.0268,0.0268,0.0268};
	double sciyerh[6] = {0.42,0.14,0.08,0.04,0.04,0.01};
	double sciyerl[6] = {0.56,0.19,0.1,0.05,0.08,0.03};
	TGraphAsymmErrors *scigr = new TGraphAsymmErrors(6,sciqsq,scicsc,scixerl,scixerh,sciyerl,sciyerh);*/

	//MINIBOONE	
	double minqsq[17] = {0.133,0.201,0.268,0.336,0.404,0.472,0.539,0.607,0.674,0.741,0.809,0.877,0.944,1.012,1.079,1.147,1.214};
	double mincsc[17] = {3.35,2.95,2.5,2.09,1.75,1.42,1.18,0.92,0.77,0.6,0.49,0.39,0.31,0.28,0.22,0.2,0.14};
	double minxer[17] = {0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338,0.0338};
	double minyer[17] = {0.35,0.4,0.42,0.35,0.25,0.23,0.24,0.22,0.22,0.21,0.21,0.22,0.22,0.21,0.14,0.12,0.1};
	TGraphErrors *mingr = new TGraphErrors(17,minqsq,mincsc,minxer,minyer);

	//BNL
	double bnlqsq[7] = {0.425,0.525,0.625,0.725,0.825,0.925,1.025};
	double bnlcsc[7] = {1.65,1.09,0.8,0.65,0.42,0.29,0.2};
	double bnlxer[7] = {0.05,0.05,0.05,0.05,0.05,0.05,0.05};
	double bnlyer[7] = {0.12,0.09,0.09,0.08,0.08,0.08,0.08};
	TGraphErrors *bnlgr = new TGraphErrors(7,bnlqsq,bnlcsc,bnlxer,bnlyer);
	
//	gr->Draw("AP");
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

	mingr->SetFillColor(kBlue);
	mingr->SetMarkerStyle(20);
	mingr->SetFillStyle(3001);
	mingr->Draw("samea3");
	
//	bnlgr->SetMarkerColor(kRed);
//	bnlgr->SetMarkerStyle(20);
//	bnlgr->Draw("sameP");


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
