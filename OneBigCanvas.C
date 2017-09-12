{

  TFile *f = TFile::Open("liquidlethplots.root","READ");
  
  double binedge[20]={1.0,
		      1.5,
		      2.0,
		      3.0,
		      4.0,
		      5.0,
		      5.5,
		      6.0,
		      7.0,
		      8.0,
		      9.0,
		      10.0,
		      11.0,
		      11.5,
		      12.0,
		      13.0,
		      14.0,
		      15.0,
		      17.5,
		      20.0};

  gStyle->SetOptStat(0);
  gStyle->SetLineWidth(2);
  
  TCanvas* c = new TCanvas("c","c",1000,1000);
  c->Divide(4,5);
  
  for (int i=0;i<19;i++)
    {
      char name[128];
      char bname[128];
      sprintf(name,"hf_%02.1f_%02.1f",binedge[i],binedge[i+1]);
      sprintf(bname,"hb_%02.1f_%02.1f",binedge[i],binedge[i+1]);
      TH1 *hftemp = (TH1*)gDirectory->FindObjectAny(name);
      TH1 *hbtemp = (TH1*)gDirectory->FindObjectAny(bname);
      
      hftemp->SetTitle("");
      hbtemp->SetTitle("");
      hftemp->SetTitle("");
      //hftemp->SetLineColor(kGreen+2);
      //hftemp->SetMarkerColor(kGreen+2);
      hbtemp->SetMarkerColor(kRed);
      hbtemp->SetLineColor(kRed);
      hftemp->GetXaxis()->CenterTitle(1);
      hftemp->GetXaxis()->SetTitleFont(42);
      hftemp->GetXaxis()->SetTitleSize(0.065);
      hftemp->GetXaxis()->SetLabelSize(0.045);
      hftemp->GetYaxis()->CenterTitle(1);
      hftemp->GetYaxis()->SetTitleFont(42);
      hftemp->GetYaxis()->SetTitleSize(0.065);
      hftemp->GetYaxis()->SetLabelSize(0.045);
      TGaxis::SetMaxDigits(3);
      c->cd(i+1);
      hftemp->Draw();
      gPad->SetLogx();
      gPad->SetTickx();
      gPad->SetTicky();
      hbtemp->Draw("same");

      char text[128];
      sprintf(text,"E_{inc} = %02.1f - %02.1f MeV",binedge[i],binedge[i+1]);
      TLatex *tex1 = new TLatex(0.56,0.5,text);
      tex1->SetNDC();
      tex1->SetTextFont(42);
      tex1->SetTextSize(0.07);
      tex1->SetTextColor(kRed);
      tex1->Draw();
      gPad->RedrawAxis();
    }
  //c->RedrawAxis();
  




}
