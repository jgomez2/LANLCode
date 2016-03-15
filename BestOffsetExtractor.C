
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
condition_00000.clear(); condition_00008.clear(); condition_00080.clear(); condition_00088.clear(); condition_00800.clear(); condition_00808.clear(); condition_00880.clear(); condition_00888.clear(); condition_08000.clear(); condition_08008.clear(); condition_08080.clear(); condition_08088.clear(); condition_08800.clear(); condition_08808.clear(); condition_08880.clear(); condition_08888.clear(); condition_80000.clear(); condition_80008.clear(); condition_80080.clear(); condition_80088.clear(); condition_80800.clear(); condition_80808.clear(); condition_80880.clear(); condition_80888.clear(); condition_88000.clear(); condition_88008.clear(); condition_88080.clear(); condition_88088.clear(); condition_88800.clear(); condition_88808.clear(); condition_88880.clear();


firstboard.clear();
secondboard.clear();
thirdboard.clear();
fourthboard.clear();
fifthboard.clear();

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

  TH1 *h1 =(TH1*)gDirectory->FindObjectAny("td0_04_time_t00_liquid03");
  TH1 *h2 =(TH1*)gDirectory->FindObjectAny("td0_04_time_t00_liquid10");
  TH1 *h3 =(TH1*)gDirectory->FindObjectAny("td0_04_time_t00_liquid17");

  if (IsFiveBoards)
    {
      TH1 *h4 =(TH1*)gDirectory->FindObjectAny("td0_04_time_t00_liquid27");
      TH1 *h5 =(TH1*)gDirectory->FindObjectAny("td0_04_time_t00_liquid50");
    }

  firstisfit=false;
  secondisfit=false;
  thirdisfit=false;
  fourthisfit=false;
  fifthisfit=false;
  
  if (h1->GetEntries()) Fit(h1,1);
  if (h2->GetEntries()) Fit(h2,2);
  if (h3->GetEntries()) Fit(h3,3);
  if (IsFiveBoards)
    {
      if (h4->GetEntries()) Fit(h4,4);
      if (h5->GetEntries()) Fit(h5,5);
    }
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
	      else if (BoardNumber==4)
		{
		  fourthboard.push_back(mean);
		  fourthisfit=true;
		  // new TCanvas;
	      //MyHist->Draw();
		}
	      else if (BoardNumber==5) 
		{
		  fifthboard.push_back(mean);
		  fifthisfit=true;
		  //new TCanvas;
		  //MyHist->Draw();
		}
	      
	    }//end of if it falls in range
	}//end of if fit exists
    }//end of loop over ranges
}//End of fit function


void Sort(int RunNumber){

  

  if (IsFiveBoards)
    {
      if (firstisfit==false || secondisfit==false || thirdisfit==false || fourthisfit==false || fifthisfit==false) 
	{
	  condition_error.push_back(RunNumber);
	  return;
	}
    }


  if (IsFiveBoards==false)
    {
      if (firstisfit==false || secondisfit==false || thirdisfit==false) 
	{
	  condition_error.push_back(RunNumber);
	  return;
	}
    }


  // for (int ii=0; ii<firstboard.size();ii++)
  // {
      Double_t Board1Result=0;
      Double_t Board2Result=0;
      Double_t Board3Result=0;
      Double_t Board4Result=0;
      Double_t Board5Result=0;
      
      //First Board Fit
      if ( (firstboard[firstboard.size()-1] > -2) && (firstboard[firstboard.size()-1] < 2) ) Board1Result=0;

      
      //Second Board Fit
      if ( (secondboard[secondboard.size()-1] > -2) && (secondboard[secondboard.size()-1] < 1) ) Board2Result=0;
      if ( (secondboard[secondboard.size()-1] > -9) && (secondboard[secondboard.size()-1] < -6.8) ) 
	{
	  Board2Result=-8;
	}
      if ( (secondboard[secondboard.size()-1] > 7) && (secondboard[secondboard.size()-1] < 10) ) Board2Result=8;
      

      //Third Board Fit
      if ( (thirdboard[thirdboard.size()-1] > -1) && (thirdboard[thirdboard.size()-1] < 0) ) Board3Result=0;
      if ( (thirdboard[thirdboard.size()-1] > -9) && (thirdboard[thirdboard.size()-1] < -6) ) Board3Result=-8;
      if ( (thirdboard[thirdboard.size()-1] > 7) && (thirdboard[thirdboard.size()-1] < 10) ) 
	{
	  Board3Result=8;
	  //std::cout<<"I made it here"<<std::endl;
	}
      
      
      if (IsFiveBoards)
	{
	  //Fourth Board Fit
	  if ( (fourthboard[fourthboard.size()-1] > -1) && (fourthboard[fourthboard.size()-1] < 0) ) Board4Result=0;
	  if ( (fourthboard[fourthboard.size()-1] > -9) && (fourthboard[fourthboard.size()-1] < -6) ) Board4Result=-8;
	  if ( (fourthboard[fourthboard.size()-1] > 7) && (fourthboard[fourthboard.size()-1] < 10) ) 
	    {
	      Board4Result=8;
	      //std::cout<<"I made it here"<<std::endl;
	    }
	  
	  //Fifth Board Fit
	  if ( (fifthboard[fifthboard.size()-1] > -1) && (fifthboard[fifthboard.size()-1] < 0) ) Board5Result=0;
	  if ( (fifthboard[fifthboard.size()-1] > -9) && (fifthboard[fifthboard.size()-1] < -6) ) Board5Result=-8;
	  if ( (fifthboard[fifthboard.size()-1] > 7) && (fifthboard[fifthboard.size()-1] < 10) ) 
	    {
	      Board5Result=8;
	      //std::cout<<"I made it here"<<std::endl;
	    }
	  
	}//only check the other fits if there is five boards
      
      

      if ( (Board2Result==-8) || (Board3Result==-8) || (Board4Result==-8) || (Board5Result==-8))
	{
	  Board1Result+=8;
	  Board2Result+=8;
	  Board3Result+=8;
	  Board4Result+=8;
	  Board5Result+=8;
	}
      
      

      //Categorize 
      if (IsFiveBoards==false)
	{
	  if      ((Board1Result==0) && (Board2Result==0) && (Board3Result==0)) condition_000.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==0) && (Board3Result==8)) condition_008.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==0)) condition_080.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==8)) condition_088.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==0)) condition_800.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==8)) condition_808.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==0)) condition_880.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==8)) condition_000.push_back(RunNumber); // not _888
	}
      if (IsFiveBoards)
	{
	  if      ((Board1Result==0) && (Board2Result==0) && (Board3Result==0) && (Board4Result==0) && (Board5Result==0)) condition_00000.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==0) && (Board3Result==0) && (Board4Result==0) && (Board5Result==8)) condition_00008.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==0) && (Board3Result==0) && (Board4Result==8) && (Board5Result==0)) condition_00080.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==0) && (Board3Result==0) && (Board4Result==8) && (Board5Result==8)) condition_00088.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==0) && (Board3Result==8) && (Board4Result==0) && (Board5Result==0)) condition_00800.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==0) && (Board3Result==8) && (Board4Result==0) && (Board5Result==8)) condition_00808.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==0) && (Board3Result==8) && (Board4Result==8) && (Board5Result==0)) condition_00880.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==0) && (Board3Result==8) && (Board4Result==8) && (Board5Result==8)) condition_00888.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==0) && (Board4Result==0) && (Board5Result==0)) condition_08000.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==0) && (Board4Result==0) && (Board5Result==8)) condition_08008.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==0) && (Board4Result==8) && (Board5Result==0)) condition_08080.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==0) && (Board4Result==8) && (Board5Result==8)) condition_08088.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==8) && (Board4Result==0) && (Board5Result==0)) condition_08800.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==8) && (Board4Result==0) && (Board5Result==8)) condition_08808.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==8) && (Board4Result==8) && (Board5Result==0)) condition_08880.push_back(RunNumber);
	  else if ((Board1Result==0) && (Board2Result==8) && (Board3Result==8) && (Board4Result==8) && (Board5Result==8)) condition_08888.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==0) && (Board4Result==0) && (Board5Result==0)) condition_80000.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==0) && (Board4Result==0) && (Board5Result==8)) condition_80008.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==0) && (Board4Result==8) && (Board5Result==0)) condition_80080.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==0) && (Board4Result==8) && (Board5Result==8)) condition_80088.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==8) && (Board4Result==0) && (Board5Result==0)) condition_80800.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==8) && (Board4Result==0) && (Board5Result==8)) condition_80808.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==8) && (Board4Result==8) && (Board5Result==0)) condition_80880.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==0) && (Board3Result==8) && (Board4Result==8) && (Board5Result==8)) condition_80888.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==0) && (Board4Result==0) && (Board5Result==0)) condition_88000.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==0) && (Board4Result==0) && (Board5Result==8)) condition_88008.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==0) && (Board4Result==8) && (Board5Result==0)) condition_88080.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==0) && (Board4Result==8) && (Board5Result==8)) condition_88088.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==8) && (Board4Result==0) && (Board5Result==0)) condition_88800.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==8) && (Board4Result==0) && (Board5Result==8)) condition_88808.push_back(RunNumber);	  
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==8) && (Board4Result==8) && (Board5Result==0)) condition_88880.push_back(RunNumber);
	  else if ((Board1Result==8) && (Board2Result==8) && (Board3Result==8) && (Board4Result==8) && (Board5Result==8)) condition_00000.push_back(RunNumber);//Not _88888
	  
	}//End of check for five Boards

      // }//end of loop over board results
}//end of sort function


void Print(){
  /////////////////////////////////////////////////////
  /////NOW PRINT THE RESULTS IN THE DESIGNATED FILES///
  /////////////////////////////////////////////////////

  ofstream myout;
  myout.open("CombinedResults.txt");

  if (IsFiveBoards==false)
    {
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
      
    }//Do this for three boards


  if (IsFiveBoards)
    {
      myout<<"First Board"<<"    "<<"Second Board"<<"    "<<"Third Board"<<"     "<<"Fourth Board"<<"     "<<"Fifth Board"<<endl;
      for (int ii=0; ii<firstboard.size();ii++)
	{
	  myout<<firstboard[ii]<<"    "<<secondboard[ii]<<"    "<<thirdboard[ii]<<"     "<<fourthboard[ii]<<"     "<<fifthboard[ii]<<endl;
	}
      myout.close();
      // if(firstboard.size()!=0)
      
      //Now make the text files that will hold the run numbers
      ofstream out1;
      out1.open("ClockOffset_00000.iac");
      for (int j=0;j<condition_00000.size();j++) out1<<condition_00000[j]<<",";
      out1.close();
      
      ofstream out2;
      out2.open("ClockOffset_00008.iac");
      for (int j=0;j<condition_00008.size();j++) out2<<condition_00008[j]<<",";
      out2.close();
      
      ofstream out3;
      out3.open("ClockOffset_00080.iac");
      for (int j=0;j<condition_00080.size();j++) out3<<condition_00080[j]<<",";
      out3.close();
      
      ofstream out4;
      out4.open("ClockOffset_00088.iac");
      for (int j=0;j<condition_00088.size();j++) out4<<condition_00088[j]<<",";
      out4.close();
      
      ofstream out5;
      out5.open("ClockOffset_00800.iac");
      for (int j=0;j<condition_00800.size();j++) out5<<condition_00800[j]<<",";
      out5.close();
      
      ofstream out6;
      out6.open("ClockOffset_00808.iac");
      for (int j=0;j<condition_00808.size();j++) out6<<condition_00808[j]<<",";
      out6.close();
      
      ofstream out7;
      out7.open("ClockOffset_00880.iac");
      for (int j=0;j<condition_00880.size();j++) out7<<condition_00880[j]<<",";
      out7.close();
      
      ofstream out8;
      out8.open("ClockOffset_00888.iac");
      for (int j=0;j<condition_00888.size();j++) out8<<condition_00888[j]<<",";
      out8.close();
      
      ofstream out9;
      out9.open("ClockOffset_08000.iac");
      for (int j=0;j<condition_08000.size();j++) out9<<condition_08000[j]<<",";
      out9.close();
      
      ofstream out10;
      out10.open("ClockOffset_08008.iac");
      for (int j=0;j<condition_08008.size();j++) out10<<condition_08008[j]<<",";
      out10.close();
      
      ofstream out11;
      out11.open("ClockOffset_08080.iac");
      for (int j=0;j<condition_08080.size();j++) out11<<condition_08080[j]<<",";
      out11.close();
      
      ofstream out12;
      out12.open("ClockOffset_08088.iac");
      for (int j=0;j<condition_08088.size();j++) out12<<condition_08088[j]<<",";
      out12.close();
      
      ofstream out13;
      out13.open("ClockOffset_08800.iac");
      for (int j=0;j<condition_08800.size();j++) out13<<condition_08800[j]<<",";
      out13.close();
      
      ofstream out14;
      out14.open("ClockOffset_08808.iac");
      for (int j=0;j<condition_08808.size();j++) out14<<condition_08808[j]<<",";
      out14.close();

      ofstream out15;
      out15.open("ClockOffset_08880.iac");
      for (int j=0;j<condition_08880.size();j++) out15<<condition_08880[j]<<",";
      out15.close();

      ofstream out16;
      out16.open("ClockOffset_08888.iac");
      for (int j=0;j<condition_08888.size();j++) out16<<condition_08888[j]<<",";
      out16.close();

      ofstream out17;
      out17.open("ClockOffset_80000.iac");
      for (int j=0;j<condition_80000.size();j++) out17<<condition_80000[j]<<",";
      out17.close();

      ofstream out18;
      out18.open("ClockOffset_80008.iac");
      for (int j=0;j<condition_80008.size();j++) out18<<condition_80008[j]<<",";
      out18.close();

      ofstream out19;
      out19.open("ClockOffset_80080.iac");
      for (int j=0;j<condition_80080.size();j++) out19<<condition_80080[j]<<",";
      out19.close();

      ofstream out20;
      out20.open("ClockOffset_80088.iac");
      for (int j=0;j<condition_80088.size();j++) out20<<condition_80088[j]<<",";
      out20.close();

      ofstream out21;
      out21.open("ClockOffset_80800.iac");
      for (int j=0;j<condition_80800.size();j++) out21<<condition_80800[j]<<",";
      out21.close();

      ofstream out22;
      out22.open("ClockOffset_80808.iac");
      for (int j=0;j<condition_80808.size();j++) out22<<condition_80808[j]<<",";
      out22.close();

      ofstream out23;
      out23.open("ClockOffset_80880.iac");
      for (int j=0;j<condition_80880.size();j++) out23<<condition_80880[j]<<",";
      out23.close();

      ofstream out24;
      out24.open("ClockOffset_80888.iac");
      for (int j=0;j<condition_80888.size();j++) out24<<condition_80888[j]<<",";
      out24.close();

      ofstream out25;
      out25.open("ClockOffset_88000.iac");
      for (int j=0;j<condition_88000.size();j++) out25<<condition_88000[j]<<",";
      out25.close();

      ofstream out26;
      out26.open("ClockOffset_88008.iac");
      for (int j=0;j<condition_88008.size();j++) out26<<condition_88008[j]<<",";
      out26.close();

      ofstream out27;
      out27.open("ClockOffset_88080.iac");
      for (int j=0;j<condition_88080.size();j++) out27<<condition_88080[j]<<",";
      out27.close();

      ofstream out28;
      out28.open("ClockOffset_88088.iac");
      for (int j=0;j<condition_88088.size();j++) out28<<condition_88088[j]<<",";
      out28.close();



      ofstream out29;
      out29.open("ClockOffset_88800.iac");
      for (int j=0;j<condition_88800.size();j++) out29<<condition_88800[j]<<",";
      out29.close();

      ofstream out30;
      out30.open("ClockOffset_88808.iac");
      for (int j=0;j<condition_88808.size();j++) out30<<condition_88808[j]<<",";
      out30.close();

      ofstream out31;
      out31.open("ClockOffset_88880.iac");
      for (int j=0;j<condition_88880.size();j++) out31<<condition_88880[j]<<",";
      out31.close();
    }//Do this for five boards
  
  
  ofstream out32;
  out32.open("RunsWithErrors.text");
  for (int j=0;j<condition_error.size();j++) out32<<condition_error[j]<<",";
  out32.close();

}//End of Print Function
