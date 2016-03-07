{

  char histname[128];
  char histoname[128];
  TFile *f = new TFile("jgomez2-dflt-tag-sum.root");
  f->cd("histos/TwoDetectorCoinc");


  for (int l=1;l<23;l++)
    {
      if (l<10) sprintf(histoname,"td0_05_tdi2_ppac01_ligl0%i_int1",l);
      if (l>=10) sprintf(histoname,"td0_05_tdi2_ppac01_ligl%i_int1",l);
      TH2 *h1 = (TH2*)gDirectory->FindObjectAny(histoname);

      for (int i=2;i<3;i++)
        {
          if (l<10)
            {
              if (i<10) sprintf(histname,"td0_05_tdi2_ppac0%i_ligl0%i_int1",i,l);
              if (i=10) sprintf(histname,"td0_05_tdi2_ppac%i_ligl0%i_int1",i,l);
            }
          if (l>=10)
            {
              if (i<10) sprintf(histname,"td0_05_tdi2_ppac0%i_ligl%i_int1",i,l);
              if (i=10) sprintf(histname,"td0_05_tdi2_ppac%i_ligl%i_int1",i,l);
            }
          TH2 *h = (TH2*)gDirectory->FindObjectAny(histname);
          int binsX=h->GetXaxis()->GetNbins();
          int binsY=h->GetYaxis()->GetNbins();

          for (int j=1;j<binsY+1;j++)
            {
              for (int k=1;k<binsX+1;k++)
                {
                  h1->AddBinContent(h1->GetBin(k,j),h->GetBinContent(k,j));
                }//end of loop over x bins
            }//end of loop over y bins
          //h1->Add(h);
        }//end of loop over ppacs

      new TCanvas;
      gPad->SetLogz();
      h1->Draw("colz");
    }//end of loop over ligls
}//end of the whole thing
