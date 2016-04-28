void FindHist(int);

char histoname[128];
char histname[128];
char canvasname[128];
TCanvas *myCanvas[22];

Int_t BananaCompare(){

  for (int i = 1; i<=22;i++)
    {
      if(i==3) continue;
      FindHist(i);
    }
  return 0;
}

void FindHist(int ligl){

  sprintf(canvasname,"ligl%02i",ligl);
  myCanvas[ligl-1] = new TCanvas(canvasname,canvasname,1000,700);
  sprintf(histoname,"cut_dc1_6_tdi3_t00_ppac01_ligl%02i",ligl);
  TCutG* c = (TCutG*)gDirectory->FindObjectAny(histoname);
  c->Draw("axpl");
  c->SetLineColor(kRed);

  sprintf(histname,"cut_dc1_6_tdi3_t00_ppac10_ligl%02i",ligl);
  TCutG* c1 = (TCutG*)gDirectory->FindObjectAny(histname);
  c1->Draw("lsame");
  c1->SetLineColor(kBlue);

  TLegend* leg = new TLegend(0.22,0.65,0.5,0.85,"","brNDC");
  leg->AddEntry("c","Red is PPAC 1 , Blue is PPAC 10","lep");
  // leg->AddEntry("c1","LiglX w.r.t. PPAC 10","lep");                                                                         
  leg->Draw();

}//end find hist     
