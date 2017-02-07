#include<vector>
#include<cstring>
//Int_t FirstRun;
//Int_t LastRun;

char FileName[128];
FILE *ptr_file;
Double_t range_low_lower=33950.0;
Double_t range_high_lower=34469.0;

Double_t range_low_higher=34515.0;
Double_t range_high_higher=35107.0;

//Declare Vector to store run numbers
vector<string> v1;
vector<string> v2;

//Clear the vectors out
//v1.clear();
//v2.clear();

void AnalyzeRun(string);
void Print();

Int_t BeamRateChecker(){

  ifstream textfile;
  textfile.open("mylistofruns.txt");
  //while (! textfile.eof());{
  string str;
  while(std::getline(textfile,str))
    {
      AnalyzeRun(str);
    }//End of loop over runs
  Print();
  return 0;
}


void AnalyzeRun(string runstr){
  
  TFile *f = TFile::Open(runstr.c_str(),"READ");
  
  f->cd("histos/Scaler");
  //new TCanvas;
  
  TH1F *t0 = (TH1F*)gDirectory->FindObjectAny("rate_s027_t00_hits");
  
  //new TCanvas;
  //t0->Draw();
  if (t0)
    {  
      TH1D *comparehist = new TH1D("compare","compare",1300,33900,35200);
      
      for (int i=1;i<=t0->GetNbinsX();i++)
	{
	  comparehist->Fill(t0->GetBinContent(i));
	}
      
      //new TCanvas;
      //comparehist->Draw();
      
      Double_t averagecounts = comparehist->GetMean(1);
      
      if ( (averagecounts>range_low_lower) && (averagecounts<range_high_lower) ) v1.push_back(runstr);
      if ( (averagecounts>range_low_higher) && (averagecounts<range_high_higher) ) v2.push_back(runstr);
    }
  f->Close();

}//End of Analyze Run function

void Print(){

  ofstream myout;
  myout.open("BeamCountResults.txt");
  
  myout<<"Runs with counts between 33950-34469"<<endl;
  for (int i=0;i<v1.size();i++)
    {
      myout<<v1[i].c_str()<<endl; 
    }

  myout<<" "<<endl;
  myout<<" "<<endl;


  myout<<"Runs with counts between 34515-35107"<<endl;
  for (int i=0;i<v2.size();i++)
    {
      myout<<v2[i].c_str()<<endl; 
    }

  myout.close();

}//End of print function
