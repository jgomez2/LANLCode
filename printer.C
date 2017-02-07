{
  //READ IN AMBE Files
  //TFile *fambentofs = TFile::Open("withntofs.root","READ");
  //  TFile *fambeRA = TFile::Open("jgomez2-correctRA-ambe.root","READ");
  
  //READ IN Cf files
  //TFile *cfntofs= TFile::Open("usingntofs_cf.root","READ");
  TFile *cfRA=TFile::Open("jgomez2-correctRA-cf.root","READ");
  
  // fambentofs->cd();
  // ofstream myout;
  // myout.open("AMBE_gamma_coinc.txt");
  // myout<<"Bin Center \t Bin Content"<<endl;
  // for (int i=1;i<=tof_gf->GetNbinsX();i++)
  //   {
  //     char bincenter[128];				       
  //     sprintf(bincenter,"%08.2f",tof_gf->GetBinCenter(i));  
  //     char bincontent[128];				       
  //     sprintf(bincontent,"%08.2f",tof_gf->GetBinContent(i));
  //     myout<<bincenter<<" "<<bincontent<<endl;
  //   }

  //  myout.close();
  //return;
  
  // cfntofs->cd();
  // ofstream myout1;
  // myout1.open("Cf_gamma_coinc.txt");
  // myout1<<"Bin Center \t Bin Content"<<endl;
  // for (int i=1;i<=tof_gf->GetNbinsX();i++)
  //   {
  //     char bincenter[128];				             
  //     sprintf(bincenter,"%08.2f",tof_gf->GetBinCenter(i));  
  //     char bincontent[128];				       
  //     sprintf(bincontent,"%08.2f",tof_gf->GetBinContent(i));
  //     myout1<<bincenter<<" "<<bincontent<<endl;
  //   }

  // myout1.close();

  // fambeRA->cd();
  // ofstream myout2;
  // myout2.open("AMBE_RossiAlpha.txt");
  // myout2<<"Bin Center \t Bin Content"<<endl;
  // for (int i=1;i<=ShortRossiAlpha_AllLiquids->GetNbinsX();i++)
  //   {
  //     char bincenter[128];
  //     sprintf(bincenter,"%08.2f",ShortRossiAlpha_AllLiquids->GetBinCenter(i));
  //     char bincontent[128];
  //     sprintf(bincontent,"%08.2f",ShortRossiAlpha_AllLiquids->GetBinContent(i));
  //     myout2<<bincenter<<" "<<bincontent<<endl;
  //   }
  
  // myout2.close();
  
  cfRA->cd();
  ofstream myout3;
  myout3.open("Cf_RossiAlpha.txt");
  myout3<<"Bin Center \t Bin Content"<<endl;
  for (int i=1;i<=ShortTimeRossiAlpha_AllLiquids->GetNbinsX();i++)
    {
      char bincenter[128];
      sprintf(bincenter,"%08.2f",ShortTimeRossiAlpha_AllLiquids->GetBinCenter(i));
      char bincontent[128];
      sprintf(bincontent,"%08.2f",ShortTimeRossiAlpha_AllLiquids->GetBinContent(i));
      myout3<<bincenter<<" "<<bincontent<<endl;
    }  
  
  
  myout3.close();
  
  
}
