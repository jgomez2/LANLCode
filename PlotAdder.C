{

  char histname[128];
  char histoname[128];
  _file0->cd("histos/DoubleCoinc");

  sprintf(histoname,"dc1_3_diff_time_t00_ppac01_ligl01");
  TH1 *hf = (TH1*)gDirectory->FindObjectAny(histoname);

  for (int l=1;l<23;l++)
    {
      if (l == 3 ||
          l == 5 ||
          l == 16) continue;
      for (int i=1;i<11;i++)
        {
          if (l==1 && i==1) continue;
          // std::cout<<"LIGL NUMBER "<<l<<"   "<<"PPAC NUMBER "<<i-1<<std::endl;                                             
          sprintf(histname,"dc1_3_diff_time_t00_ppac%02i_ligl%02i",i,l);
          TH1 *h = (TH1*)gDirectory->FindObjectAny(histname);
          hf->Add(h);
        }//end of loop over ppacs                                                                                             
    }//end of loop over ligls                                                                                                 
  new TCanvas;
  hf->SetLineColor(kRed);
  hf->Draw();

  _file0->cd("histos/TwoDetectorCoinc/background");
  sprintf(histoname,"td1_05_back_time_ppac01_ligl01");
  TH1* hb = (TH1*)gDirectory->FindObjectAny(histoname);

  for (int l=1;l<23;l++)
    {
      if (l == 3 ||
          l == 5 ||
          l == 16) continue;
      for (int i=1;i<11;i++)
        {
          if (l==1 && i==1) continue;
          sprintf(histname,"td1_05_back_time_ppac%02i_ligl%02i",i,l);
          TH1 *h = (TH1*)gDirectory->FindObjectAny(histname);
          hb->Add(h);
        }//end of loop over ppacs                                                                                             
    }//end of loop over ligls                                                                                                 
  hb->Draw("same");


}//end of the whole thing  
