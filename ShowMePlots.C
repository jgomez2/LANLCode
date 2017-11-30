char FileName[128];
TH1 *l3;
TH1 *l10;
TH1 *l17;

//use with 'for F in `seq RunA RunB`;do root ShowMePlots.C\($F\);done' and then hit -q every time to check the time offset for
//betteroffsetextractor.C


void ShowMePlots(int runNum) {
  
  sprintf(FileName,"jgomez2-dflt-tag-%i.root",runNum);
  ptr_file=fopen(FileName,"r");
  if(ptr_file==NULL) return;
  
  TFile *f = new TFile(FileName);
  f->cd("histos/TwoDetectorCoinc");
  
  TH1 *l3 =(TH1*)gDirectory->FindObjectAny("td1_05_time_ppac05_ligl03");
  TH1 *l10 =(TH1*)gDirectory->FindObjectAny("td1_05_time_ppac05_ligl10");
  TH1 *l17 =(TH1*)gDirectory->FindObjectAny("td1_05_time_ppac05_ligl17");

  l3->GetXaxis()->SetRangeUser(-20,20);
  l10->GetXaxis()->SetRangeUser(-20,20);
  l17->GetXaxis()->SetRangeUser(-20,20);


  TCanvas *c1 =new TCanvas("c1","c1");
  c1->SetCanvasSize(1000,1000);
  c1->SetWindowSize(1200,1200);
  c1->Divide(1,3);
  c1->cd(1);
  l3->Draw();
  c1->cd(2);
  l10->Draw();
  c1->cd(3);
  l17->Draw();

}
