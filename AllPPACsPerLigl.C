{

  char histotitle[128];
  char histname[128];
  char histoname[128];
  char histtitle[128];
  char cutname[128];



  TFile *_file0 = TFile::Open("FinalSum.root","READ");
  TFile *_file1 = TFile::Open("polygons_U235_2015.root","READ");

  for (int l=1;l<23;l++)
    {
      _file0->cd("histos/DoubleCoinc");
      if (l == 3) continue;
      sprintf(histoname,"dc1_5_tdi3_t00_ppac01_ligl%02i",l);
      TH1 *hf = (TH1*)gDirectory->FindObjectAny(histoname);
      for (int i=2;i<11;i++)
        {
          sprintf(histname,"dc1_5_tdi3_t00_ppac%02i_ligl%02i",i,l);
          TH1 *h = (TH1*)gDirectory->FindObjectAny(histname);
          hf->Add(h);
          //std::cout<<"Adding histogram "<<histname<<std::endl;                                                              
        }//end of loop over ppacs                                                                                            \
                                                                                                                              
      new TCanvas;
      gPad->SetLogz();
      sprintf(histotitle,"Pulse Height vs. ToF ligl%02i all PPACs",l);
      hf->SetTitle(histotitle);
      gStyle->SetOptStat(0);
      hf->Draw("colz");


      _file1->cd();
      sprintf(cutname,"cut_dc1_7_tdi3_t00_ppac10_ligl%02i",l);
      TCutG *c = (TCutG*)gDirectory->FindObjectAny(cutname);
      c->SetLineColor(kRed);
      c->SetLineWidth(3);
      c->Draw("same");
	
      tex1=new TLatex(0.65,0.75,"E_{n}^{in} = 0.7-6 MeV");
      tex1->SetNDC();
      tex1->SetTextFont(43);
      tex1->SetTextSize(22);
      tex1->SetTextColor(kRed);
      tex1->Draw();


    }//end of loop over ligls                                                                                                \
                                                                                                                              
}//end of the whole thing      
