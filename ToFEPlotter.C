// TGraph* cielo;
// TGraph* maxwellian;
// TH1* hb (0);
// TH1* hf (0);

//====================================================================

void scaleGraph (TGraphErrors* g, double scale) {

//--------------------------------------------------------------------

  int nPoints = g->GetN();
  for (int i=0; i<nPoints; ++i) {
    g->GetY()[i]  *= scale;
    g->GetEY()[i] *= scale;
  }

  return;
}

//====================================================================

void ToFEPlotter (void) {

//--------------------------------------------------------------------

//  gStyle = gStylePublication;

  TFile *f = new TFile("AlmostAll.root","READ");
 
  f->cd("histos/DoubleCoinc");
  //dc1_5_leth_poly_t00_ppac01_ligl01->Draw();
  
  char histotitle[128];
  char histoname[128];
  char histname[128];
  char histtitle[128];
  
  TH1D* h;
  TH1D* h1;
  TH1D* hf = 0;
  TH1D* hb = 0;
 
  for (int ppac=1;ppac<=10;ppac++)
    {
      for (int ligl=1;ligl<=22;ligl++)
        {
          if (ligl!=5 && ligl!=16) continue;
          sprintf(histname,"dc1_5_leth_poly_t00_ppac%02i_ligl%02i",ppac,ligl);
          h = (TH1D*)gDirectory->FindObjectAny(histname);
          sprintf(histoname,"dc1_5_back_diff_leth_t00_ppac%02i_ligl%02i",ppac,ligl);
          h1 = (TH1D*)gDirectory->FindObjectAny(histoname);
	  
          if (!hf) hf = new TH1D (*h ); hf->Clear();
          if (!hb) hb = new TH1D (*h1); hb->Clear();
	  
          if (h1) hb->Add(h1);
          if (h)  hf->Add(h);
        }//end of loop over ligls                                                                                        
    }//end of loop over ppacs    

  // for (int i=1; i<=hf->GetNbinsX(); ++i) {
  //   double de = hf->GetBinWidth( i);
  //   double c = hf->GetBinContent( i);
  //   c *= de;
  //   double e = sqrt(c);
  //   e /= de;
  //   hf->SetBinError( i, e);
  // }
  //  hf->Add(hb,-1);
  hf->GetYaxis()->SetTitle("counts/dE (MeV^{-1})");
  hf->GetXaxis()->SetRangeUser(0.010,2.5);
  hf->GetXaxis()->SetTitle("E_{n}^{out} (MeV^{-1})");
  //  hf->UseCurrentStyle();
  hf->Draw();
  hb->SetLineColor(kRed);
  hb->SetLineWidth(3);
  hb->Draw("same");

    //hf->SetLineColor(kGreen+2);
    //hf->SetLineWidth(3);
    //hf->SetMarkerColor(kGreen+2);

  gPad->SetLogx( kFALSE);
  gPad->SetLogy( kFALSE);
  
  // tex1=new TLatex(0.65,0.75,"E_{n}^{in} = 0.7-6.0 MeV");
  // tex1->SetNDC();
  // tex1->SetTextFont(43);
  // tex1->SetTextSize(22);
  // tex1->SetTextColor(kRed);
  // tex1->Draw();
  
  // TLegend *leg = new TLegend(0.45,0.65,0.52,0.85,"","brNDC");
  // leg->AddEntry(hf,"Chi-Nu Data Prelim E_{n}^{in}=0.7 - 6.0 MeV","lp");
  // leg->AddEntry(hb,"Background","lp");
  // leg->SetFillColor(kWhite);
  // leg->SetTextFont(43);
  // leg->SetTextSize(20);
  // leg->SetBorderSize(0);
  // leg->Draw();

}

