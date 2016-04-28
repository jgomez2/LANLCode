{

  char histname[128];
  char histoname[128];
  char cutname[128];
 
  TFile *_file0 = TFile::Open("BigReplay.root","READ");
  TFile *_file1 = TFile::Open("polygons_U235_2015.root","UPDATE");

  for (int l=1;l<23;l++)
    {
      _file0->cd("histos/DoubleCoinc");
      if (l == 3) continue;
      sprintf(histoname,"dc1_6_tdi3_t00_ppac01_ligl%02i",l);
      TH1 *hf = (TH1*)gDirectory->FindObjectAny(histoname);
      for (int i=2;i<11;i++)
        {
	  sprintf(histname,"dc1_6_tdi3_t00_ppac%02i_ligl%02i",i,l);
          TH1 *h = (TH1*)gDirectory->FindObjectAny(histname);
          hf->Add(h);
	  std::cout<<"Adding histogram "<<histname<<std::endl;
        }//end of loop over ppacs                                                                                             
      new TCanvas;
      gPad->SetLogz();
      hf->Draw("colz");

      
      _file1->cd();
      sprintf(cutname,"cut_dc1_6_tdi3_t00_ppac10_ligl%02i",l);
      TCutG *c = (TCutG*)gDirectory->FindObjectAny(cutname);
      c->SetLineColor(kRed);
      c->SetLineWidth(3);
      c->Draw("same");
      
    }//end of loop over ligls                                                                                                 
}//end of the whole thing  
