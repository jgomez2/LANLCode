//====================================================================

void scaleGraph (TGraphErrors* g, double scale) {

  //--------------------------------------------------------------------

  int nPoints = g->GetN();
  for (int i=0; i<nPoints; ++i) {
    g->GetY()[i]  *= scale;
    g->GetEY()[i] *= scale;
  }

  return;
}

//====================================================================

void PFNSPlotter (void) {

  //--------------------------------------------------------------------

  //  gStyle = gStylePublication;

  TFile *f = new TFile("jgomez2-lowE-allruns_0pt7to6_6to12_12to18.root","READ");
 
  char fissionhistoname[128];
  TH1D *fHisto;

  f->cd("histos/SinglesInCoincs");
  Double_t nFissions = 0.;
  Double_t nuBar = 2.4;
  Double_t cielo1Neutrons = 758041792.;
  Double_t cielo2Neutrons = 949824200;
  Double_t ENDFNeutrons = 594219978;
  Double_t maxwellianNeutrons = 957283252;
  

  
  //Special Scaling Section
  char withoutcutshisto[128];
  char withcutshisto[129];
  TH1D* chisto;
  TH1D* nochisto;
  
  Double_t nsignalswithcut=0.;
  Double_t nsignalswithoutcut=0.;
  Double_t integralwidth = 50;
  
  f->cd("histos/DoubleCoinc/background");
  for (int ppac=1;ppac<=10;ppac++)
    {
      sprintf(withoutcutshisto,"dc1_3_back_sngl_t00_ppac%02i",ppac);
      sprintf(withcutshisto,"dc1_5_back_sngl_t00_ppac%02i",ppac);
      

      nochisto = (TH1D*)gDirectory->FindObjectAny(withoutcutshisto);
      TAxis *axis = nochisto->GetXaxis();
      int bmin = axis->FindBin(-50);
      int bmax = axis->FindBin(0.0); 
      double dataintegral = nochisto->Integral(bmin,bmax);
      //std::cout<<dataintegral<<std::endl;
      //     nsignalswithoutcut+=nochisto->GetEntries();
      dataintegral = (dataintegral/integralwidth)*1130.;
    

      chisto = (TH1D*)gDirectory->FindObjectAny(withcutshisto);
      nsignalswithcut+=chisto->Integral()-dataintegral;
    }//end of finding scale factor of the scale factor

  
  f->cd("histos/DoubleCoinc");

  //Creating Splines which fit the Graph data points
  maxwellian= new TGraphErrors("max_leth_latest","%lg %lg %lg");
  TSpline3 *smaxwellian = new TSpline3("sss",maxwellian);
  cielo= new TGraphErrors("cielo_leth_latest","%lg %lg %lg");
  TSpline3 *scielo = new TSpline3("ss",cielo);
  pfns = new TGraphErrors("PFNS_ENDFVIIpt1B_1MeV.txt","%lg %lg");
  TSpline3 *spfns = new TSpline3("s",pfns);
    

  //Setting options to better see the graphs
  cielo->SetMarkerSize(0.75);
  cielo->SetMarkerColor(kBlue);
  cielo->SetMarkerStyle(21);
  
  maxwellian->SetMarkerColor(kRed);
  maxwellian->SetMarkerSize(0.5);
  maxwellian->SetMarkerStyle(21);

  char histotitle[128];
  char histoname[128];
  char histname[128];
  char histtitle[128];
  
  TH1D* h;
  TH1D* h1;
  TH1D* hf = 0;
  TH1D* hb = 0;
 
  //Creating the foreground and background histos, hf and hb respectively
  for (int ppac=1;ppac<=10;ppac++)
    {
      for (int ligl=1;ligl<=22;ligl++)
	{
	  //if (ligl!=1 && ligl!=12) continue;
	  //if (ligl==3 || ligl==5 || ligl==16) continue;
	  if (ligl==3) continue;
	  //if (ligl!=5 && ligl!=16) continue;
	  sprintf(histname,"dc1_5_leth_poly_t00_ppac%02i_ligl%02i",ppac,ligl);
	  h = (TH1D*)gDirectory->FindObjectAny(histname);
	  sprintf(histoname,"dc1_5_back_diff_leth_t00_ppac%02i_ligl%02i",ppac,ligl);
	  h1 = (TH1D*)gDirectory->FindObjectAny(histoname);

          if (!hf) hf = new TH1D (*h ); hf->Clear();
          if (!hb) hb = new TH1D (*h1); hb->Clear();
	    
          if (h1) hb->Add(h1);
	  if (h)  hf->Add(h);
	}//end of loop over ligls
    }//end of loop over ppacs

  //Copying the histograms in order to get the appropriate binning
  TH1D *hcopy = (TH1D*) hf->Clone();
  TH1D *hpfns = (TH1D*) hf->Clone();
  hpfns->Clear();
  hpfns->GetYaxis()->SetTitle("");
  hpfns->Reset();
  TH1D *hmaxwellian = (TH1D*)hf->Clone();
  hmaxwellian->Clear();
  hmaxwellian->GetYaxis()->SetTitle("");
  hmaxwellian->Reset();
  TH1D *hcielo = (TH1D*)hf->Clone();
  hcielo->Clear();
  hcielo->GetYaxis()->SetTitle("");
  hcielo->Reset();
  TH1D *oner = (TH1D*) hf->Clone();
  oner->Clear();
  oner->GetYaxis()->SetTitle("");
  oner->Reset();

  //Filling histograms with interpolated values 
  for (int biniter=1;biniter<=hcielo->GetNbinsX();biniter++)
    {
      //Fill PFNS histo
      hpfns->SetBinContent(biniter,spfns->Eval(hpfns->GetBinCenter(biniter)));
      
      //Fill Cielo histo
      hcielo->SetBinContent(biniter,scielo->Eval(hcielo->GetBinCenter(biniter)));
      //hcielo->
      
      //Fill Maxwellian histo
      hmaxwellian->SetBinContent(biniter,smaxwellian->Eval(hmaxwellian->GetBinCenter(biniter)));
    }

  new TCanvas;
  hcielo->Draw();
  return;
  //Scaling histograms by Nfission Neutrons
  hcielo->Scale((nsignalswithcut*nuBar)/(cielo1Neutrons));
  hmaxwellian->Scale((nsignalswithcut*nuBar)/(maxwellianNeutrons));
  
  
  // //Putting points from TGraph of PFNS into a TH1D
  // for (int graphiter=0;graphiter<pfns->GetN();graphiter++)
  //   {
  //     double x = pfns->GetX()[graphiter];
  //     double y = pfns->GetY()[graphiter];
  //     hpfns->SetBinContent(hpfns->FindBin(x),y);
  //   }
  
  // //Putting points from Maxwellian TGraph into a TH1D
  // for (int graphiter=0;graphiter<maxwellian->GetN();graphiter++)
  //   {
  //     double x = maxwellian->GetX()[graphiter];
  //     double y = maxwellian->GetY()[graphiter];
  //     double yerr = maxwellian->GetEY()[graphiter];
  //     hmaxwellian->SetBinContent(hmaxwellian->FindBin(x),y);
  //     //  hmaxwellian->SetBinError(hmaxwellian->FindBin(x),yerr);
  //   }

  // //Putting points from cielo TGraph into a TH1D
  // for (int graphiter=0;graphiter<cielo->GetN();graphiter++)
  //   {
  //     double x = cielo->GetX()[graphiter];
  //     double y = cielo->GetY()[graphiter];
  //     double yerr = cielo->GetEY()[graphiter];
  //     hcielo->SetBinContent(hcielo->FindBin(x),y);
  //     // hcielo->SetBinError(hcielo->FindBin(x),yerr);
  //   }

  //Fill the histogram with ones
  for (int i=1;i<=oner->GetNbinsX();i++)
    {
      oner->SetBinContent(i,1);
    }



  // new TCanvas;
  // hf->Add(hb,-1);
  hcopy->Add(hb,-1);
  // hf->GetYaxis()->SetTitle("counts");
  // hf->GetXaxis()->SetRangeUser(0.010,2.5);
  // hf->GetYaxis()->SetRangeUser(-200.0,8000);
  // hf->GetXaxis()->SetTitle("E_{n}^{out} (MeV)");
  // hf->UseCurrentStyle();
  // hf->GetYaxis()->SetTitleOffset(1.4);
  // gStyle->SetPadTickY(1);
  // gStyle->SetPadTickX(1);
  // hf->Draw();
  
    // int scaleBin = hf->FindBin( 0.240);
  // double scale = hf->GetBinContent( scaleBin) / 2754000;
  // scaleGraph( cielo, scale);
  // scaleGraph( maxwellian, scale);

  // double dataintegral;
  // TAxis *axis = hf->GetXaxis();
  // int bmin = axis->FindBin(0.010);
  // int bmax = axis->FindBin(2.5); 
  // double dataintegral = hf->Integral(bmin,bmax);
  // dataintegral -= hf->GetBinContent(bmin)*(0.010-axis->GetBinLowEdge(bmin))/axis->GetBinWidth(bmin);
  // dataintegral -= hf->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-2.5)/axis->GetBinWidth(bmax);


  // double scaleC = (nsignalswithcut*nuBar)/(cielo1Neutrons);
  // double scaleM = (nsignalswithcut*nuBar)/(maxwellianNeutrons);
  // scaleGraph( cielo, scaleC);
  // scaleGraph( maxwellian, scaleM);
  // cielo->Draw("p");
  // maxwellian->Draw("lp");

  
  
  // hf->SetLineColor(kGreen+2);
  // hf->SetLineWidth(3);
  // hf->SetMarkerColor(kGreen+2);
  // hf->SetMarkerSize(1.3);

  // gPad->SetLogx( kTRUE);
  // gPad->SetLogy( kFALSE);
  
  // TLegend *leg = new TLegend(0.2,0.75,0.25,0.9,"","brNDC");
  // leg->AddEntry(hf,"Chi-Nu Data Prelim E_{n}^{in} = 0.7 - 6.0 MeV","lp"); 
  // leg->AddEntry(cielo,"ENDF/B-VIII.beta.1 CIELO E_{n}^{in} = 1 MeV","lp");
  // leg->AddEntry(maxwellian,"Maxwellian T = 1.42 MeV","lp");
  // leg->SetFillColor(kWhite);
  // leg->SetTextFont(43);
  // leg->SetTextSize(20);
  // leg->SetBorderSize(0);
  // leg->Draw();
  TF1 *f1 = new TF1("f1","[0]*TMath::Sqrt(x)*(1/([1]^(3/2)))*TMath::Exp(-x/[1])",0.010,2.5);
  f1->SetParameter(0,1);
  f1->SetParameter(1,1.424);


  new TCanvas;
  hpfns->GetXaxis()->SetTitle("Neutron Energy (MeV)");
  hpfns->GetYaxis()->SetTitle("PFNS/Max ENDF-B/VII.1");
  hpfns->GetXaxis()->SetRangeUser(0.010,19);
  gPad->SetLogx( kTRUE);
  hpfns->Draw();
  // return;

  new TCanvas;
  hcielo->GetXaxis()->SetTitle("Neutron Energy (MeV)");
  hcielo->GetYaxis()->SetTitle("MCNP(PFNS)/MCNP(Max)");
  TH1D *hcielo2= (TH1D*)hcielo->Clone();
  hcielo->Divide(hmaxwellian);
  hcielo->SetMarkerStyle(22);
  hcielo->SetMarkerColor(kBlue+2);
  hcielo->SetMarkerSize(1.5);
  hcielo->GetXaxis()->SetRangeUser(0.010,2.5);
  gPad->SetLogx( kTRUE);
  hcielo->Draw("p");
  oner->Draw("same");
  
  new TCanvas;
  hcielo2->Divide(hmaxwellian);
  hcielo2->Divide(hpfns);
  hcopy->Divide(hmaxwellian);
  hcopy->Divide(hcielo2);
  for (int j=0;j<=hcopy->GetNbinsX();j++) hcopy->SetBinError(j,0);
  gPad->SetLogx( kTRUE);
  gPad->SetLogy( kFALSE);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  hcopy->GetYaxis()->SetTitle("PFNS (arb. units)");
  hcopy->GetXaxis()->SetRangeUser(0.010,2.5); 
  hcopy->GetXaxis()->SetTitle("Neutron Energy (MeV)");
  // hcopy->GetYaxis()->SetRangeUser(0.0,9500);
  hcopy->GetYaxis()->SetTitleOffset(1.4);
  hcopy->Multiply(f1,1);
  hcopy->SetLineColor(kGreen+2);
  hcopy->SetLineWidth(2);
  hcopy->SetMarkerStyle(22);
  hcopy->SetMarkerColor(kGreen+2);
  hcopy->SetMarkerSize(1.5);
  //hcielo2->Draw();
  hcopy->Draw("p");
  //hmaxwellian->Draw("same");
  //hcielo->Draw();

  // TLegend *leg = new TLegend(0.4,0.75,0.50,0.9,"","brNDC");
  // //leg->AddEntry(hcopy,"Chi-Nu Data Prelim E_{n}^{in} = 0.7 - 6.0 MeV","lp"); 
  // leg->AddEntry(hcopy,"ENDF/B-VIII.beta.1 E_{n}^{in}(data) = 0.7-6.0 MeV","lp");
  // //leg->AddEntry(maxwellian,"Maxwellian T = 1.42 MeV","lp");
  // leg->SetFillColor(kWhite);
  // leg->SetTextFont(43);
  // leg->SetTextSize(20);
  // leg->SetBorderSize(0);
  // leg->Draw();

  oner->SetLineColor(kRed);
  oner->SetLineWidth(2);
  //oner->Draw("same");
  

  //  hb->SetLineColor(kRed);
  //hb->SetLineWidth(2);
  //hb->SetMarkerColor(kRed);
  //hb->Draw("same");



}
