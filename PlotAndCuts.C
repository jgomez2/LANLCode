{

  char histname[128];
  char histoname[128];


  TFile *f = TFile::Open("BigReplay.root","READ");
  TFile *f1 = TFile::Open("polygons_U235_2015.root","UPDATE");



  for (int l=1;l<=22;l++)
    {
      f->cd("histos/DoubleCoinc");
      if (l == 3 ) continue;
      sprintf(histname,"dc1_6_tdi3_t00_ppac01_ligl%02i",l);
      TH2 *h = (TH2*)gDirectory->FindObjectAny(histname);

      new TCanvas;
      h->Draw("colz");

      f1->cd();

      sprintf(histoname,"cut_dc1_6_tdi3_t00_ppac01_ligl%02i",l);
      TCutG* c = (TCutG*)gDirectory->FindObjectAny(histoname);
      c->Draw("same");

   }//end of loop over ligls                                                                                                   

}//end of the whole thing                                                                                                      

