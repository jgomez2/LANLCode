{
  TFile *f = TFile::Open("jgomez2-dflt-tag-supertight.root","READ");
  f->cd("histos/SinglesCleaned");

  TH1 *h = (TH1*)s1_time_ligl19->Clone();
  TH1 *h1 = (TH1*)s1_time_ppac05->Clone();

  gStyle->SetLineWidth(2);
  gStyle->SetOptStat(0);

  const double ymax=200000.;
  const double ypmax=40000.;

  h->SetTitle("");
  
  h->GetXaxis()->SetTitle("Pulse Time (#mus)");
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->CenterTitle(1);
  h->GetXaxis()->SetTitleSize(0.055);
  h->GetXaxis()->SetLabelSize(0.045);

  h->GetYaxis()->SetTitle("Counts");
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->CenterTitle(1);
  h->GetYaxis()->SetTitleSize(0.055);
  h->GetYaxis()->SetLabelSize(0.045);


  h1->SetTitle("");
  
  h1->GetXaxis()->SetTitle("Pulse Time (#mus)");
  h1->GetXaxis()->SetTitleFont(42);
  h1->GetXaxis()->CenterTitle(1);
  h1->GetXaxis()->SetTitleSize(0.055);
  h1->GetXaxis()->SetLabelSize(0.045);

  h1->GetYaxis()->SetTitle("Counts");
  h1->GetYaxis()->SetTitleFont(42);
  h1->GetYaxis()->CenterTitle(1);
  h1->GetYaxis()->SetTitleSize(0.055);
  h1->GetYaxis()->SetLabelSize(0.045);
  

  TLine *l = new TLine(50,0,50,ymax);
  l->SetLineColor(kRed);
  l->SetLineWidth(2);
  l->SetLineStyle(2);

  TLine *l1 = new TLine(100,0,100,ymax);
  l1->SetLineColor(kRed);
  l1->SetLineWidth(2);
  l1->SetLineStyle(2);

  TLine *l2 = new TLine(150,0,150,ymax);
  l2->SetLineColor(kRed);
  l2->SetLineWidth(2);
  l2->SetLineStyle(2);

  TLine *l3 = new TLine(200,0,200,ymax);
  l3->SetLineColor(kRed);
  l3->SetLineWidth(2);
  l3->SetLineStyle(2);

  TLine *l4 = new TLine(250,0,250,ymax);
  l4->SetLineColor(kRed);
  l4->SetLineWidth(2);
  l4->SetLineStyle(2);

  TLine *l5 = new TLine(300,0,300,ymax);
  l5->SetLineColor(kRed);
  l5->SetLineWidth(2);
  l5->SetLineStyle(2);

  TLine *l6 = new TLine(400,0,400,ymax);
  l6->SetLineColor(kRed);
  l6->SetLineWidth(2);
  l6->SetLineStyle(2);

  TLine *l7 = new TLine(500,0,500,ymax);
  l7->SetLineColor(kRed);
  l7->SetLineWidth(2);
  l7->SetLineStyle(2);

  TLine *l8 = new TLine(600,0,600,ymax);
  l8->SetLineColor(kRed);
  l8->SetLineWidth(2);
  l8->SetLineStyle(2);

  TLine *l9 = new TLine(0.,0,0.,ymax);
  l9->SetLineColor(kRed);
  l9->SetLineWidth(2);
  l9->SetLineStyle(2);

  TLine *pl = new TLine(50,0,50,ypmax);
  pl->SetLineColor(kRed);
  pl->SetLineWidth(2);
  pl->SetLineStyle(2);

  TLine *pl1 = new TLine(100,0,100,ypmax);
  pl1->SetLineColor(kRed);
  pl1->SetLineWidth(2);
  pl1->SetLineStyle(2);
  
  TLine *pl2 = new TLine(150,0,150,ypmax);
  pl2->SetLineColor(kRed);
  pl2->SetLineWidth(2);
  pl2->SetLineStyle(2);

  TLine *pl3 = new TLine(200,0,200,ypmax);
  pl3->SetLineColor(kRed);
  pl3->SetLineWidth(2);
  pl3->SetLineStyle(2);

  TLine *pl4 = new TLine(250,0,250,ypmax);
  pl4->SetLineColor(kRed);
  pl4->SetLineWidth(2);
  pl4->SetLineStyle(2);

  TLine *pl5 = new TLine(300,0,300,ypmax);
  pl5->SetLineColor(kRed);
  pl5->SetLineWidth(2);
  pl5->SetLineStyle(2);

  TLine *pl6 = new TLine(400,0,400,ypmax);
  pl6->SetLineColor(kRed);
  pl6->SetLineWidth(2);
  pl6->SetLineStyle(2);

  TLine *pl7 = new TLine(500,0,500,ypmax);
  pl7->SetLineColor(kRed);
  pl7->SetLineWidth(2);
  pl7->SetLineStyle(2);

  TLine *pl8 = new TLine(600,0,600,ypmax);
  pl8->SetLineColor(kRed);
  pl8->SetLineWidth(2);
  pl8->SetLineStyle(2);

  TLine *pl9 = new TLine(0.,0,0.,ypmax);
  pl9->SetLineColor(kRed);
  pl9->SetLineWidth(2);
  pl9->SetLineStyle(2);
  

  new TCanvas;
  h->Draw();
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  gPad->SetLogy(1);
  l->Draw("same");l1->Draw("same");l2->Draw("same");l3->Draw("same");
  l4->Draw("same");l5->Draw("same");l6->Draw("same");l7->Draw("same");
  l8->Draw("same");l9->Draw("same");

  TLatex *mytex = new TLatex(0.7,0.3,"LiGl");
  mytex->SetNDC();
  mytex->SetTextFont(42);
  mytex->SetTextSize(.05);
  mytex->Draw();



  new TCanvas;
  h1->Draw();
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  gPad->SetLogy(1);
  pl->Draw("same");pl1->Draw("same");pl2->Draw("same");pl3->Draw("same");
  pl4->Draw("same");pl5->Draw("same");pl6->Draw("same");pl7->Draw("same");
  pl8->Draw("same");pl9->Draw("same");

  TLatex *mytex1 = new TLatex(0.7,0.6,"PPAC");
  mytex1->SetNDC();
  mytex1->SetTextFont(42);
  mytex1->SetTextSize(.05);
  mytex1->Draw();

  TH1 *h2= (TH1*)h1->Clone();
  h2->Clear();
  h2->Reset();
  const int xlobin= h2->FindBin(0.0);
  const int xhibin= h2->FindBin(50.0);
  for (int i=xlobin;i<=xhibin;i++) h2->SetBinContent(i,h1->GetBinContent(i));
  h2->SetLineColor(kRed);
  h2->SetMarkerColor(kRed);

  new TCanvas;
  h1->Draw();
  h2->Draw("same");
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  gPad->SetLogy(1);
  pl->Draw("same");pl1->Draw("same");pl2->Draw("same");pl3->Draw("same");
  pl4->Draw("same");pl5->Draw("same");pl6->Draw("same");pl7->Draw("same");
  pl8->Draw("same");pl9->Draw("same");
  c1_n3->RedrawAxis();
  
  mytex1->Draw();


}
