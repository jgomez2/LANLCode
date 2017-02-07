//Int_t FirstRun;
//Int_t LastRun;

char FileName[128];
FILE *ptr_file;
Double_t range_low_lower=33950.0;
Double_t range_high_lower=34469.0;
Double_t range_low_higher=34515.0;
Double_t range_high_higher=35107.0;

//Declare Vector to store run numbers
std::vector<int> condition_low;
std::vector<int> condition_high;

//Clear the vectors out
condition_low.clear();condition_high.clear();

void AnalyzeRun(int);

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

TH1D *t0 = (TH1*) rate_s027_t00_hits->Clone();

new TCanvas;
t0->Draw();

TH1D *comparehist = new TH1D("compare","compare",20000,0,60000);

for (int i=1;i<=t0->GetNbinsX();i++)
{
   comparehist->Fill(t0->GetBinContent(i));
}

new TCanvas;
comparehist->Draw();
}//End of Analyze Run function
