{
  
  /////////////DATA PARAMS/////////////
  const double MinEinc = 0.7;
  const double MaxEinc = 5.0;
  		
  const double MinEout =0.01;
  const double MaxEout = 2.5;
  
  const int NbinsPerDecade= 100;//THIS IS FOR THE OUTPUT!!!

  const bool MakeAPFNS = true;

  const bool PrintDataPoints = false;

  const int ParametersInTheModel=20;

  /////////////MCNP PARAMS//////////////
  const double MCNP_Einc=1.0;//Please select from the following
                             //1.0
                             //2.0
                             //Ultimately we want
                             //1.5   For E range (1MeV - 2MeV)
                             //2.5   For E range (2MeV - 3MeV)
                             //3.5   For E range (3MeV - 4MeV)
                             //4.5   For E range (4MeV - 5MeV)
                             //5.25  For E range (5MeV - 5.5MeV)
                             //5.75  For E range (5.5MeV - 6MeV)
                             //6.25  For E range (6MeV - 6.5MeV)
                             //7.25  For E range (6.5MeV - 8MeV) 
                             //8.75  For E range (8Mev - 9.5MeV)
                             //10.25 For E range (9.5MeV - 11MeV)
                             //11.25 For E range (11MeV - 11.5MeV)
                             //11.75 For E range (11.5MeV - 12MeV)
                             //12.25 For E range (12MeV - 12.5MeV)
                             ///Do we care anymore?
                             //13.75 For E range (12.5MeV - 15MeV)


  const int MCNP_RENORMRANGE=1;//Please select from the following:
                               //1 = Below 100 keV
                               //2 = 100 - 800 keV
                               //3 = 800keV - 1.2MeV
                               //4 = 1.2MeV - 4MeV
                               //5 = Above 4MeV
  
  
  const int WhichMCNP=1;//Please select from the following:
                        //1 = To use the Positive 2 sigma for the Ratio of Ratios
                        //2 = To use the Positive 1 sigma for the Ratio of Ratios
                        //3 = To use the Negative 2 sigma for the Ratio of Ratios  
                        //4 = To use the Negative 1 sigma for the Ratio of Ratios

  // std::cout<<"What is the minimum incoming energy desired (in units of MeV)?"<<std::endl;
  // std::cin>>MinEinc;
  
  // std::cout<<""<<std::endl;

  // std::cout<<"What is the maximum incoming energy desired (in units of MeV)?"<<std::endl;
  // std::cin>>MaxEinc;

  // std::cout<<""<<std::endl;
  
  // std::cout<<"What is the minimum outgoing neutron energy desired (in units of MeV)?"<<std::endl;
  // std::cin>>MinEout;
  
  // std::cout<<""<<std::endl;
  
  // std::cout<<"What is the maximum outgoing neutron energy desired (in units of MeV)?"<<std::endl;
  // std::cin>>MaxEout;
  
  // std::cout<<""<<std::endl;
  
  // std::cout<<"What is the number of bins desired per energy decade (please enter an integer)?"<<std::endl;
  // std::cin>>NbinsPerDecade;
  
  // std::cout<<""<<std::endl;
    
  //TFile * const f = TFile::Open("jgomez2-FinalReplay-u235-ligl2015.root","READ");
  TFile * const f = TFile::Open("jgomez2-u235-cleaned2x-complete-sum.root","READ");
  //TFile *f = TFile::Open("./data/jgomez2-21870-21871-21870.root","READ");

  f->cd("histos/DoubleCoinc");
  
  
  ////////////////////////////////////////////////////////
  /////Grab and sum foreground and background histos/////
  ///////////////////////////////////////////////////////
  TH2 *hf;
  TH2 *hftemp;
  char hfname[128];
  
  TH2 *hb;
  TH2 *hbtemp;
  char hbname[128];
  
  for (int l=1;l<=22;l++)
    {
      if (l==3 || l==5 || l==16) continue; //Skip ligl 3 cuz it sucks
      for (int p=1;p<=10;p++)
  	{
  	  sprintf(hfname,"dc1_3_poly_2eth_t00_ppac%02i_ligl%02i",p,l);//FG
  	  hftemp = (TH2*)gDirectory->FindObjectAny(hfname);
	  hftemp->Sumw2();
  	  if (!hf) hf=(TH2*)hftemp->Clone();
  	  if (hf) hf->Add(hftemp);
	  
	  sprintf(hbname,"dc1_3_back_poly_2eth_t00_ppac%02i_ligl%02i",p,l);//BG
	  hbtemp = (TH2*)gDirectory->FindObjectAny(hbname);
	  if (!hb) hb=(TH2*)hbtemp->Clone();
	  if (hb) hb->Add(hbtemp);
  	}//end of loop over ppacs
    }//End of loop over ligls
  /////////////////////////////////////////
  /////END OF SUMMING FG AND BG HISTOS/////
  /////////////////////////////////////////

  gStyle=gStylePublication;
  
  

  //////////////////////////////////////////////////////////////
  //////////Making evenly space log bins for new plots//////////
  /////////////////////////////////////////////////////////////
  const double nDecades = log10(MaxEout) - log10(MinEout);
  const int nBins = NbinsPerDecade*nDecades+1;
  Double_t x[nBins+1];// = {0};  
  for(int i=0;i<=nBins;i++)
    {
      double id = static_cast<double>(i);
      x[i] = pow(10.,log10(MinEout)+id/NbinsPerDecade);
    }

  //Create the empty 1D histos
  TH1D *hf1d = new TH1D("hf1d","hf1d",nBins,x);//Foreground plot
  hf1d->Sumw2();
  TH1D *hb1d = new TH1D("hb1d","hb1d",nBins,x);//Background plot
  hb1d->Sumw2();
  ///////////////////////////////////////////////////////////////////
  //////////Done making evenly space log bins for new plots//////////
  //////////////////////////////////////////////////////////////////

  
  //////////////////////////////////////////////////////////////////////////////
  //////////////Do various operations to project FG down////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  TH2* hfcopy =(TH2*)hf->Clone(); 
  projectiony = hfcopy->ProjectionY("py",
				    hfcopy->GetXaxis()->FindBin(MinEinc),
				    hfcopy->GetXaxis()->FindBin(MaxEinc));

  double fgFractions[hf1d->GetNbinsX()][projectiony->GetNbinsX()];

  for (int rows=0;rows<hf1d->GetNbinsX();rows++)
    {
      for (int cols=0;cols<projectiony->GetNbinsX();cols++)
	{
	  fgFractions[rows][cols]=0.;
	}
    }
  /////////////////////////////////////
  //////////Making Fractions //////////
  ////////////////////////////////////
  
  
  int srcBin=1;
  int dstBin=1;

  const int nSrcBins=projectiony->GetNbinsX();
  const int nDstBins=nBins;

  while (srcBin<nSrcBins && dstBin<nDstBins)
    //while (srcBin<=maxSrcBin && dstBin<=nBins)
    {
      
      const double srcLow = projectiony->GetBinLowEdge(srcBin);
      const double srcUpp = projectiony->GetBinLowEdge(srcBin+1);
      const double dstLow = hf1d->GetXaxis()->GetBinLowEdge(dstBin);
      const double dstUpp = hf1d->GetXaxis()->GetBinLowEdge(dstBin+1);

            
      std::cout<<srcBin<<"\t"<<dstBin<<std::endl;
      
      // check source bin overlaps with destination bin                                  
      // if not move on                                                                    
      if (srcUpp < dstLow) {
	++srcBin;
	continue;
      }
      if (srcLow > dstUpp) {
	++dstBin;
	continue;
      }
      
      int nextDstBin = dstBin;
      int nextSrcBin = srcBin;
      double fraction = 0.;
      
      if (srcLow <= dstLow && srcUpp >= dstUpp) {
	// source bin fully spans destination bin
	fraction = (dstUpp - dstLow) / (srcUpp - srcLow);
	++nextDstBin;
	//std::cout<<"Made it in 1"<<std::endl;
      } else if (srcLow >= dstLow && srcUpp <= dstUpp) {
	// source bin fully inside destination bin
	fraction = 1.;
	++nextSrcBin;
	//std::cout<<"Made it in 2"<<std::endl;
      } else if (srcLow <  dstLow && srcUpp <  dstUpp) {
	// source bin overlaps start of destination bin
	fraction = (srcUpp - dstLow) / (srcUpp - srcLow);
	//std::cout<<"Made it in 3 with fraction "<<(srcUpp - dstLow) / (srcUpp - srcLow)<<std::endl;
	++nextSrcBin;
      } else if (srcLow >  dstLow && srcUpp >  dstUpp) {
	// source bin overlaps end of destination bin
	fraction = (dstUpp - srcLow) / (srcUpp - srcLow);
	//std::cout<<"Made it in 4 with fraction "<< (dstUpp - srcLow) / (srcUpp - srcLow)<<std::endl;
	++nextDstBin;
      }
      //std::cout<<"I made it here where dst bin was "<<dstBin<<"\t and srcBin was "<<srcBin<<std::endl;
      fgFractions[dstBin-1][srcBin-1]=fraction;
      dstBin = nextDstBin;
      srcBin = nextSrcBin;
      
    }
  
 

  /////////////////////////////////////////////
  //////////End of Making Fractions //////////
  ////////////////////////////////////////////

  // for (int row=0;row<nDstBins;row++)
  //   {
  //     for (int col=0;col<nSrcBins;col++)
  // 	{
  // 	  if (fgFractions[row][col]!=0) std::cout<<"First index is: "<<row<<"  Second index is:  "<<col<<"="<<fgFractions[row][col]<<std::endl;
  // 	}
  //   }
  // return;




  ///////////////////////////////////////////////////////////////////////////////
  /////Grabbing error and bin content arrays for easier transplanting of info///
  //////////////////////////////////////////////////////////////////////////////
  TArrayD *Errors = projectiony->GetSumw2();
  // Double_t *fgErrors = Errors->GetArray();
  Double_t *fgValues = projectiony->GetArray();
  
  TArrayD *newErrors = hf1d->GetSumw2();
  //Double_t *newfgErrors = newErrors->GetArray();  
  Double_t *newfgValues = hf1d->GetArray();
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  
  //////////////////////////////////////////////////////////////////////////////
  //////Now using those arrays, put the info from projection histo to new histo/
  //////////////////////////////////////////////////////////////////////////////
  for (int newbins=1;
       newbins<=hf1d->GetNbinsX();
       newbins++)
    {
      for (int oldbins=projectiony->FindBin(MinEout);
	   oldbins<=projectiony->FindBin(MaxEout);
	   oldbins++)
	{
	  newfgValues[newbins]+=fgValues[oldbins]*fgFractions[newbins-1][oldbins-1];
	  
	  newErrors->SetAt((newErrors->GetAt(newbins))+
			   (Errors->GetAt(oldbins)*
			    fgFractions[newbins-1][oldbins-1]*
			    fgFractions[newbins-1][oldbins-1]),newbins);
	}
    }//end of loop over new bins
  //////////////////////////////////////////////////////////////////////////////
  //////////END OF DOING STUFF TO THE FG////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

 
  //////////////////////////////////////////////////////////////////////////////
  //////////////Do various operations to project BG down////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  TH2* hbcopy=(TH2*)hb->Clone();
  bgprojectiony = hbcopy->ProjectionY("bgpy",
  				      hbcopy->GetXaxis()->FindBin(MinEinc),
  				      hbcopy->GetXaxis()->FindBin(MaxEinc));
  



  ///////////////////////////////////////////////////////////////////////////////
  /////Grabbing error and bin content arrays for easier transplanting of info///
  //////////////////////////////////////////////////////////////////////////////
  TArrayD *BGErrors = bgprojectiony->GetSumw2();
  //Double_t *bgErrors = BGErrors->GetArray();
  Double_t *bgValues = bgprojectiony->GetArray();
  
  TArrayD *newBGErrors = hb1d->GetSumw2();
  //Double_t *newbgErrors = newBGErrors->GetArray();  
  Double_t *newbgValues = hb1d->GetArray();
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  

  //////////////////////////////////////////////////////////////////////////////
  //////Now using those arrays, put the info from projection histo to new histo/
  //////////////////////////////////////////////////////////////////////////////
  for (int newbins=1;
       newbins<=hb1d->GetNbinsX();
       newbins++)
    {
      for (int oldbins=bgprojectiony->FindBin(MinEout);
	   oldbins<=bgprojectiony->FindBin(MaxEout);
	   oldbins++)
	{
	  newbgValues[newbins]+=bgValues[oldbins]*fgFractions[newbins-1][oldbins-1];
	  
	  //newbgErrors[newbins]+=bgErrors[oldbins]
	  // *fgFractions[newbins-1][oldbins-1]
	  // *fgFractions[newbins-1][oldbins-1];

	  newBGErrors->SetAt((newBGErrors->GetAt(newbins))+
			     (BGErrors->GetAt(oldbins)*
			      fgFractions[newbins-1][oldbins-1]*
			      fgFractions[newbins-1][oldbins-1]),newbins);
	  
	}
    }//end of loop over new bins
  //////////////////////////////////////////////////////////////////////////////
  //////////END OF DOING STUFF TO THE BG////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////



  //////////////////////////////////////////////////////////////////////////////
  ////////////////START MAKING PRETTY PLOTS FOR INFOS SAKE//////////////////////
  //////////////////////////////////////////////////////////////////////////////
  hb1d->SetLineColor(kRed);
  hf1d->SetLineColor(kGreen+2);
  hf1d->GetYaxis()->SetTitle("Counts");
  hb1d->GetYaxis()->SetTitle("Counts");
  hf1d->GetXaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
  hb1d->GetXaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
  //hf1d->GetXaxis()->SetTitleOffset(1.8);
    
  ////////////////////////////////////////////
  //////////MAKING FG PLOTS FOR TALK//////////
  ////////////////////////////////////////////
  TCanvas *c1 = new TCanvas("c1","c1",1200,1200);
  TPad *p1 = new TPad("p1", "p1", 0.0, 0.55, 1., 1, 0);
  p1->SetTickx(1);
  p1->SetTicky(1);
  p1->Draw();

  TPad *p2 = new TPad("p2", "p2", 0.0, 0.02, 1, 0.5, 0);
  p2->SetTickx(1);
  p2->SetTicky(1);
  p2->Draw();

  hf->GetYaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
  hf->GetYaxis()->SetRangeUser(MinEout,MaxEout);
  hf->GetXaxis()->SetTitle("Incident Neutron Energy (MeV)");
  hf->GetXaxis()->SetRangeUser(MinEinc,MaxEinc);

  p1->cd();hf->Draw("colz"); gPad->SetLogz(kTRUE);gPad->SetLogy(kTRUE);
  gPad->SetLogx(kTRUE);
  p2->cd();hf1d->Draw(); gPad->SetLogx(kTRUE);
  char mytex1[128];
  sprintf(mytex1,"E_{n}^{in} = %0.1f - %0.1f MeV",MinEinc,MaxEinc);
  tex1=new TLatex(0.7,0.75,mytex1);
  tex1->SetNDC();
  tex1->SetTextFont(43);
  tex1->SetTextSize(22);
  tex1->SetTextColor(kRed);
  tex1->Draw();
  ///////////////////////////////////////////////////
  //////////END OF MAKING BG PLOTS FOR TALK//////////
  ///////////////////////////////////////////////////

  
  ////////////////////////////////////////////
  //////////MAKING BG PLOTS FOR TALK//////////
  ////////////////////////////////////////////
  TCanvas *c2 = new TCanvas("c2","c2",1200,1200);
  c2->cd();
  TPad *p3 = new TPad("p3", "p3", 0.0, 0.55, 1., 1, 0);
  p3->SetTickx(1);
  p3->SetTicky(1);
  p3->Draw();

  TPad *p4 = new TPad("p4", "p4", 0.0, 0.02, 1, 0.5, 0);
  p4->SetTickx(1);
  p4->SetTicky(1);
  p4->Draw();

  hb->GetYaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
  hb->GetYaxis()->SetRangeUser(MinEout,MaxEout);
  hb->GetXaxis()->SetTitle("Incident Neutron Energy (MeV)");
  hb->GetXaxis()->SetRangeUser(MinEinc,MaxEinc);

  // hb->GetXaxis()->SetRangeUser(MinEinc,MaxEinc);
  // hb->GetYaxis()->SetRangeUser(MinEout,MaxEout);
  p3->cd();hb->Draw("colz"); gPad->SetLogz(kTRUE);gPad->SetLogy(kTRUE);
  gPad->SetLogx(kTRUE);
  char mytex2[128];
  sprintf(mytex2,"E_{n}^{in} = %0.1f - %0.1f MeV",MinEinc,MaxEinc);
  p4->cd();hb1d->Draw(); gPad->SetLogx(kTRUE);
  tex2=new TLatex(0.7,0.75,mytex2);
  tex2->SetNDC();
  tex2->SetTextFont(43);
  tex2->SetTextSize(22);
  tex2->SetTextColor(kRed);
  tex2->Draw();

  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////END OF MAKING DATA AND BG PLOTS////////////////////
  //////////////////////////////////////////////////////////////////////////////


  
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  /////////////////FORWARD ANALYSIS SECTION/////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  
  //////////////////////////////////////////////////////////////////
  //////////Need to extract number of fissions for scaling//////////
  //////////////////////////////////////////////////////////////////
  char nocuthisto[128];
  TH1D *nochisto;
  
  Double_t nsignals=0.;
  Double_t integralwidth=50;
  
  ///NEED TO CONVERT FROM ENERGY TO TIME
  Double_t beta_max=0;
  Double_t beta_min=0;
  Double_t NeutronMass=939.57;
  Double_t ell=21.5;
  Double_t timeMin=0.;
  Double_t timeMax=0.;
  Double_t cee=299792458;//in m/s

  //BETA = SQRT(T^2+(2MT))/(m+T)
  //t= l/BETA*c - l/c
  beta_max = TMath::Sqrt((MaxEinc*MaxEinc)+(2*NeutronMass*MaxEinc))/(NeutronMass+MaxEinc);
  timeMax = (ell/(beta_max*cee))-(ell/cee);
  timeMax=timeMax/(1e-9);

  beta_min = TMath::Sqrt((MinEinc*MinEinc)+(2*NeutronMass*MinEinc))/(NeutronMass+MinEinc);
  timeMin = (ell/(beta_min*cee))-(ell/cee);
  timeMin=timeMin/(1e-9);
  
  
  // std::cout<<timeMax<<std::endl;
  //return;


  
  /////////////////////////
  /////WHAT I AM DOING/////
  /////////////////////////
  //I am going into doublecoinc/background, there you can find a singles histo
  //for a given ppac. I am looping over all of the ppac histos and taking the 
  //integral from -50ns to 0ns. I am saying that this is all a flat alpha bckgd.
  //I am then assuming that the alpha background is flat in time, so I then 
  //subtract that flat background from the total integral of that histogram.
  //DO NOT FORGET TO MULTIPLY BY BIN WIDTH!!!
  ////////////////////////////////////////////////////////////////////////////
  f->cd("histos/DoubleCoinc/background");
  for (int ppac=1;ppac<=10;ppac++)
    {
      sprintf(nocuthisto,"dc1_3_back_sngl_t00_ppac%02i",ppac);
      
      nochisto = (TH1D*)gDirectory->FindObjectAny(nocuthisto);
      TAxis *axis = nochisto->GetXaxis();
      int bmin = axis->FindBin(-50);
      int bmax = axis->FindBin(0.0);
  
      int lowerlimit= axis->FindBin(timeMin);
      int upperlimit= axis->FindBin(timeMax);
      int binrange = (upperlimit-lowerlimit)+1;
    
      double bgintegral=nochisto->Integral(bmin,bmax);
      bgintegral = (bgintegral/integralwidth)*binrange;
      
      nsignals+=nochisto->Integral(lowerlimit,upperlimit)-bgintegral;
    }

  //std::cout<<"The estimated number of fissions was\t"<<nsignals<<std::endl;
  //return;
  //////////////////////////////////////////////////////////////////
  //////////END OF SCALING SECTION//////////////////////////////////
  //////////////////////////////////////////////////////////////////


  /////////////////////////////////////////////
  /////CREATE THE HISTOGRAMS APPROPRIATELY/////
  /////////////////////////////////////////////

  TH1 *hfa = (TH1*)hf1d->Clone(); //Clone the 1D Projected FG
  hfa->Add(hb1d,-1);//Subtract the 1D Projected BG

  /////////////////////////////////////////////////////////
  //////////CREATE AND ADD UP THE MCNP HISTOGRAMS//////////
  /////////////////////////////////////////////////////////

  //Positive Sigma Histograms//
  //OneSigma First
  TH1D *hp1mcnp = new TH1D("hp1mcnp","hp1mcnp",nBins,x);//Clone the FG to get same bins
  hp1mcnp->SetLineColor(kGreen+2);
  hp1mcnp->GetYaxis()->SetTitle("Counts");
  hp1mcnp->GetXaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
  hp1mcnp->GetXaxis()->SetTitleOffset(1.8);
  hp1mcnp->Sumw2();

  TH1D *hp2mcnp = new TH1D("hp2mcnp","hp2mcnp",nBins,x);//Clone the FG to get same bins
  hp2mcnp->SetLineColor(kCyan+2);
  hp2mcnp->GetYaxis()->SetTitle("Counts");
  hp2mcnp->GetXaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
  hp2mcnp->GetXaxis()->SetTitleOffset(1.8);
  hp2mcnp->Sumw2();

  //Negative Sigma Histograms//
  //OneSigma First
  TH1D *hn1mcnp = new TH1D("hn1mcnp","hn1mcnp",nBins,x);//Clone the FG to get same bins
  hn1mcnp->SetLineColor(kMagenta+2);
  hn1mcnp->GetYaxis()->SetTitle("Counts");
  hn1mcnp->GetXaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
  hn1mcnp->GetXaxis()->SetTitleOffset(1.8);
  hn1mcnp->Sumw2();

  TH1D *hn2mcnp = new TH1D("hn2mcnp","hn2mcnp",nBins,x);//Clone the FG to get same bins
  hn2mcnp->SetLineColor(kRed+2);
  hn2mcnp->GetYaxis()->SetTitle("Counts");
  hn2mcnp->GetXaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
  hn2mcnp->GetXaxis()->SetTitleOffset(1.8);
  hn2mcnp->Sumw2();

  


  /////////////////////////////////////////////////
  /////Open the available evaluated root files/////
  /////////////////////////////////////////////////
  if (MCNP_Einc==1.0)
    {
      if (MCNP_RENORMRANGE==1)
	{
	  //TFile *p2sigma = TFile::Open("JaimesTest.root","READ");
	  TFile *p2sigma = TFile::Open("pos2sigbelow100keveinc1mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sigbelow100keveinc1mev.root","READ");
	  
	  TFile *n2sigma = TFile::Open("neg2sigbelow100keveinc1mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sigbelow100keveinc1mev.root","READ");
	}
      else if (MCNP_RENORMRANGE==2)
	{
	  TFile *p2sigma = TFile::Open("pos2sig100to800keveinc1mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sig100to800keveinc1mev.root","READ");
	  
	  TFile *n2sigma = TFile::Open("neg2sig100to800keveinc1mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sig100to800keveinc1mev.root","READ");
	}
      else if (MCNP_RENORMRANGE==3)
	{
	  TFile *p2sigma = TFile::Open("pos2sig800to1pt2meveinc1mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sig800to1pt2meveinc1mev.root","READ");
				       
	  TFile *n2sigma = TFile::Open("neg2sig800to1pt2meveinc1mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sig800to1pt2meveinc1mev.root","READ");
	}
      else if (MCNP_RENORMRANGE==4)
	{
	  TFile *p2sigma = TFile::Open("pos2sig1pt2to4meveinc1mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sig1pt2to4meveinc1mev.root","READ");
	  
	  TFile *n2sigma = TFile::Open("neg2sig1pt2to4meveinc1mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sig1pt2to4meveinc1mev.root","READ");
	}
      else if (MCNP_RENORMRANGE==5)
	{
	  TFile *p2sigma = TFile::Open("pos2sigabove4meveinc1mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sigabove4meveinc1mev.root","READ");
	  
	  TFile *n2sigma = TFile::Open("neg2sigabove4meveinc1mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sigabove4meveinc1mev.root","READ");
	}
    } else if (MCNP_Einc==2.0)
    {
      if (MCNP_RENORMRANGE==1)
	{
	  TFile *p2sigma = TFile::Open("pos2sigbelow100keveinc2mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sigbelow100keveinc2mev.root","READ");
	  
	  TFile *n2sigma = TFile::Open("neg2sigbelow100keveinc2mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sigbelow100keveinc2mev.root","READ");
	}
      else if (MCNP_RENORMRANGE==2)
	{
	  TFile *p2sigma = TFile::Open("pos2sig100to800keveinc2mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sig100to800keveinc2mev.root","READ");
	  
	  TFile *n2sigma = TFile::Open("neg2sig100to800keveinc2mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sig100to800keveinc2mev.root","READ");
	}
      else if (MCNP_RENORMRANGE==3)
	{
	  TFile *p2sigma = TFile::Open("pos2sig800to1pt2meveinc2mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sig800to1pt2meveinc2mev.root","READ");
				       
	  TFile *n2sigma = TFile::Open("neg2sig800to1pt2meveinc2mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sig800to1pt2meveinc2mev.root","READ");
	}
      else if (MCNP_RENORMRANGE==4)
	{
	  TFile *p2sigma = TFile::Open("pos2sig1pt2to4meveinc2mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sig1pt2to4meveinc2mev.root","READ");
	  
	  TFile *n2sigma = TFile::Open("neg2sig1pt2to4meveinc2mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sig1pt2to4meveinc2mev.root","READ");
	}
      else if (MCNP_RENORMRANGE==5)
	{
	  TFile *p2sigma = TFile::Open("pos2sigabove4meveinc2mev.root","READ");
	  TFile *p1sigma = TFile::Open("pos1sigabove4meveinc2mev.root","READ");
	  
	  TFile *n2sigma = TFile::Open("neg2sigabove4meveinc2mev.root","READ");
	  TFile *n1sigma = TFile::Open("neg1sigabove4meveinc2mev.root","READ");
	}
    }

  //Grab pos 2sigma simulated histos//
  char h2sname[128];
  TH1D* h2s;
  TH1D* htemp2s = new TH1D;
  p2sigma->cd();
  double p2sneutrons=Nevents->GetBinContent(1);//Get number of fissions
  for (int p=1;p<=10;p++)
    {
      for (int l=1;l<=22;l++)
        {
          if (l==3) continue;//Skip over ligl3
	  sprintf(h2sname,"uac_1de_yield_%i_%i",p,l);
          htemp2s = (TH1D*)gDirectory->FindObjectAny(h2sname);
	  htemp2s->Sumw2();
          if (!h2s) h2s=(TH1D*)htemp2s->Clone();
	  if (h2s) h2s->Add(htemp2s);
	}
    }

  //Grab pos 1sigma simulated histos//
  char h1sname[128];
  TH1D* h1s;
  TH1D* htemp1s = new TH1D;
  p1sigma->cd();
  double p1sneutrons=Nevents->GetBinContent(1);//Get number of fissions
  for (int p=1;p<=10;p++)
    {
      for (int l=1;l<=22;l++)
        {
          if (l==3) continue;//Skip over ligl3
	  sprintf(h1sname,"uac_1de_yield_%i_%i",p,l);
          htemp1s = (TH1D*)gDirectory->FindObjectAny(h1sname);
	  htemp1s->Sumw2();
          if (!h1s) h1s=(TH1D*)htemp1s->Clone();
	  if (h1s) h1s->Add(htemp1s);
	}
    }
  
  //Grab neg 2 sigma simulated histos//
  char hn2sname[128];
  TH1D* hn2s;
  TH1D* hntemp2s;
  n2sigma->cd();
  double n2sneutrons=Nevents->GetBinContent(1);//Get number of fissions
  for (int p=1;p<=10;p++)
    {
      for (int l=1;l<=22;l++)
        {
          if (l==3) continue;
	  sprintf(hn2sname,"uac_1de_yield_%i_%i",p,l);
          hntemp2s = (TH1D*)gDirectory->FindObjectAny(hn2sname);
	  hntemp2s->Sumw2();
          if (!hn2s) hn2s=(TH1D*)hntemp2s->Clone();
	  if (hn2s) hn2s->Add(hntemp2s);
	}
    }

  //Grab neg 1 sigma simulated histos//
  char hn1sname[128];
  TH1D* hn1s;
  TH1D* hntemp1s;
  n1sigma->cd();
  double n1sneutrons=Nevents->GetBinContent(1);//Get number of fissions
  for (int p=1;p<=10;p++)
    {
      for (int l=1;l<=22;l++)
        {
          if (l==3) continue;
	  sprintf(hn1sname,"uac_1de_yield_%i_%i",p,l);
          hntemp1s = (TH1D*)gDirectory->FindObjectAny(hn1sname);
	  hntemp1s->Sumw2();
          if (!hn1s) hn1s=(TH1D*)hntemp1s->Clone();
	  if (hn1s) hn1s->Add(hntemp1s);
	}
    }
  
  ///////////////////////////////////////////////////////////////////////////////
  /////Grabbing error and bin content arrays for easier transplanting of info///
  //////////////////////////////////////////////////////////////////////////////
  
  //First do the positive 2 sigma//
  TArrayD *pos2sMCNPErrors = h2s->GetSumw2();
  //Double_t *posmcnpErrors = posMCNPErrors->GetArray();
  Double_t *pos2smcnpValues = h2s->GetArray();
    
  TArrayD *newMCNP2sErrors  = hp2mcnp->GetSumw2();
  //Double_t *newmcnpErrors = newMCNPErrors->GetArray();  
  Double_t *newmcnp2sValues = hp2mcnp->GetArray();

  //Then do the positive 1 sigma//
  TArrayD *pos1sMCNPErrors = h1s->GetSumw2();
//   //Double_t *posmcnpErrors = posMCNPErrors->GetArray();
  Double_t *pos1smcnpValues = h1s->GetArray();
    
  TArrayD *newMCNP1sErrors  = hp1mcnp->GetSumw2();
//   //Double_t *newmcnpErrors = newMCNPErrors->GetArray();  
  Double_t *newmcnp1sValues = hp1mcnp->GetArray();
  
  
  //Next do the negative 2 sigma//
  TArrayD *neg2sMCNPErrors  = hn2s->GetSumw2();
  //Double_t *negmcnpErrors = negMCNPErrors->GetArray();
  Double_t *neg2smcnpValues = hn2s->GetArray();
  
  TArrayD *newn2sMCNPErrors = hn2mcnp->GetSumw2();
  //Double_t *newnmcnpErrors = newnMCNPErrors->GetArray();  
  Double_t *newn2smcnpValues = hn2mcnp->GetArray();

  //Lastly do the negative 1 sigma//
  TArrayD *neg1sMCNPErrors  = hn1s->GetSumw2();
  //Double_t *negmcnpErrors = negMCNPErrors->GetArray();
  Double_t *neg1smcnpValues = hn1s->GetArray();
  
  TArrayD *newn1sMCNPErrors = hn1mcnp->GetSumw2();
  //Double_t *newnmcnpErrors = newnMCNPErrors->GetArray();  
  Double_t *newn1smcnpValues = hn1mcnp->GetArray();

  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  

  //////////////////////////////////////////////////////////////////////////////
  //////Now using those arrays, put the info from projection histo to new histo/
  //////////////////////////////////////////////////////////////////////////////
  for (int newbins=1;
       newbins<=hp2mcnp->GetNbinsX();
       newbins++)
    {
      for (int oldbins=h2s->FindBin(MinEout);
	   oldbins<=h2s->FindBin(MaxEout);
	   oldbins++)
	{
	  newmcnp2sValues[newbins]+=pos2smcnpValues[oldbins]
	    *fgFractions[newbins-1][oldbins-1];//Positive 2 sigma

	  newmcnp1sValues[newbins]+=pos1smcnpValues[oldbins]
 	    *fgFractions[newbins-1][oldbins-1];//Positive 1 sigma
	  
   	  newn2smcnpValues[newbins]+=neg2smcnpValues[oldbins]
	    *fgFractions[newbins-1][oldbins-1];//Negative 2 sigma

	  newn1smcnpValues[newbins]+=neg1smcnpValues[oldbins]
	    *fgFractions[newbins-1][oldbins-1];//Negative 1 sigma


	  newMCNP2sErrors->SetAt((newMCNP2sErrors->GetAt(newbins))+
				 (pos2sMCNPErrors->GetAt(oldbins)*
				  fgFractions[newbins-1][oldbins-1]*
				  fgFractions[newbins-1][oldbins-1]),newbins);
	                          //Positive 2 sigma errors

	  newMCNP1sErrors->SetAt((newMCNP1sErrors->GetAt(newbins))+
				 (pos1sMCNPErrors->GetAt(oldbins)*
				  fgFractions[newbins-1][oldbins-1]*
				  fgFractions[newbins-1][oldbins-1]),newbins);
	                           //Positive 1 sigma errors
	  
	  newn2sMCNPErrors->SetAt((newn2sMCNPErrors->GetAt(newbins))+
				  (neg2sMCNPErrors->GetAt(oldbins)*
				   fgFractions[newbins-1][oldbins-1]*
				   fgFractions[newbins-1][oldbins-1]),newbins);
	                           //Negative 2 sigma errors

	  newn1sMCNPErrors->SetAt((newn1sMCNPErrors->GetAt(newbins))+
				  (neg1sMCNPErrors->GetAt(oldbins)*
				   fgFractions[newbins-1][oldbins-1]*
				   fgFractions[newbins-1][oldbins-1]),newbins);
	                           //Negative 1 sigma errors
	}
    }//end of loop over new bins
  //////////////////////////////////////////////////////////////////////////////
  //////////END OF SUMMING MCNP PLOTS///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  
  ///////////////////////////////////////////////////
  //////////SCALING AND BEAUTIFYING SECTION//////////
  ///////////////////////////////////////////////////
  Double_t nuBar = 2.4;//This is a tabulated value somewhere

  //Pos2Sigma
  hp2mcnp->SetLineColor(kBlue+2);
  hp2mcnp->SetMarkerColor(kBlue+2);
  hp2mcnp->SetLineWidth(2);
  hp2mcnp->GetXaxis()->SetRangeUser(MinEout,MaxEout);
  //hp2mcnp->Scale((nsignals*nuBar)/(p2sneutrons));//Scaling histogram to...
  //match data with ~number of fission neutrons
  hp2mcnp->Scale(1./hp2mcnp->Integral());

  //Pos1Sigma
  hp1mcnp->SetLineColor(kCyan+2);
  hp1mcnp->SetMarkerColor(kCyan+2);
  hp1mcnp->SetLineWidth(2);
  hp1mcnp->GetXaxis()->SetRangeUser(MinEout,MaxEout);
//   //hp1mcnp->Scale((nsignals*nuBar)/(p1sneutrons));//Scaling histogram to...
//   //match data with ~number of fission neutrons
  hp1mcnp->Scale(1./hp1mcnp->Integral());

  //Neg2Sigma
  hn2mcnp->SetLineColor(kRed+2);
  hn2mcnp->SetMarkerColor(kRed+2);
  hn2mcnp->SetLineWidth(2);
  hn2mcnp->GetXaxis()->SetRangeUser(MinEout,MaxEout);
  //hn2mcnp->Scale((nsignals*nuBar)/(n2sneutrons));//Same scaling as above
  hn2mcnp->Scale(1./hn2mcnp->Integral());

  //Neg1Sigma
  hn1mcnp->SetLineColor(kMagenta+2);
  hn1mcnp->SetMarkerColor(kMagenta+2);
  hn1mcnp->SetLineWidth(2);
  hn1mcnp->GetXaxis()->SetRangeUser(MinEout,MaxEout);
  //hn1mcnp->Scale((nsignals*nuBar)/(n1sneutrons));//Same scaling as above
  hn1mcnp->Scale(1./hn1mcnp->Integral());
  
  
  hfa->Scale(1./hfa->Integral());



  ///////////////////////////////////////////////////////////
  //////////////////CALCULATING A CHI^2//////////////////////
  ///////////////////////////////////////////////////////////
  double Chi2P1S=0.;//Chi2 for Positive 1 sigma
  double Chi2P2S=0.;//Chi2 for Positive 2 sigma
  double Chi2N1S=0.;//Chi2 for Negative 1 sigma
  double Chi2N2S=0.;//Chi2 for Negative 2 sigma
  for (int ex=1;ex<hfa->GetNbinsX();ex++)
    {
      //Pos 2 Sigma
      double tempchi2p2s=0.0;
      tempchi2p2s=(hfa->GetBinContent(ex) - hp2mcnp->GetBinContent(ex))
	*(hfa->GetBinContent(ex) - hp2mcnp->GetBinContent(ex));
      tempchi2p2s=tempchi2p2s/((hfa->GetBinError(ex)*hfa->GetBinError(ex))
			     +(hp2mcnp->GetBinError(ex)*hp2mcnp->GetBinError(ex)));
      Chi2P2S+=tempchi2p2s;

      //Pos 1 Sigma
      double tempchi2p1s=0.0;
   tempchi2p1s=(hfa->GetBinContent(ex) - hp1mcnp->GetBinContent(ex))
	*(hfa->GetBinContent(ex) - hp1mcnp->GetBinContent(ex));
      tempchi2p1s=tempchi2p1s/((hfa->GetBinError(ex)*hfa->GetBinError(ex))
			     +(hp1mcnp->GetBinError(ex)*hp1mcnp->GetBinError(ex)));
      Chi2P1S+=tempchi2p1s;

      
      //Neg 2 Sigma
      double tempchi2n2s=0.0;
      tempchi2n2s=(hfa->GetBinContent(ex) - hn2mcnp->GetBinContent(ex))
      	*(hfa->GetBinContent(ex) - hn2mcnp->GetBinContent(ex));
      tempchi2n2s=tempchi2n2s/((hfa->GetBinError(ex)*hfa->GetBinError(ex))
      			     +(hn2mcnp->GetBinError(ex)*hn2mcnp->GetBinError(ex)));
      Chi2N2S+=tempchi2n2s;

      //Neg 1 Sigma
      double tempchi2n1s=0.0;
      tempchi2n1s=(hfa->GetBinContent(ex) - hn1mcnp->GetBinContent(ex))
      	*(hfa->GetBinContent(ex) - hn1mcnp->GetBinContent(ex));
      tempchi2n1s=tempchi2n1s/((hfa->GetBinError(ex)*hfa->GetBinError(ex))
      			     +(hn1mcnp->GetBinError(ex)*hn1mcnp->GetBinError(ex)));
      Chi2N1S+=tempchi2n1s;

      
    }
  ///////////////////////////////////////////////////////////
  //////////END OF CALCULATING A CHI^2///////////////////////
  ///////////////////////////////////////////////////////////
 

  
  new TCanvas;
  gPad->SetLogx(kTRUE);
  hfa->Draw();
  hp2mcnp->Draw("same");
  hn2mcnp->Draw("same");
  hp1mcnp->Draw("same");
  hn1mcnp->Draw("same");
  
  char firstline[128];
  char secondline[128];
  
  sprintf(firstline,"Neudecker Eval. Einc=%2.1fMeV",MCNP_Einc);
  if(MCNP_RENORMRANGE==1) sprintf(secondline,"+2#sigma <100keV norm");
  else if(MCNP_RENORMRANGE==2) sprintf(secondline,"+2#sigma 100-800keV norm");
  else if(MCNP_RENORMRANGE==3) sprintf(secondline,"+2#sigma 800keV-1.2MeV norm");
  else if(MCNP_RENORMRANGE==4) sprintf(secondline,"+2#sigma 1.2-4MeV norm");
  else if(MCNP_RENORMRANGE==5) sprintf(secondline,"+2#sigma >4MeV norm");
  
  TLegend *leg = new TLegend(0.25,0.65,0.40,0.85,"","brNDC");
  leg->AddEntry(hfa,"Chi-Nu Data Prelim.","lp");
  leg->AddEntry(hp2mcnp,TString::Format("#splitline{%s}{%s}",
				firstline,secondline),"lp");

  //MY WORK AROUND/////////////////////////////
  //leg->AddEntry(hp2mcnp,firstline,"lp");
  //leg->AddEntry((TObject*)0,secondline,"");
  /////////////////////////////////////////////
  leg->AddEntry(hp1mcnp,"Neudecker Eval. +#sigma","lp");
  leg->AddEntry(hn1mcnp,"Neudecker Eval. -#sigma","lp");
  leg->AddEntry(hn2mcnp,"Neudecker Eval. -2#sigma","lp");
  leg->SetFillColor(kWhite);
  leg->SetTextFont(43);
  leg->SetTextSize(18);
  leg->SetBorderSize(0);
  leg->Draw();
  
  tex3=new TLatex(0.7,0.75,mytex2);
  tex3->SetNDC();
  tex3->SetTextFont(43);
  tex3->SetTextSize(22);
  tex3->SetTextColor(kRed);
  tex3->Draw();




  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  ////////////////////////END OF FORWARD ANALYSIS SECTION///////////////////////
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  
  std::cout<<"The reduced chi2 for Positive two sigma is:\t"<<Chi2P2S/(hfa->GetNbinsX()-ParametersInTheModel)<<std::endl;
  std::cout<<"The reduced chi2 for Positive one sigma is:\t"<<Chi2P1S/(hfa->GetNbinsX()-ParametersInTheModel)<<std::endl;
  std::cout<<"The reduced chi2 for Negative two sigma is:\t"<<Chi2N2S/(hfa->GetNbinsX()-ParametersInTheModel)<<std::endl;
  std::cout<<"The reduced chi2 for Negative one sigma is:\t"<<Chi2N1S/(hfa->GetNbinsX()-ParametersInTheModel)<<std::endl;
  
  double HowdWeDoP2s=0.;
  HowdWeDoP2s = TMath::Prob(Chi2P2S,hfa->GetNbinsX()-ParametersInTheModel);

   double HowdWeDoP1s=0.;
   HowdWeDoP1s = TMath::Prob(Chi2P1S,hfa->GetNbinsX()-ParametersInTheModel);
  
  double HowdWeDoN2s=0.;
  HowdWeDoN2s = TMath::Prob(Chi2N2S,hfa->GetNbinsX()-ParametersInTheModel);

  double HowdWeDoN1s=0.;
  HowdWeDoN1s = TMath::Prob(Chi2N1S,hfa->GetNbinsX()-ParametersInTheModel);

  //std::cout<<"This is how we did\t"<<HowdWeDoP2s<<std::endl;
  

  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  ////////////////////////MAKING A PFNS/////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  if (!MakeAPFNS) return;
    
  //Read in the ENDF 7 Standard PFNS
  pfns = new TGraphErrors("PFNS_ENDFVIIpt1B_1MeV.txt","%lg %lg");
  TSpline3 *spfns = new TSpline3("s",pfns);//Fit it using a poly(3)
  //Make a histogram that the fit function will populate
  TH1D *hpfns = new TH1D("hpfns","hpfns",nBins,x);
  hpfns->GetYaxis()->SetTitle("Counts");
  hpfns->GetXaxis()->SetTitle("Outgoing Neutron Energy (MeV)");
  hpfns->SetLineColor(kRed+2);
  hpfns->SetLineWidth(1.4);
    
  //Get w2 and bin content arrays for pfns histo
  Double_t *pfnsValues = hpfns->GetArray();
  
  for (int biniter=1;biniter<=hpfns->GetNbinsX();biniter++)
    {
      pfnsValues[biniter]=spfns->Eval(hpfns->GetBinCenter(biniter));
    }


  TH1 *data = (TH1*)hfa->Clone();//Clone the data histogram
  TArrayD *Dataw2 = data->GetSumw2();
  
  //Make maxwellian curve to give PFNS the appropriate shape                                                                  
  TF1 *f1 = new TF1("f1","[0]*TMath::Sqrt(x)*(1/([1]^(3/2)))*TMath::Exp(-x/[1])"
		    ,MinEout,MaxEout+MaxEout/100);
  f1->SetParameter(0,1);
  f1->SetParameter(1,1.424);//Corresponds to T=1.424
  

  TH1 *hpfns2 = (TH1*)hpfns->Clone();
  hpfns2->SetLineColor(kRed);
  hpfns2->SetLineWidth(2);
  hpfns2->Multiply(f1,1);
  hpfns2->Scale(1./hpfns2->Integral());
  //hpfns2->Scale(1./5);

  new TCanvas;//Now setting up the ratio of ratios method
  if (WhichMCNP==1)data->Divide(hp2mcnp);
  //else if (WhichMCNP==2)data->Divide(hp1mcnp);
  else if (WhichMCNP==3)data->Divide(hn2mcnp);
  else if (WhichMCNP==4)data->Divide(hn1mcnp);
  data->GetYaxis()->SetTitleOffset(1.7);
  data->Multiply(hpfns);
  data->Multiply(f1,1);

  double I=0.0;
  double ess=0.0;
  
      for (int been=1;been<data->GetNbinsX();been++)
	{
	  //	  double exx=data->GetBinContent(been)/data->GetBinWidth(been);
	  //I+=(exx*data->GetBinCenter(been));
	  //ess+=exx;
	  double exx = ((data->GetBinContent(been)+data->GetBinContent(been+1))/(2.0))*
	    (data->GetBinLowEdge(been+1)-data->GetBinLowEdge(been));
	  I +=(exx*(data->GetBinLowEdge(been)+data->GetBinLowEdge(been+1))/2.0);
	  ess+=exx;
	}
      std::cout<<I/ess<<std::endl;
      
      
      data->Scale(1./data->Integral());


  //Now propagating errors correctly
  for (int bin=1;bin<data->GetNbinsX();bin++)
    {
      double R = data->GetBinContent(bin);
      double kl = hfa->GetBinContent(bin);
      double xsig = hfa->GetBinError(bin);
      if (WhichMCNP==1)
	{
	  double z = hp2mcnp->GetBinContent(bin);
	  double zsig = hp2mcnp->GetBinError(bin);
	}
      else if (WhichMCNP==2)
 	{
 	  double z = hp1mcnp->GetBinContent(bin);
 	  double zsig = hp1mcnp->GetBinError(bin);
 	}
      else if (WhichMCNP==3)
	{
	  double z = hn2mcnp->GetBinContent(bin);
	  double zsig = hn2mcnp->GetBinError(bin);
	}
      else if (WhichMCNP==4)
	{
	  double z = hn1mcnp->GetBinContent(bin);
	  double zsig = hn1mcnp->GetBinError(bin);
	}
      
      double xratio = (xsig/kl)*(xsig/kl);
      double zratio = (zsig/z)*(zsig/z);
      double added = TMath::Sqrt(xratio+zratio);
      double unc = (R*added)*(R*added);
      //   std::cout<<unc<<std::endl;
      Dataw2->SetAt(unc,bin);
    }//end of loop over bins

  data->Draw();
  hpfns2->Draw("lsame");

  //TSpline3 *sdata = new TSpline3("s",data);



  char mytex8[128];
  sprintf(mytex8,"E_{n}^{in} = %0.1f - %0.1f MeV",MinEinc,MaxEinc);
  tex8=new TLatex(0.6,0.45,mytex2);
  tex8->SetNDC();
  tex8->SetTextFont(43);
  tex8->SetTextSize(22);
  tex8->SetTextColor(kRed);
  tex8->Draw();

  char mytex9[128];
  sprintf(mytex9,"<E> = %2.3f MeV",I/ess);
  tex9=new TLatex(0.6,0.35,mytex9);
  tex9->SetNDC();
  tex9->SetTextFont(43);
  tex9->SetTextSize(22);
  tex9->SetTextColor(kRed);
  tex9->Draw();

  TLegend *leg10 = new TLegend(0.25,0.65,0.40,0.85,"","brNDC");
  leg10->AddEntry(data,"Chi-Nu Data","lp");
  leg10->AddEntry(hpfns2,"ENDF/B-VII.1","lp");
  leg10->SetFillColor(kWhite);
  leg10->SetTextFont(43);
  leg10->SetTextSize(18);
  leg10->SetBorderSize(0);
  leg10->Draw();
  
  gPad->SetLogx(kTRUE);



  if (MakeAPFNS==false && PrintDataPoints==true)
    {
      std::cout<<"You cant print data points without a histogram you goose!"<<std::endl;
      return;
    }
  
  if (MakeAPFNS==true && PrintDataPoints==true)
    {
      ofstream myout;
      char textname[128];
      
      if (WhichMCNP==1)
	{
	  if (MCNP_RENORMRANGE==1)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_below100keVRenorm_pos2sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==2)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_100to800keVRenorm_pos2sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==3)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_800to1pt2MeVRenorm_pos2sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==4)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_1pt2to4MeVRenorm_pos2sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==5)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_above4MeVRenorm_pos2sigma.txt",MinEinc,MaxEinc);
	    }
	}
      else if (WhichMCNP==2)
	{
	  if (MCNP_RENORMRANGE==1)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_below100keVRenorm_pos1sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==2)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_100to800keVRenorm_pos1sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==3)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_800to1pt2MeVRenorm_pos1sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==4)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_1pt2to4MeVRenorm_pos1sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==5)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_above4MeVRenorm_pos1sigma.txt",MinEinc,MaxEinc);
	    }
	}
      else if (WhichMCNP==3)
	{
	  if (MCNP_RENORMRANGE==1)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_below100keVRenorm_neg2sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==2)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_100to800keVRenorm_neg2sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==3)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_800to1pt2MeVRenorm_neg2sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==4)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_1pt2to4MeVRenorm_neg2sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==5)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_above4MeVRenorm_neg2sigma.txt",MinEinc,MaxEinc);
	    }
	}
      else if (WhichMCNP==4)
	{
	  if (MCNP_RENORMRANGE==1)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_below100keVRenorm_neg1sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==2)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_100to800keVRenorm_neg1sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==3)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_800to1pt2MeVRenorm_neg1sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==4)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_1pt2to4MeVRenorm_neg1sigma.txt",MinEinc,MaxEinc);
	    }
	  else if (MCNP_RENORMRANGE==5)
	    {
	      sprintf(textname,"DataPointsForPFNS_%2.1f_%2.1f_above4MeVRenorm_neg1sigma.txt",MinEinc,MaxEinc);
	    }
	}
      myout.open(textname);
      //myout.open("DataPointsForPFNS.txt");
      myout<<"Bin Lower Edge"<<"\t"<<"Bin Upper Edge"<<"\t"<<"Bin Value"<<"\t"
	   <<"BinStatisticalError"<<"\t"<<"Percentage"<<endl;
      
      for (i=1;i<=data->GetXaxis()->FindBin(MaxEout);i++)
	{
	  myout<<data->GetBinLowEdge(i)<<"\t"<<
	    (data->GetBinLowEdge(i)+data->GetBinWidth(i))<<"\t"<<
	    data->GetBinContent(i)<<"\t"<<data->GetBinError(i)<<"\t"<<
	    data->GetBinError(i)/data->GetBinContent(i)<<endl;
	}



      myout<<"\n"<<endl;
      myout<<"The reduced Chi2 for Pos2 Sigma was:\t"<<Chi2P2S/(hfa->GetNbinsX()-ParametersInTheModel)<<"  Meaning we did this well\t"<<HowdWeDoP2s<<endl;
      myout<<"The reduced Chi2 for Pos1 Sigma was:\t"<<Chi2P1S/(hfa->GetNbinsX()-ParametersInTheModel)<<"  Meaning we did this well\t"<<HowdWeDoP1s<<endl;
      myout<<"The reduced Chi2 for Neg2 Sigma was:\t"<<Chi2N2S/(hfa->GetNbinsX()-ParametersInTheModel)<<"  Meaning we did this well\t"<<HowdWeDoN2s<<endl;
      myout<<"The reduced Chi2 for Neg1 Sigma was:\t"<<Chi2N1S/(hfa->GetNbinsX()-ParametersInTheModel)<<"  Meaning we did this well\t"<<HowdWeDoN1s<<endl;
      myout<<"\n"<<endl;
      myout<<"\n"<<endl;
      myout<<"<E> = "<<I/ess<<"    #pm"<<TMath::Sqrt(data->GetRMS())<<std::endl;
      myout.close();
      return;
    }
}

