{

  //TFile *f = TFile::Open("jgomez2-timeordered.root");
  //TFile *f = TFile::Open("/Volumes/MACLiglData/jgomez2-19150-19154-19151.root","READ");
  TFile *f = TFile::Open("/Volumes/MACLiglData/jgomez2-19156-19166-19163.root","READ");
  
  f->cd("histos/Scaler");

  TH1D *liglrate = new TH1D("ligl7rate","ligl7rate",3500,0,3500);
  TH1D *ppacrate = new TH1D("ppac2rate","ppac2rate",750,0,750);
  TH1D *t0rate = new TH1D("t0Rate","t0Rate",600000,0,600000);
  
  TH1 *ligl= (TH1*)rate_s041_ligl07_hits->Clone();
  TH1 *ppac = (TH1*)rate_s032_ppac02_hits->Clone();
  TH1 *t0 = (TH1*)rate_s027_t00_hits->Clone();


  for (int i=1;i<=ppac->GetNbinsX();i++)
    {
      liglrate->Fill(ligl->GetBinContent(i));
      ppacrate->Fill(ppac->GetBinContent(i));
      t0rate->Fill(t0->GetBinContent(i));
    }
  
  
  new TCanvas;
  liglrate->Draw();

  new TCanvas;
  ppacrate->Draw();

  new TCanvas;
  t0rate->Draw();



}
