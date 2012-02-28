{
//=========Macro generated from canvas: canvas/canvas
//=========  (Tue Feb 28 14:25:48 2012) by ROOT version5.28/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",332,21,640,576);
   canvas->SetHighLightColor(2);
   canvas->Range(-74.62687,-87.75251,671.6418,1025.773);
   canvas->SetBorderSize(2);
   canvas->SetFrameFillColor(0);
   Double_t xAxis1[6] = {0, 119.403, 238.806, 358.209, 477.6119, 597.0149}; 
   
   TH1D *datatruth = new TH1D("datatruth","Title",5, xAxis1);
   datatruth->SetBinContent(1,204);
   datatruth->SetBinContent(2,872);
   datatruth->SetBinContent(3,728);
   datatruth->SetBinContent(4,277);
   datatruth->SetBinContent(5,64);
   datatruth->SetBinContent(6,28);
   datatruth->SetEntries(2173);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.835,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(2);
   ptstats->SetTextAlign(12);
   TText *text = ptstats->AddText("datatruth");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 2173   ");
   text = ptstats->AddText("Mean  =  249.4");
   text = ptstats->AddText("RMS   =  104.6");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   datatruth->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(datatruth->GetListOfFunctions());
   datatruth->Draw("");
   Double_t xAxis2[6] = {0, 119.403, 238.806, 358.209, 477.6119, 597.0149}; 
   
   TH1D *unfoldingresult = new TH1D("unfoldingresult","Title",5, xAxis2);
   unfoldingresult->SetBinContent(1,287.6875);
   unfoldingresult->SetBinContent(2,583.491);
   unfoldingresult->SetBinContent(3,587.6803);
   unfoldingresult->SetBinContent(4,362.2598);
   unfoldingresult->SetBinContent(5,197.1353);
   unfoldingresult->SetBinContent(6,59);
   unfoldingresult->SetBinError(1,8.493251);
   unfoldingresult->SetBinError(2,8.742933);
   unfoldingresult->SetBinError(3,8.572818);
   unfoldingresult->SetBinError(4,7.227936);
   unfoldingresult->SetBinError(5,4.542769);
   unfoldingresult->SetBinError(6,7.681146);
   unfoldingresult->SetEntries(2183);
   unfoldingresult->Draw("E1same");
   
   TPaveText *pt = new TPaveText(0.01,0.945,0.1227673,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   text = pt->AddText("Title");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
