{

  TProfile *backchange = new TProfile("BackgroundPercentChange","BackgroundPercentChange",22,0,22);
  backchange->GetYaxis()->SetRangeUser(0.5,1.5);
  backchange->GetYaxis()->SetTitle("Percent Change in Counts");
  backchange->Sumw2();
  
  TFile *f47 = TFile::Open("/Volumes/MACLiglData/jgomez2-19243-19252-19247.root","READ");
  TFile *f58 = TFile::Open("/Volumes/MACLiglData/jgomez2-19456-19466-19458.root","READ");
  
  Double_t t47=0.0;
  Double_t t58=0.0;
   
  f47->cd("histos/SinglesInCoincs");
  TH1 *ht47 = (TH1*)gDirectory->FindObjectAny("s2_time_t00");
  t47=ht47->GetEntries();

  f58->cd("histos/SinglesInCoincs");
  TH1 *ht58 = (TH1*)gDirectory->FindObjectAny("s2_time_t00");
  t58=ht58->GetEntries();
  
 
  
  f47->cd("histos/DoubleCoinc/background");
  TAxis *xaxis = dc1_3_back_poly_leth_t00_ppac02_ligl07->GetXaxis();
  //TH2D *twodchange = new TH2D("ChangevsE","ChangevsE",22,0,22,1000,0.99,1.01);
  TH2D *twodchange = new TH2D("ChangevsE","ChangevsE",xaxis->GetNbins(),xaxis->GetXbins()->GetArray(),22,0,22);
  char binname[128];
  for (int z=1;z<=22;z++)
    {
      sprintf(binname,"ligl%02i",z);
      backchange->GetXaxis()->SetBinLabel(z,binname);
      twodchange->GetYaxis()->SetBinLabel(z,binname);
    }
  twodchange->GetZaxis()->SetRangeUser(0.09999,1.0009);
  backchange->GetXaxis()->LabelsOption("v");
  gStyle=gStylePublication;

  
   for (int ligliter=7;ligliter<=7;ligliter++)
     {
       if (ligliter==3) continue;
       char liglname[128];
       sprintf(liglname,"dc1_3_back_poly_leth_t00_ppac02_ligl%02i",ligliter);
       //sprintf(liglname,"dc1_3_back_diff_leth_t00_ppac02_ligl%02i",ligliter);
      
      
       f47->cd("histos/DoubleCoinc/background");
       //f47->cd("histos/DoubleCoinc/");
       //TH1 *h47 = (TH1*)dc1_3_back_poly_leth_t00_ppac02_ligl07->Clone();
       TH1F *h47 = new TH1F*;
       h47=(TH1F*)gDirectory->FindObjectAny(liglname);
       
      
       f58->cd("histos/DoubleCoinc/background");
       //f58->cd("histos/DoubleCoinc/");
       //TH1 *h58 = (TH1*)dc1_3_back_poly_leth_t00_ppac02_ligl07->Clone();
       TH1F *h58 = new TH1F*;
       h58=(TH1F*)gDirectory->FindObjectAny(liglname);
              
       
       new TCanvas;
       h47->Scale(1./t47);
       h58->Scale(1./t58);
       
       return;
     }
}
       
