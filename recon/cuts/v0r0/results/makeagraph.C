//Will plot efficiency as a function of cut
/* ************************ To Change:

   	size = <sizeyouwant>
	and change values of efficiency and purity


	then save, run make then ./run

   */

#define XyPlot_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TApplication.h>


void makemygraph()
{
	const int size=7;
	int i;
	//Define the points
	Double_t cutnumber[size];
	for(i=0;i<size;i++) cutnumber[i] = i;
	//cutnumber=0 should be uncut data(or initial cut data)

	Double_t efficiency[size]={0.849,0.849,0.4450,0.348,0.317,0.276,0.246};
	Double_t purity[size]={0.101,0.101,0.248,0.229,0.395,0.421,0.430};
	Double_t effpur[size];
	
	for(i=0;i<size;i++) effpur[i] = 4*efficiency[i]*purity[i];


	TMultiGraph *mg = new TMultiGraph();
	TCanvas *canvas = new TCanvas("canvas","Efficiency & Purity as a function of cuts.",200,100,700,500);

	TGraph *effgr = new TGraph(size,cutnumber,efficiency);
	effgr->SetLineColor(kRed);

	TGraph *purgr = new TGraph(size,cutnumber,purity);
	purgr->SetLineColor(kBlue);

	TGraph *epgr = new TGraph(size,cutnumber,effpur);
	epgr->SetLineColor(kGreen);

	mg->Add(effgr);
	mg->Add(purgr);
	mg->Add(epgr);

	mg->Draw("ALP");
	mg->GetXaxis()->SetTitle("Cuts");
	mg->GetYaxis()->SetTitle("Efficiency, Purity");
	mg->Draw("ALP");


}

int main(int argc, char *argv[])
{
	TApplication *a = new TApplication("app", &argc, argv);
	makemygraph();
	a->Run();
	return 0;
}

