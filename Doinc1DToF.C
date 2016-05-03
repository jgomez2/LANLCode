void findHisto(int);

char histotitle[128];
char histoname[128];
char histname[128];
char histtitle[128];
char canvasname[128];
TCanvas *myCanvas[10];


TFile *f = TFile::Open("FinalSum.root","READ");

Int_t Doinc1DToF(){

  for (int i = 1; i<11; i++)
    {
      findHisto(i);
    }
  return 0;
}



void findHisto(int ppac) {


  sprintf(canvasname,"ppac%02i",ppac);
  myCanvas[ppac-1] = new TCanvas(canvasname,canvasname,1000,700);


  for (int j=1;j<23;j++)
    {
      f->cd("histos/DoubleCoinc");
      sprintf(histoname,"dc1_5_diff_time_t00_ppac%02i_ligl%02i",ppac,j);
      if (j==3 || j==5 || j==16) continue;
      if (j==1) TH1 *hf = (TH1*)gDirectory->FindObjectAny(histoname);
      else      TH1*  h = (TH1*)gDirectory->FindObjectAny(histoname);
      hf->Add(h);
      //std::cout<<"Adding "<<histoname<<std::endl;                                                                          \
                                                                                                                              
      f->cd("histos/DoubleCoinc/background");
      sprintf(histname,"dc1_5_back_diff_time_t00_ppac%02i_ligl%02i",ppac,j);
      if (j==3 || j==5 || j==16) continue;
      if (j==1) TH1 *hb = (TH1*)gDirectory->FindObjectAny(histoname);
      else      TH1* h1 = (TH1*)gDirectory->FindObjectAny(histoname);
      hb->Add(h1);
    }//end of loop over ligls                                                                                                \
                                                                                                                              

  myCanvas[ppac-1]->cd(1);
  //gPad->SetLogy();                                                                                                         \
                                                                                                                              
  gPad->SetLogy();
  sprintf(histotitle,"ToF PPAC %02i All Ligls Except 3,5,16",ppac);
  hf->SetTitle(histotitle);
  gStyle->SetOptStat(0);
  hf->Draw();
  hb->Draw("same");

  tex1=new TLatex(0.65,0.75,"E_{n}^{in} = 0.7-6 MeV");
  tex1->SetNDC();
  tex1->SetTextFont(43);
  tex1->SetTextSize(22);
  tex1->SetTextColor(kRed);
  tex1->Draw();

}//end of findHisto      
