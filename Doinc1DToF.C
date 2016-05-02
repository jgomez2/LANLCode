File Edit Options Buffers Tools C++ Help                                                                                      
void findHisto(int);

char histotitle[128];
char histoname[128];
char histname[128];
char histtitle[128];
char canvasname[128];
TCanvas *myCanvas[10];


  TFile *f = TFile::Open("FinalSum.root","READ");

Int_t IntegralPlotter(){

  for (int i = 1; i<11; i++)
    {
      findHisto(i);
    }
  return 0;
}



void findHisto(int ppac) {


  sprintf(canvasname,"ppac%02i",ppac);
  myCanvas[ppac-1] = new TCanvas(canvasname,canvasname,1000,700);

  f->cd("histos/DoubleCoinc");
  for (int j=1;j<23;j++)
    {
      sprintf(histoname,"dc1_5_diff_time_t00_ppac%02i_ligl%02i",ppac,j);
      if (j==1) TH1 *h = (TH1*)gDirectory->FindObjectAny(histoname);
      if (j==3 || j==5 || j==16) continue;
      TH1*  h = (TH1*)gDirectory->FindObjectAny(histoname);
      hf->Add(h);
    }//end of loop over ligls
    
  gPad->SetLogy(1);
  sprintf(histotitle,"Ligl %02i Integral 1 Raw",ligl);
  hf->SetTitle(histotitle);
  gStyle->SetOptStat(0);
  hf->Draw();


}//end of findHisto                                                                                                           

