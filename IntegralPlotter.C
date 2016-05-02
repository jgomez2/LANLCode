void findHisto(int);
char histoname[128];
char histname[128];
char canvasname[128];
TCanvas *myCanvas[22];

Int_t IntegralPlotter(){
TFile *f = TFile::Open("FinalSum.root","READ");

for (int i = 0; i<23; i++)
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
  h->Draw();
  
  f->cd("histos/IntegralsCleaned");
  sprintf(histname,"i1_ligl%02i_integral1_baseRestored",ligl);
  TH1* h1 = (TH1*)gDirectory->FindObjectAny(histname);
  myCanvas[ligl-1]->cd(2);
  h1->Draw();
  
}//end of findHisto
