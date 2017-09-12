{


  TFile *f = TFile::Open("jgomez2-u235-cleaned2x-complete-sum.root","READ");
  TFile *f1 = TFile::Open("/home/jgomez2/LocalCopy/replayCfg/caenAndZtec/U235_LiGl2015/polygons_U235_2015.root","READ");

  f->cd("histos/DoubleCoinc");
  
  TH2 *htemp;
  TH2 *h1;
  char hname[128];

  char h2name[128];
  TH1 *h3;
  TH1 *blah;

  for (int l=1;l<2;l++)
    {
      if (l==3) continue;
      for (int p=1;p<=10;p++)
	{
	  sprintf(hname,"dc1_3_tdi3_t00_ppac%02i_ligl%02i",p,l);
	  htemp = (TH2*)gDirectory->FindObjectAny(hname);
	  if (!h1) h1 = (TH2*)htemp->Clone();
	  if (h1) h1->Add(htemp);

	  sprintf(h2name,"dc1_3_diff_time_t00_ppac%02i_ligl%02i",p,l);
	  blah = (TH1*)gDirectory->FindObjectAny(h2name);
	  if (!h3) h3=(TH1*)blah->Clone();
	  if (h3) h3->Add(blah);
	  
	}//end of loop on ppacs
    }//end of loop on ligls

  h1->SetTitle("");
  h1->GetYaxis()->SetTitle("Ligl01_PulseHeight");
  h1->GetXaxis()->SetRangeUser(-150,349);
  //gStyle = gStylePublication;
  gStyle->SetOptStat(0);


  f->cd("histos/Integrals");
  TH1 *h;
  h=(TH1*)i0_ligl01_integral1_baseRestored->Clone();
  h->GetXaxis()->SetTitle("");

  f1->cd();
  TCutG *mycut = (TCutG*)cut_dc1_3_tdi3_t00_ppac01_ligl01->Clone();

  TCanvas *c1 = new TCanvas("c1","c1",1200,1200);

  gStyle->SetLineWidth(2);
  //  gStyle->Set


  TPad *p1 = new TPad("p1", "p1", 0.0, 0.02, 0.7, 0.5, 0);
  p1->SetTopMargin(0);
  p1->SetBottomMargin(0.125);
  p1->SetRightMargin(0);
  p1->SetTickx(1);
  p1->Draw();

  TPad *p2 = new TPad("p2", "p2", 0.7, 0.02, 1, 0.5, 0);
  p2->SetTopMargin(0);
  p2->SetBottomMargin(.125);
  p2->SetLeftMargin(0);
  p2->SetRightMargin(0.15);
  p2->SetTickx(1);
  p2->SetTicky(1);
  p2->Draw();

   TPad *p3 = new TPad("p3","p3",0.0,0.5,0.707,0.98,0);
   p3->SetRightMargin(0.01);
   p3->SetBottomMargin(0);
   p3->SetTickx(1);
   p3->SetTicky(1);
   p3->Draw();

   h3->SetTitle("");
   h3->GetYaxis()->SetTitle("Counts");
   h3->GetYaxis()->SetTitleSize(0.055);
   h3->GetYaxis()->CenterTitle(1);
   h3->GetYaxis()->SetTitleFont(42);
   h3->GetYaxis()->SetTitleOffset(0.9);
   h3->GetYaxis()->SetLabelFont(42);
   h3->GetYaxis()->SetLabelSize(0.045);

   h1->GetYaxis()->SetTitle("LiGl Pulse Height");
   h1->GetYaxis()->SetTitleSize(0.055);
   h1->GetYaxis()->CenterTitle(1);
   h1->GetYaxis()->SetTitleFont(42);
   h1->GetYaxis()->SetTitleOffset(0.9);
   h1->GetYaxis()->SetLabelFont(42);
   h1->GetYaxis()->SetLabelSize(0.045);

   h1->GetXaxis()->SetTitle("Outgoing Neutron Time Of Flight (ns)");
   h1->GetXaxis()->SetTitleSize(0.055);
   h1->GetXaxis()->CenterTitle(1);
   h1->GetXaxis()->SetTitleFont(42);
   h1->GetXaxis()->SetLabelFont(42);
   h1->GetXaxis()->SetLabelSize(0.045);

   h->SetTitle("");
   h->GetYaxis()->SetTitle("Counts");
   h->GetYaxis()->CenterTitle(1);
   h->GetYaxis()->SetTitleFont(42);
   h->GetYaxis()->SetTitleSize(0.0855);
   h->GetYaxis()->SetTitleOffset(0.6);
   h->SetNdivisions(5,"Y");
   h->GetYaxis()->SetLabelFont(42);
   h->GetYaxis()->SetLabelSize(0.07);
   h->GetYaxis()->SetLabelOffset(.0001);
   h->GetYaxis()->SetRangeUser(0.001,1.1*h->GetBinContent(h->GetMaximumBin()));

   p1->cd();h1->Draw("colz");mycut->Draw("same");gPad->SetLogz();
   h->SetFillColor(1);
   p2->cd();h->Draw("hbar");
   p3->cd();h3->Draw();gPad->SetLogy();

}
