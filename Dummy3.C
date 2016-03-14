{

  TCanvas *c1 = new TCanvas("c1","multipads", 600, 500);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  Double_t W = 0.3; // Pad Width
  Int_t Nx = 3; // Number of pads along X
  Double_t Xm = (1-(Nx*W))/2; // X Margin
  Double_t dw = (W*0.1)/4;

  TPad *p1 = new TPad("p1", "p1", Xm, 0.2, Xm+W+dw, 0.8, 0, 0, 0);
  p1->SetRightMargin(0);
  p1->Draw();

  TPad *p2 = new TPad("p2", "p2", Xm+W+dw, 0.2, Xm+2*W-dw, 0.8, 0, 0, 0);
  p2->SetRightMargin(0);
  p2->SetLeftMargin(0);
  p2->Draw();

  TPad *p3 = new TPad("p3", "p3", Xm+2*W-dw, 0.2, Xm+3*W, 0.8, 0, 0, 0);
  p3->SetLeftMargin(0);
  p3->Draw();

  TH1F *h1 = new TH1F("h1","test1",20,-3,3);
  TH1F *h2 = (TH1F*)h1->Clone("h2");
  TH1F *h3 = (TH1F*)h1->Clone("h3");

  h1->FillRandom("gaus",500); h1->SetMaximum(80);
  h2->FillRandom("gaus",300); h2->SetMaximum(80);
  h3->FillRandom("gaus",900); h3->SetMaximum(130);

  p1->cd(); h1->Draw();
  p2->cd(); h2->Draw();
  p3->cd(); h3->Draw();
}
