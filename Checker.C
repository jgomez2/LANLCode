{

  TProfile *backchange = new TProfile("BackgroundPercentChange","BackgroundPercentChange",22,0,22);
  backchange->GetYaxis()->SetRangeUser(0.5,1.5);
  backchange->GetYaxis()->SetTitle("Percent Change in Counts");
  backchange->Sumw2();
  
  TFile *f81 = TFile::Open("./SecondTry/jgomez2-dflt-tag-19581.root","READ");
  TFile *f87 = TFile::Open("./SecondTry/jgomez2-dflt-tag-19587.root","READ");
  TFile *fsum = TFile::Open("./jgomez2-dflt-tag-sum.root","READ");

  Double_t t81=0.0;
  Double_t t87=0.0;
  Double_t tsum=0.0;
  
  f81->cd("histos/SinglesInCoincs");
  TH1 *ht81 = (TH1*)gDirectory->FindObjectAny("s2_time_t00");
  t81=ht81->GetEntries();

  f87->cd("histos/SinglesInCoincs");
  TH1 *ht87 = (TH1*)gDirectory->FindObjectAny("s2_time_t00");
  t87=ht87->GetEntries();
  
  fsum->cd("histos/SinglesInCoincs");
  TH1 *htsum = (TH1*)gDirectory->FindObjectAny("s2_time_t00");
  tsum=htsum->GetEntries();

  
  f81->cd("histos/DoubleCoinc/background");
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

  
   for (int ligliter=1;ligliter<=22;ligliter++)
     {
       if (ligliter==3) continue;
       char liglname[128];
       //sprintf(liglname,"dc1_3_back_poly_leth_t00_ppac02_ligl%02i",ligliter);
       sprintf(liglname,"dc1_3_back_diff_leth_t00_ppac02_ligl%02i",ligliter);
      
      
       f81->cd("histos/DoubleCoinc/background");
       //f81->cd("histos/DoubleCoinc/");
       //TH1 *h81 = (TH1*)dc1_3_back_poly_leth_t00_ppac02_ligl07->Clone();
       TH1 *h81 = new TH1*;
       h81=(TH1*)gDirectory->FindObjectAny(liglname);
       
      
       f87->cd("histos/DoubleCoinc/background");
       //f87->cd("histos/DoubleCoinc/");
       //TH1 *h87 = (TH1*)dc1_3_back_poly_leth_t00_ppac02_ligl07->Clone();
       TH1 *h87 = new TH1*;
       h87=(TH1*)gDirectory->FindObjectAny(liglname);
       

       fsum->cd("histos/DoubleCoinc/background");
       //fsum->cd("histos/DoubleCoinc/");
       //TH1 *hsum = (TH1*)dc1_3_back_poly_leth_t00_ppac02_ligl07->Clone();
       TH1 *hsum = new TH1*;
       hsum=(TH1*)gDirectory->FindObjectAny(liglname);

       TH1 *h81c = (TH1*)h81->Clone();
      h81c->Add(h87,1);
      h81c->SetLineColor(kRed);
      h81c->SetMarkerColor(kRed);
      
      //new TCanvas;
      //hsum->Draw();
      //h81->Draw("same");
      
      TH1 *hrat= new TH1*;
      hrat= (TH1*)hsum->Clone();
      hrat->Divide(h81c);
      
      //new TCanvas;
      //hrat->Draw();

      
      for (int i=1;i<=hrat->GetNbinsX();i++)
	{
	  if (hrat->GetBinContent(i)!=1 && hrat->GetBinContent(i)!=0) 
	    {
	      //std::cout<<"The bin content for bin: "<<i<<"  was: "<<hrat->GetBinContent(i)<<std::endl;
	      //std::cout<<hrat->GetBinCenter(i)<<"\t"<<ligliter<<std::endl;
	      backchange->Fill(ligliter-0.5,hrat->GetBinContent(i));
	    }
	  if(hrat->GetBinContent(i)!=0)twodchange->Fill(hrat->GetBinCenter(i),ligliter-0.5,hrat->GetBinContent(i));
	  else if(hrat->GetBinContent(i)==0)twodchange->Fill(hrat->GetBinCenter(i),ligliter-0.5,0.000001);
	}
      
      
     }

   
   

   // new TCanvas;
   // backchange->Draw("TEXTE");

   // for (int j=1;j<=22;j++)
   //   {
   //     if (j==3) continue;
   //     std::cout<<"Ligl "<<j<<"\t Percent Change:"<<(backchange->GetBinContent(j)-1)*100.<<std::endl;
   //   }
  
   // new TCanvas;
   // twodchange->Draw("colz");
 
   
   new TCanvas;
   hsum->GetYaxis()->SetTitle("Counts");
   hsum->GetYaxis()->CenterTitle(1);
   hsum->GetXaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
   hsum->GetXaxis()->CenterTitle(1);
   // hsum->Scale(1./tsum);
   hsum->SetLineColor(kGreen+1);
   hsum->SetMarkerColor(kGreen+1);	 
   hsum->SetMarkerStyle(2);
   hsum->Draw();
   //h81->Scale(1./t81);
   h81->SetLineColor(kRed);
   h81->SetMarkerColor(kRed);
   h81->Draw("same");
   //h87->Scale(1./t87);
   h87->SetLineColor(kBlue);
   h87->SetMarkerColor(kBlue);
   h87->Draw("same");
   //h81c->Scale(1./(t81+t87));
   h81c->SetLineColor(kMagenta);
   h81c->SetMarkerColor(kMagenta);
   h81c->SetMarkerStyle(5);
   h81c->Draw("same");

   TLegend *leg = new TLegend(0.55,0.55,0.8,0.8,"","brNDC");
   leg->AddEntry(hsum,"bkg(19581+19587)","lp");
   leg->AddEntry(h81,"bkg(19581)","lp");
   leg->AddEntry(h87,"bkg(19587)","lp");
   leg->AddEntry(h81c,"bkg(19581)+bkg(19587)","lp");
   leg->SetFillColor(kWhite);
   leg->SetBorderSize(0);
   leg->SetTextFont(43);
   leg->SetTextSize(20);
   leg->Draw();
   
   
   char firstline[128];
   char secondline[128];
   char thirdline[128];
   sprintf(firstline,"n_{t_{0}}^{sum} = %8.f",tsum);
   sprintf(secondline,"n_{t_{0}}^{19581} = %8.f",t81);
   sprintf(thirdline,"n_{t_{0}}^{19587} = %8.f",t87);

   tex1 = new TLatex(0.6,0.4,TString::Format("#splitline{%s}{#splitline{%s}{%s}}",firstline,secondline,thirdline));
   tex1->SetNDC();
   tex1->SetTextFont(43);
   tex1->SetTextSize(22);
   tex1->Draw();

}
