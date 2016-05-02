void findHisto(int);

char histotitle[128];
char histoname[128];
char histname[128];
char histtitle[128];
char canvasname[128];
TCanvas *myCanvas[22];


  TFile *f = TFile::Open("FinalSum.root","READ");

Int_t IntegralPlotter(){

  for (int i = 1; i<23; i++)
    {
      if (i==3) continue;
      findHisto(i);
    }
  return 0;
}



void findHisto(int ligl) {


  sprintf(canvasname,"ligl%02i",ligl);
  myCanvas[ligl-1] = new TCanvas(canvasname,canvasname,1000,700);
  myCanvas[ligl-1]->Divide(2,1);

  f->cd("histos/Integrals");
  sprintf(histoname,"i0_ligl%02i_integral1_baseRestored",ligl);
  TH1* h = (TH1*)gDirectory->FindObjectAny(histoname);
  myCanvas[ligl-1]->cd(1);
  sprintf(histotitle,"Ligl %02i Integral 1 Raw",ligl);
  h->SetTitle(histotitle);
  gStyle->SetOptStat(0);
  h->Draw();

  f->cd("histos/IntegralsCleaned");
  sprintf(histname,"i1_ligl%02i_integral1_baseRestored",ligl);
  TH1* h1 = (TH1*)gDirectory->FindObjectAny(histname);
  myCanvas[ligl-1]->cd(2);
  sprintf(histtitle,"Ligl %02i Integral 1 Cleaned",ligl);
  h1->SetTitle(histtitle);
  gStyle->SetOptStat(0);
  h1->Draw();

}//end of findHisto    
