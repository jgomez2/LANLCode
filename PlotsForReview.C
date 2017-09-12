{
  TFile *f = TFile::Open("liquidanalysis_july2017.root","READ");
  TFile *f1 = TFile::Open("jgomez2-dflt-tag-supertight.root","READ");

  f->cd("histos/DoubleCoinc");
  TH2* hf;
  TH2* hb;
  for (int p=1;p<=10;p++)
    {
      for(int l=1;l<=54;l++)
        {
          if(l==8 || l==16 || l==24) continue;
          char name[128];
	  char bname[128];
          sprintf(name,"dc1_4_poly_2eth_t00_ppac%02i_liquid%02i",p,l-1);
	  sprintf(bname,"dc1_4_back_poly_2eth_t00_ppac%02i_liquid%02i",p,l-1);
          TH2 *temp = (TH2*)gDirectory->FindObjectAny(name);
          TH2 *btemp = (TH2*)gDirectory->FindObjectAny(bname);
	  if(p==1 &&l==1)
            {
              hf=(TH2*)temp->Clone();
	      hb=(TH2*)btemp->Clone();
            }else
            {
              hf->Add(temp);
	      hb->Add(btemp);
            }
        }
    }

  new TCanvas;
  hf->Draw("colz");
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->SetLogz();
  hf->SetTitle("");
  gPad->SetTickx();
  gPad->SetTicky();
  gStyle->SetOptStat(0);
  gStyle->SetLineWidth(2);
  hf->GetXaxis()->SetRangeUser(.8,100);
  hf->GetYaxis()->SetRangeUser(0.08,100);
  hf->GetXaxis()->SetTitle("Incident Neutron Energy from T.O.F. (MeV)");
  hf->GetXaxis()->CenterTitle(1);
  hf->GetXaxis()->SetTitleFont(42);
  hf->GetXaxis()->SetTitleSize(0.05);
  hf->GetXaxis()->SetLabelSize(0.045);
  hf->GetZaxis()->SetLabelSize(0.045);
  hf->GetYaxis()->SetTitle("Outgoing Neutron Energy from T.O.F. (MeV)");
  hf->GetYaxis()->CenterTitle(1);
  hf->GetYaxis()->SetTitleFont(42);
  hf->GetYaxis()->SetTitleSize(0.05);
  hf->GetYaxis()->SetLabelSize(0.045);

  new TCanvas;
  hb->Draw("colz");
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->SetLogz();
  hb->SetTitle("");
  gPad->SetTickx();
  gPad->SetTicky();
  gStyle->SetOptStat(0);
  gStyle->SetLineWidth(2);
  hb->GetXaxis()->SetRangeUser(0.8,100);
  hb->GetYaxis()->SetRangeUser(0.08,100);
  hb->GetXaxis()->SetTitle("Incident Neutron Energy from T.O.F. (MeV)");
  hb->GetXaxis()->CenterTitle(1);
  hb->GetXaxis()->SetTitleFont(42);
  hb->GetXaxis()->SetTitleSize(0.05);
  hb->GetXaxis()->SetLabelSize(0.045);
  hb->GetZaxis()->SetLabelSize(0.045);
  hb->GetYaxis()->SetTitle("Outgoing Neutron Energy from T.O.F. (MeV)");
  hb->GetYaxis()->CenterTitle(1);
  hb->GetYaxis()->SetTitleFont(42);
  hb->GetYaxis()->SetTitleSize(0.05);
  hb->GetYaxis()->SetLabelSize(0.045);

  TH2 *hfb=(TH2*)hf->Clone();
  hfb->Add(hb,-1);

  new TCanvas;
  hfb->Draw("colz");
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->SetLogz();
  hfb->SetTitle("");
  gPad->SetTickx();
  gPad->SetTicky();
  gStyle->SetOptStat(0);
  gStyle->SetLineWidth(2);
  hfb->GetXaxis()->SetRangeUser(0.8,100);
  hfb->GetYaxis()->SetRangeUser(0.08,100);
  hfb->GetXaxis()->SetTitle("Incident Neutron Energy from T.O.F. (MeV)");
  hfb->GetXaxis()->CenterTitle(1);
  hfb->GetXaxis()->SetTitleFont(42);
  hfb->GetXaxis()->SetTitleSize(0.05);
  hfb->GetXaxis()->SetLabelSize(0.045);
  hfb->GetZaxis()->SetLabelSize(0.045);
  hfb->GetYaxis()->SetTitle("Outgoing Neutron Energy from T.O.F. (MeV)");
  hfb->GetYaxis()->CenterTitle(1);
  hfb->GetYaxis()->SetTitleFont(42);
  hfb->GetYaxis()->SetTitleSize(0.05);
  hfb->GetYaxis()->SetLabelSize(0.045);

  f1->cd("histos/DoubleCoinc");
  TH2* hlf;
  TH2* hlb;
  for (int p=1;p<=10;p++)
    {
      for(int l=1;l<=22;l++)
        {
          if(l==3) continue;
          char name[128];
	  char bname[128];
          sprintf(name,"dc1_3_poly_2eth_t00_ppac%02i_ligl%02i",p,l);
	  sprintf(bname,"dc1_3_back_poly_2eth_t00_ppac%02i_ligl%02i",p,l);
          TH2 *temp = (TH2*)gDirectory->FindObjectAny(name);
          TH2 *btemp = (TH2*)gDirectory->FindObjectAny(bname);
	  if(p==1 &&l==1)
            {
              hlf=(TH2*)temp->Clone();
	      hlb=(TH2*)btemp->Clone();
            }else
            {
              hlf->Add(temp);
	      hlb->Add(btemp);
            }
        }
    }

  new TCanvas;
  hlf->Draw("colz");
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->SetLogz();
  hlf->SetTitle("");
  gPad->SetTickx();
  gPad->SetTicky();
  gStyle->SetOptStat(0);
  gStyle->SetLineWidth(2);
  hlf->GetXaxis()->SetRangeUser(0.8,100);
  hlf->GetYaxis()->SetRangeUser(0.08,100);
  hlf->GetXaxis()->SetTitle("Incident Neutron Energy from T.O.F. (MeV)");
  hlf->GetXaxis()->CenterTitle(1);
  hlf->GetXaxis()->SetTitleFont(42);
  hlf->GetXaxis()->SetTitleSize(0.05);
  hlf->GetXaxis()->SetLabelSize(0.045);
  hlf->GetZaxis()->SetLabelSize(0.045);
  hlf->GetYaxis()->SetTitle("Outgoing Neutron Energy from T.O.F. (MeV)");
  hlf->GetYaxis()->CenterTitle(1);
  hlf->GetYaxis()->SetTitleFont(42);
  hlf->GetYaxis()->SetTitleSize(0.05);
  hlf->GetYaxis()->SetLabelSize(0.045);

  new TCanvas;
  hlb->Draw("colz");
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->SetLogz();
  hlb->SetTitle("");
  gPad->SetTickx();
  gPad->SetTicky();
  gStyle->SetOptStat(0);
  gStyle->SetLineWidth(2);
  hlb->GetXaxis()->SetRangeUser(0.8,100);
  hlb->GetYaxis()->SetRangeUser(0.08,100);
  hlb->GetXaxis()->SetTitle("Incident Neutron Energy from T.O.F. (MeV)");
  hlb->GetXaxis()->CenterTitle(1);
  hlb->GetXaxis()->SetTitleFont(42);
  hlb->GetXaxis()->SetTitleSize(0.05);
  hlb->GetXaxis()->SetLabelSize(0.045);
  hlb->GetZaxis()->SetLabelSize(0.045);
  hlb->GetYaxis()->SetTitle("Outgoing Neutron Energy from T.O.F. (MeV)");
  hlb->GetYaxis()->CenterTitle(1);
  hlb->GetYaxis()->SetTitleFont(42);
  hlb->GetYaxis()->SetTitleSize(0.05);
  hlb->GetYaxis()->SetLabelSize(0.045);

  TH2 *hlfb=(TH2*)hlf->Clone();
  hlfb->Add(hlb,-1);

  new TCanvas;
  hlfb->Draw("colz");
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->SetLogz();
  hlfb->SetTitle("");
  gPad->SetTickx();
  gPad->SetTicky();
  gStyle->SetOptStat(0);
  gStyle->SetLineWidth(2);
  hlfb->GetXaxis()->SetRangeUser(0.8,100);
  hlfb->GetYaxis()->SetRangeUser(0.08,100);
  hlfb->GetXaxis()->SetTitle("Incident Neutron Energy from T.O.F. (MeV)");
  hlfb->GetXaxis()->CenterTitle(1);
  hlfb->GetXaxis()->SetTitleFont(42);
  hlfb->GetXaxis()->SetTitleSize(0.05);
  hlfb->GetXaxis()->SetLabelSize(0.045);
  hlfb->GetZaxis()->SetLabelSize(0.045);
  hlfb->GetYaxis()->SetTitle("Outgoing Neutron Energy from T.O.F. (MeV)");
  hlfb->GetYaxis()->CenterTitle(1);
  hlfb->GetYaxis()->SetTitleFont(42);
  hlfb->GetYaxis()->SetTitleSize(0.05);
  hlfb->GetYaxis()->SetLabelSize(0.045);
  
}
