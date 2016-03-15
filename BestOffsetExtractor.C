
Int_t FirstRun;
Int_t LastRun;
bool IsFiveBoards;
char FileName[128];
FILE *ptr_file;
Float_t range_low[3];
Float_t range_hi[3];
range_low[0]=-13; range_hi[0]=-3;
range_low[1]=-5;  range_hi[1]=5;
range_low[2]=5;   range_hi[2]=11;

//Declare Vectors To Store Run Numbers

//Three Board Vectors
std::vector<int> condition_000;
std::vector<int> condition_008;
std::vector<int> condition_088;
std::vector<int> condition_080;
std::vector<int> condition_880;
std::vector<int> condition_808;
std::vector<int> condition_800;

//Error Vector
std::vector<int> condition_error;

//Five Board Vectors
std::vector<int> condition_00000;
std::vector<int> condition_00008;
std::vector<int> condition_00080;
std::vector<int> condition_00088;
std::vector<int> condition_00800;
std::vector<int> condition_00808;
std::vector<int> condition_00880;
std::vector<int> condition_00888;
std::vector<int> condition_08000;
std::vector<int> condition_08008;
std::vector<int> condition_08080;
std::vector<int> condition_08088;
std::vector<int> condition_08800;
std::vector<int> condition_08808;
std::vector<int> condition_08880;
std::vector<int> condition_08888;
std::vector<int> condition_80000;
std::vector<int> condition_80008;
std::vector<int> condition_80080;
std::vector<int> condition_80088;
std::vector<int> condition_80800;
std::vector<int> condition_80808;
std::vector<int> condition_80880;
std::vector<int> condition_80888;
std::vector<int> condition_88000;
std::vector<int> condition_88008;
std::vector<int> condition_88080;
std::vector<int> condition_88088;
std::vector<int> condition_88800;
std::vector<int> condition_88808;
std::vector<int> condition_88880;

std::vector<float> firstboard;
std::vector<float> secondboard;
std::vector<float> thirdboard;
std::vector<float> fourthboard;
std::vector<float> fifthboard;

bool firstisfit;
bool secondisfit;
bool thirdisfit;
bool fourthisfit;
bool fifthisfit;


//Clear the 3 board Vectors
condition_000.clear();condition_008.clear();condition_088.clear();
condition_080.clear();condition_880.clear();condition_808.clear();condition_800.clear();condition_error.clear();

//Clear the 5 board vectors



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
  std::cout<<"Are there five digitizer boards? Please enter 1 for 'yes' or 0 for 'no'"<<std::endl;
  std::cin>>IsFiveBoards;

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
  // TH1 *h1 =(TH1*)gDirectory->FindObjectAny("td03_time_t00_ligl03");
  // TH1 *h2 =(TH1*)gDirectory->FindObjectAny("td03_time_t00_ligl10");
  // TH1 *h3 =(TH1*)gDirectory->FindObjectAny("td03_time_t00_ligl17");

  TH1 *h1 =(TH1*)gDirectory->FindObjectAny("td0_03_time_t00_ligl03");
  TH1 *h2 =(TH1*)gDirectory->FindObjectAny("td0_03_time_t00_ligl10");
  TH1 *h3 =(TH1*)gDirectory->FindObjectAny("td0_03_time_t00_ligl17");
 
  firstisfit=false;
  secondisfit=false;
  thirdisfit=false;
  
  if (h1->GetEntries()) Fit(h1,1);
  if (h2->GetEntries()) Fit(h2,2);
  if (h3->GetEntries()) Fit(h3,3);
  Sort(ThisRun);
  

}//End of AnalyzeRun function


void Fit(TH1* MyHist, int BoardNumber){

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
	  if ( (mean>range_low[i]) && (mean<range_hi[i]) )
	    {
	      if (BoardNumber==1) 
		{
		  // std::cout<<"The standard deviation was: "<<stdeviation<<" and a mean value of: "<<mean<<std::endl;
		  //std::cout<<"With a high end of teh range being:  "<<range_hi[i]<<" with a lower end of the range: "<<range_low[i]<<std::endl;
		  firstboard.push_back(mean);
		  firstisfit=true;
	      //new TCanvas;
	      //MyHist->Draw();
		}
	      else if (BoardNumber==2)
		{
		  secondboard.push_back(mean);
		  secondisfit=true;
		  // new TCanvas;
	      //MyHist->Draw();
		}
	      else if (BoardNumber==3) 
		{
		  thirdboard.push_back(mean);
		  thirdisfit=true;
		  //new TCanvas;
		  //MyHist->Draw();
		}
	    }//end of if it falls in range
	}//end of if fit exists
    }//end of loop over ranges
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
      
         
      if ( (firstboard[firstboard.size()-1] > -2) && (firstboard[firstboard.size()-1] < 2) ) Board1Result=0;

      if ( (secondboard[secondboard.size()-1] > -2) && (secondboard[secondboard.size()-1] < 1) ) Board2Result=0;
      if ( (secondboard[secondboard.size()-1] > -9) && (secondboard[secondboard.size()-1] < -6.8) ) 
	{
	  Board2Result=-8;
	}
      if ( (secondboard[secondboard.size()-1] > 7) && (secondboard[secondboard.size()-1] < 10) ) Board2Result=8;

      if ( (thirdboard[thirdboard.size()-1] > -1) && (thirdboard[thirdboard.size()-1] < 0) ) Board3Result=0;
      if ( (thirdboard[thirdboard.size()-1] > -9) && (thirdboard[thirdboard.size()-1] < -6) ) Board3Result=-8;
      if ( (thirdboard[thirdboard.size()-1] > 7) && (thirdboard[thirdboard.size()-1] < 10) ) 
	{
	  Board3Result=8;
	  std::cout<<"I made it here"<<std::endl;
	}



      if ( (Board2Result==-8) || (Board3Result==-8) )
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
