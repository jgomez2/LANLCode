{


  TFile *f = TFile::Open("jgomez2-lowE-allruns_0pt7to6_6to12_12to18.root","READ");
  TFile *f1 = TFile::Open("polygons.root","READ");

  f->cd("histos/DoubleCoinc");
  
  TH2 *htemp;
  TH2 *h1;
  char hname[128];

  for (int l=1;l<2;l++)
    {
      if (l==3) continue;
      for (int p=1;p<=10;p++)
	{
	  sprintf(hname,"dc1_5_tdi3_t00_ppac%02i_ligl%02i",p,l);
	  htemp = (TH2*)gDirectory->FindObjectAny(hname);
	  if (!h1) h1 = (TH2*)htemp->Clone();
	  if (h1) h1->Add(htemp);
	}//end of loop on ppacs
    }//end of loop on ligls

  h1->SetTitle("");
  h1->GetYaxis()->SetTitle("Ligl01_PulseHeight");
  h1->GetXaxis()->SetRangeUser(-150,349);
  gStyle = gStylePublication;

  f->cd("histos/Integrals");
  TH1 *h;
  h=(TH1*)i0_ligl01_integral1_baseRestored->Clone();
  h->GetXaxis()->SetTitle("");

  f1->cd();
  TCutG *mycut = (TCutG*)cut_dc1_3_tdi3_t00_ppac01_ligl01->Clone();

  TCanvas *c1 = new TCanvas("c1","c1",1200,500);


  TPad *p1 = new TPad("p1", "p1", 0.0, 0.02, 0.7, 1, 0);
  //p1->SetTopMargin(0);
  //p1->SetBottomMargin(0);
  p1->SetRightMargin(0);
  p1->SetTickx(1);
  p1->Draw();

  TPad *p2 = new TPad("p2", "p2", 0.7, 0.02, 1, 1., 0);
  //p2->SetTopMargin(0);
  //p2->SetBottomMargin(0);
  p2->SetLeftMargin(0);
  p2->SetTickx(1);
  p2->Draw();

  p1->cd();h1->Draw("colz");mycut->Draw("same");
  h->SetFillColor(1);
  p2->cd();h->Draw("hbar");

}
