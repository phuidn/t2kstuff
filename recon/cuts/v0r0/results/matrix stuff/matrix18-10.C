{
//=========Macro generated from canvas: canvas/canvas
//=========  (Mon Feb  6 13:31:23 2012) by ROOT version5.28/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",820,271,640,640);
   canvas->SetHighLightColor(2);
   canvas->Range(-0.9932388,-1.226931,0.9932388,1.226931);
   TView *view = TView::CreateView(1);
   view->SetRange(0,0,0,1000,1800,2029.545);
   canvas->SetBorderSize(2);
   canvas->SetTheta(51.91176);
   canvas->SetPhi(31.69811);
   canvas->SetFrameFillColor(0);
   
   TH2D *hist = new TH2D("hist","Recon vs Truth Proton Momenta",5,0,1000,5,0,1800);
   hist->SetBinContent(8,358);
   hist->SetBinContent(9,386);
   hist->SetBinContent(10,23);
   hist->SetBinContent(11,8);
   hist->SetBinContent(12,7);
   hist->SetBinContent(13,10);
   hist->SetBinContent(15,340);
   hist->SetBinContent(16,1145);
   hist->SetBinContent(17,1841);
   hist->SetBinContent(18,669);
   hist->SetBinContent(19,96);
   hist->SetBinContent(20,118);
   hist->SetBinContent(22,134);
   hist->SetBinContent(23,134);
   hist->SetBinContent(24,415);
   hist->SetBinContent(25,1052);
   hist->SetBinContent(26,627);
   hist->SetBinContent(27,337);
   hist->SetBinContent(29,26);
   hist->SetBinContent(30,11);
   hist->SetBinContent(31,13);
   hist->SetBinContent(32,32);
   hist->SetBinContent(33,68);
   hist->SetBinContent(34,277);
   hist->SetBinContent(36,6);
   hist->SetBinContent(37,3);
   hist->SetBinContent(38,5);
   hist->SetBinContent(39,4);
   hist->SetBinContent(40,5);
   hist->SetBinContent(41,88);
   hist->SetBinContent(43,6);
   hist->SetBinContent(44,1);
   hist->SetBinContent(45,1);
   hist->SetBinContent(47,2);
   hist->SetBinContent(48,54);
   hist->SetEntries(8302);
   hist->SetContour(20);
   hist->SetContourLevel(0,3);
   hist->SetContourLevel(1,94.9);
   hist->SetContourLevel(2,186.8);
   hist->SetContourLevel(3,278.7);
   hist->SetContourLevel(4,370.6);
   hist->SetContourLevel(5,462.5);
   hist->SetContourLevel(6,554.4);
   hist->SetContourLevel(7,646.3);
   hist->SetContourLevel(8,738.2);
   hist->SetContourLevel(9,830.1);
   hist->SetContourLevel(10,922);
   hist->SetContourLevel(11,1013.9);
   hist->SetContourLevel(12,1105.8);
   hist->SetContourLevel(13,1197.7);
   hist->SetContourLevel(14,1289.6);
   hist->SetContourLevel(15,1381.5);
   hist->SetContourLevel(16,1473.4);
   hist->SetContourLevel(17,1565.3);
   hist->SetContourLevel(18,1657.2);
   hist->SetContourLevel(19,1749.1);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.755,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(2);
   ptstats->SetTextAlign(12);
   TText *text = ptstats->AddText("hist");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 8302   ");
   text = ptstats->AddText("Mean x =  498.1");
   text = ptstats->AddText("Mean y =  637.8");
   text = ptstats->AddText("RMS x =  232.7");
   text = ptstats->AddText("RMS y =  221.7");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   hist->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(hist->GetListOfFunctions());
   hist->Draw("LEGO");
   
   TPaveText *pt = new TPaveText(0.01,0.945,0.71,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   text = pt->AddText("Recon vs Truth Proton Momenta");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
