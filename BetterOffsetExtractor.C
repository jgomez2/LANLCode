
Int_t FirstRun;
Int_t LastRun;
char FileName[128];
FILE *ptr_file;
Float_t range_low[3];
Float_t range_hi[3];
range_low[0]=-13; range_hi[0]=-3;
range_low[1]=-5;  range_hi[1]=5;
range_low[2]=5;   range_hi[2]=11;

//Declare Vectors To Store Run Numbers
std::vector<int> condition_000;
std::vector<int> condition_008;
std::vector<int> condition_088;
std::vector<int> condition_080;
std::vector<int> condition_880;
std::vector<int> condition_808;
std::vector<int> condition_800;
std::vector<int> condition_error;

std::vector<float> firstboard;
std::vector<float> secondboard;
std::vector<float> thirdboard;

bool firstisfit;
bool secondisfit;
bool thirdisfit;

condition_000.clear();condition_008.clear();condition_088.clear();
condition_080.clear();condition_880.clear();condition_808.clear();condition_800.clear();condition_error.clear();

firstboard.clear();
secondboard.clear();
thirdboard.clear();


void AnalyzeRun(int);
void Fit(TH1*,int);
void Sort(int);
void Print();

Int_t BetterOffsetExtractor(){
  std::cout<<"What is the first run in the range?"<<std::endl;
  std::cin>>FirstRun;
  std::cout<<"What is the last run in the range?"<<std::endl;
  std::cin>>LastRun;

  for (int i=FirstRun;i<=LastRun;i++)
    {
      AnalyzeRun(i);
    }//End Of Loop OverRuns
  Print();
  return 0;
}




void AnalyzeRun(int ThisRun){


  sprintf(FileName,"jgomez2-dflt-tag-%i.root",ThisRun);
  ptr_file=fopen(FileName,"r");
  if(ptr_file==NULL) return;

  TFile *f = new TFile(FileName);
  f->cd("histos/TwoDetectorCoinc");
  
  ///////////////////////////////////////
  //For the Time between T0 and Ligl17//
  ///////////////////////////////////////


  ////Grab the histograms
  TH1 *h1 =(TH1*)gDirectory->FindObjectAny("td1_05_time_ppac05_ligl03");
  TH1 *h2 =(TH1*)gDirectory->FindObjectAny("td1_05_time_ppac05_ligl10");
  TH1 *h3 =(TH1*)gDirectory->FindObjectAny("td1_05_time_ppac05_ligl17");
 
  firstisfit=false;
  secondisfit=false;
  thirdisfit=false;
  
  if (h1->GetEntries()) Fit(h1,1);
  if (h2->GetEntries()) Fit(h2,2);
  if (h3->GetEntries()) Fit(h3,3);
  Sort(ThisRun);
  

}//End of AnalyzeRun function


void Fit(TH1* MyHist, int BoardNumber){
  double current_amplitude=0.;
  double current_mean=0.;
  int current_range=0.;

  for (int i=0;i<3;i++)
    {
      MyHist->GetXaxis()->SetRangeUser(range_low[i],range_hi[i]);
      TFitResultPtr res = MyHist->Fit("gaus","S");
      TF1 *myfit=(TF1*)MyHist->GetFunction("gaus");
      if (myfit)
	{
	  Float_t mean = myfit->GetParameter(1);
	  Float_t stdeviation = myfit->GetParameter(2);
	  if (stdeviation>5) continue;
	  if(myfit->GetParameter(0)<current_amplitude)continue;
	  if(myfit->GetParameter(0)>current_amplitude) 
	    {
	      current_amplitude=myfit->GetParameter(0);
	      current_mean=mean;
	      current_range=i;
	    }
	}//end of if fit exists
    }//end of loop over ranges
  
  std::cout<<"A\t"<<current_amplitude<<"    mu\t"<<current_mean<<"     range\t"<<current_range<<std::endl;
  
  if ( (current_mean>range_low[current_range]) && (current_mean<range_hi[current_range]) )
    {
      if (BoardNumber==1)
	{
	  firstboard.push_back(current_mean);
	  firstisfit=true;
	}
      else if (BoardNumber==2)
	{
	  secondboard.push_back(current_mean);
	  secondisfit=true;
	}
      else if (BoardNumber==3)
	{
	  thirdboard.push_back(current_mean);
	  thirdisfit=true;
	}
    }//End of "in the range" check
}//End of fit function


void Sort(int RunNumber){

  
  if (firstisfit==false || secondisfit==false || thirdisfit==false) 
    {
      condition_error.push_back(RunNumber);
      return;
    }

  // for (int ii=0; ii<firstboard.size();ii++)
  // {
      Double_t Board1Result=0;
      Double_t Board2Result=0;
      Double_t Board3Result=0;
      
      //First Board Checks
      if ( (firstboard[firstboard.size()-1] > -2) && (firstboard[firstboard.size()-1] < 2) ) Board1Result=0;
      if ( (firstboard[firstboard.size()-1] > -11) && (firstboard[firstboard.size()-1] < -5) ) Board1Result=-8;
      if ( (firstboard[firstboard.size()-1] > 5) && (firstboard[firstboard.size()-1] < 11) ) Board1Result=8;
     

      //Second Board Checks
      if ( (secondboard[secondboard.size()-1] > -2) && (secondboard[secondboard.size()-1] < 1) ) Board2Result=0;
      if ( (secondboard[secondboard.size()-1] > -9) && (secondboard[secondboard.size()-1] < -6.8) ) 
	{
	  Board2Result=-8;
	}
      if ( (secondboard[secondboard.size()-1] > 7) && (secondboard[secondboard.size()-1] < 10) ) Board2Result=8;


      //ThirdBoard Checks
      if ( (thirdboard[thirdboard.size()-1] > -1) && (thirdboard[thirdboard.size()-1] < 0) ) Board3Result=0;
      if ( (thirdboard[thirdboard.size()-1] > -9) && (thirdboard[thirdboard.size()-1] < -6) ) Board3Result=-8;
      if ( (thirdboard[thirdboard.size()-1] > 7) && (thirdboard[thirdboard.size()-1] < 10) ) 
	{
	  Board3Result=8;
	}



      if ( (Board1Result==-8) || (Board2Result==-8) || (Board3Result==-8) )
	{
	  Board1Result+=8;
	  Board2Result+=8;
	  Board3Result+=8;
	}
      
      
      if      ((Board1Result==0) && (Board2Result==0) && (Board3Result==0)) condition_000.push_back(RunNumber);
      else if ((Board1Result==0) && (Board2Result==0) && (Board3Result==8)) condition_008.push_back(RunNumber);
      else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==0)) condition_080.push_back(RunNumber);
      else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==8)) condition_088.push_back(RunNumber);
      else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==0)) condition_800.push_back(RunNumber);
      else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==8)) condition_808.push_back(RunNumber);
      else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==0)) condition_880.push_back(RunNumber);
      else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==8)) condition_000.push_back(RunNumber); // not _888
    

      // }//end of loop over board results
}//end of sort function


void Print(){
  /////////////////////////////////////////////////////
  /////NOW PRINT THE RESULTS IN THE DESIGNATED FILES///
  /////////////////////////////////////////////////////

  ofstream myout;
  myout.open("CombinedResults.txt");
  myout<<"First Board"<<"    "<<"Second Board"<<"    "<<"Third Board"<<endl;
  for (int ii=0; ii<firstboard.size();ii++)
    {
      myout<<firstboard[ii]<<"    "<<secondboard[ii]<<"    "<<thirdboard[ii]<<endl;
    }
  myout.close();
  // if(firstboard.size()!=0)

//Now make the text files that will hold the run numbers
  ofstream out1;
  out1.open("ClockOffset_000.iac");
  for (int j=0;j<condition_000.size();j++) out1<<condition_000[j]<<",";
  out1.close();

  ofstream out2;
  out2.open("ClockOffset_008.iac");
  for (int j=0;j<condition_008.size();j++) out2<<condition_008[j]<<",";
  out2.close();

  ofstream out3;
  out3.open("ClockOffset_088.iac");
  for (int j=0;j<condition_088.size();j++) out3<<condition_088[j]<<",";
  out3.close();

  ofstream out4;
  out4.open("ClockOffset_080.iac");
  for (int j=0;j<condition_080.size();j++) out4<<condition_080[j]<<",";
  out4.close();

  ofstream out5;
  out5.open("ClockOffset_880.iac");
  for (int j=0;j<condition_880.size();j++) out5<<condition_880[j]<<",";
  out5.close();

  ofstream out6;
  out6.open("ClockOffset_808.iac");
  for (int j=0;j<condition_808.size();j++) out6<<condition_808[j]<<",";
  out6.close();

  ofstream out7;
  out7.open("ClockOffset_800.iac");
  for (int j=0;j<condition_800.size();j++) out7<<condition_800[j]<<",";
  out7.close();

  ofstream out8;
  out8.open("RunsWithErrors.text");
  for (int j=0;j<condition_error.size();j++) out8<<condition_error[j]<<",";
  out8.close();

}//End of Print Function
