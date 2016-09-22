{


  TFile *f = TFile::Open("jgomez2-lowE-allruns_0pt7to6_6to12_12to18.root","READ");
  TFile *f1 = TFile::Open("polygons.root","READ");

  f->cd("histos/DoubleCoinc");
  
  TH2 *htemp;
  TH2 *h1;
  char hname[128];

  TH1 *blah;
  TH1 *h;
  char h2name[128];

  TH1 *backtemp;
  TH1 *hb;
  char backname[128];

  for (int l=1;l<2;l++)
    {
      if (l==3) continue;
      for (int p=1;p<=10;p++)
	{
	  sprintf(hname,"dc1_3_tdi3_t00_ppac%02i_ligl%02i",p,l);
	  htemp = (TH2*)gDirectory->FindObjectAny(hname);
	  if (!h1) h1 = (TH2*)htemp->Clone();
	  if (h1) h1->Add(htemp);

	  sprintf(h2name,"dc1_3_diff_poly_t00_ppac%02i_ligl%02i",p,l);
	  blah = (TH1*)gDirectory->FindObjectAny(h2name);
	  if (!h) h=(TH1*)blah->Clone();
	  if (h) h->Add(blah);

	  sprintf(backname,"dc1_3_back_diff_poly_t00_ppac%02i_ligl%02i",p,l);
	  backtemp = (TH1*)gDirectory->FindObjectAny(backname);
	  if (!hb) hb=(TH1*)backtemp->Clone();
	  if (hb) hb->Add(backtemp);
	  
	}//end of loop on ppacs
    }//end of loop on ligls

  hb->SetLineColor(kRed);

  h1->SetTitle("");
  h1->GetYaxis()->SetTitle("Ligl01_PulseHeight");
  h1->GetXaxis()->SetRangeUser(-150,349);
  gStyle = gStylePublication;

  hb->GetXaxis()->SetRangeUser(-150,349);
  h->GetXaxis()->SetRangeUser(-150,349);

  f1->cd();
  TCutG *mycut = (TCutG*)cut_dc1_3_tdi3_t00_ppac01_ligl01->Clone();

  TCanvas *c1 = new TCanvas("c1","c1",800,1200);


  TPad *p1 = new TPad("p1", "p1", 0.0, 0.02, 1., .5, 0);
  p1->SetTopMargin(0);
  //p1->SetBottomMargin(0);
  //p1->SetRightMargin(0);
  p1->SetTickx(1);
  p1->Draw();

  TPad *p2 = new TPad("p2", "p2", 0.0, 0.5, 1, 0.98, 0);
  //p2->SetTopMargin(0);
  p2->SetBottomMargin(0);
  //p2->SetLeftMargin(0);
  p2->SetTickx(1);
  p2->Draw();

  p1->cd();h1->Draw("colz");mycut->Draw("same");
  p2->cd();h->Draw();hb->Draw("same");

}
