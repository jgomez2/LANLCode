
#include<vector>
#include<cstring>
   
char FileName[128];
FILE *ptr_file;

bool removezeroes=true;

//TFile *newef = TFile::Open("varhistos.root","RECREATE");
//newef.Close();

TH1D *var = new TH1D("LiGlRateVar_AllRuns","LiGlRateVar_AllRuns",10000000,0,100000);
TProfile *avvar = new TProfile("Liglavvar","Liglavvar",1,0,1);


void AnalyzeRun(string);

Int_t VarRate(){
  
  ifstream textfile;
  textfile.open("mylistofruns.txt");
  string str;
  while(std::getline(textfile,str))
    {
      AnalyzeRun(str);
    }//End of loop over runs
  
  var->GetXaxis()->SetTitle("( #Gamma_{i} - #bar{#Gamma_{run}} )^{2}");
  var->GetXaxis()->CenterTitle(1);
  var->GetXaxis()->SetTitleOffset(1.2);
  var->GetYaxis()->SetTitle("counts");
  var->GetYaxis()->SetTitleOffset(1.3);
  var->SetTitle("Kinda Variance in LiGl-7 Counting Rate");
  TLatex *tex = new TLatex(0.65,0.65,"{}^{235}U Runs, 2015");
  tex->SetNDC();
  tex->SetTextColor(kRed);
  tex->SetTextFont(43);
  tex->SetTextSize(24);
  new TCanvas;
  var->Draw();
  tex->Draw();
  return 0;
  
  TFile *newef=TFile::Open("varhistos.root","UPDATE");
  newef->cd();
  var->Write();
  avvar->Write();
  newef->Close();
}


void AnalyzeRun(string runstr){
  
  string fragment = runstr.substr (41,5);
  char tempname[128];
  sprintf(tempname,"varhisto_%s",fragment.c_str());
  TH1D *tempvar = new TH1D(tempname,tempname,10000000,0,100000);
  
  TFile *f = TFile::Open(runstr.c_str(),"READ");
  f->cd("histos/Scaler");
  
  TProfile *temppro = new TProfile("temp","temp",1,0,1);
  TH1F *ligl7 = (TH1F*)gDirectory->FindObjectAny("rate_s041_ligl07_hits");
  
  if (ligl7)
    {  
      for (int i=1;i<=ligl7->GetNbinsX();i++)
	{
	  if (removezeroes && ligl7->GetBinContent(i)>5.)
	    {
	      temppro->Fill(0.5,ligl7->GetBinContent(i));
	    }
	  if (!removezeroes) temppro->Fill(0.5,ligl7->GetBinContent(i));
	}

      Double_t averagecounts = temppro->GetBinContent(1);
      Double_t countsthisrun = temppro->GetEntries();

      for (int j=1;j<=ligl7->GetNbinsX();j++)
	{
	  if (removezeroes && ligl7->GetBinContent(j)>5.)
	    {
	      var->Fill( (ligl7->GetBinContent(j)-averagecounts)*(ligl7->GetBinContent(j)-averagecounts) );
	      tempvar->Fill( (ligl7->GetBinContent(j)-averagecounts)*(ligl7->GetBinContent(j)-averagecounts)/countsthisrun );
	    }
	  if (!removezeroes) 
	    {
	      var->Fill( (ligl7->GetBinContent(j)-averagecounts)*(ligl7->GetBinContent(j)-averagecounts) );
	      tempvar->Fill( (ligl7->GetBinContent(j)-averagecounts)*(ligl7->GetBinContent(j)-averagecounts)/countsthisrun );
	    }
	}
      
      double tempcalc=0.0;
      double tempent=tempvar->GetEntries();

      //std::cout<<tempent<<countsthisrun<<std::endl;
      for (int k=1;k<=tempvar->GetNbinsX();k++) 
	{
	  tempcalc+=tempvar->GetBinContent(k)
	    *tempvar->GetBinCenter(k)
	    *tempent;
	}
      avvar->Fill(0.5,tempcalc/tempent);
    }
  f->Close();
  
  TFile *newef =TFile::Open("varhistos.root","UPDATE");
  newef->cd();
  
  if (tempvar) tempvar->Write();
  newef->Close();
  
}//End of Analyze Run function



