{

  TFile *f = TFile::Open("LiGlLiquidPFNSOutput.root","READ");
  
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
  
  //new TCanvas;
  TH2D* hist= new TH2D("","",1500,0.01,15,100,0,0.5);
  hist->GetXaxis()->SetTitle("Outgoing Neutron Energy from T.O.F (MeV)");
  hist->GetXaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTitle("PFNS (1/MeV)");
  hist->GetXaxis()->SetTitleFont(42);
  hist->GetXaxis()->SetTitleSize(0.065);
  hist->GetXaxis()->SetLabelSize(0.045);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTitleFont(42);
  hist->GetYaxis()->SetTitleSize(0.065);
  hist->GetYaxis()->SetLabelSize(0.045);
  hist->GetYaxis()->SetTitleOffset(0.8);
  hist->GetXaxis()->SetTitleOffset(0.7);
  //TGaxis::SetMaxDigits(3);

  //hist->Draw();
  // char name[128];
  // sprintf(name,"LiGl_1.0-1.5");
  // TGraphErrors *myg = (TGraphErrors*)gDirectory->FindObjectAny(name);
  // myg->SetMarkerColor(kGreen+3);
  // myg->Draw("pcsame");

  // char name2[128];
  // sprintf(name2,"Liqd_1.0-1.5");
  // TGraphErrors *my2g = (TGraphErrors*)gDirectory->FindObjectAny(name2);
  // my2g->SetMarkerColor(kRed);
  // my2g->Draw("pcsame");
    
  
  TCanvas* c = new TCanvas("c","c",1000,1000);
  c->Divide(4,5);
  
  for (int i=0;i<19;i++)
    {
      char name[128];
      char bname[128];
      sprintf(name,"LiGl_%02.1f-%02.1f",binedge[i],binedge[i+1]);
      sprintf(bname,"Liqd_%02.1f-%02.1f",binedge[i],binedge[i+1]);
      TGraphErrors *hftemp = (TGraphErrors*)gDirectory->FindObjectAny(name);
      TGraphErrors *hbtemp = (TGraphErrors*)gDirectory->FindObjectAny(bname);
      
      hftemp->SetMarkerColor();
      hftemp->SetMarkerSize(0.4);
      hbtemp->SetMarkerColor(kRed);
      hbtemp->SetMarkerSize(0.4);

      c->cd(i+1);
      hist->Draw();
      gPad->SetLogx();
      gPad->SetTickx();
      gPad->SetTicky();
      hftemp->Draw("pcsame");
      hbtemp->Draw("pcsame");

      char text[128];
      sprintf(text,"E_{inc} = %02.1f - %02.1f MeV",binedge[i],binedge[i+1]);
      TLatex *tex1 = new TLatex(0.31,0.8,text);
      tex1->SetNDC();
      tex1->SetTextFont(42);
      tex1->SetTextSize(0.08);
      tex1->SetTextColor(kRed);
      tex1->Draw();
      gPad->RedrawAxis();
    }
  // //c->RedrawAxis();
  




}
