{
  Double_t TotalNumberOfRuns=0.0;
  Double_t RunsWithErrors=0.0;
  Int_t FirstRun;
  Int_t LastRun;
  char FileName[128];
  FILE *ptr_file;
  
  std::cout<<"What is the first run in the range?"<<std::endl;
  std::cin>>FirstRun;
  std::cout<<"What is the last run in the range?"<<std::endl;
  std::cin>>LastRun;
    
  ofstream myout;
  myout.open("RunsWithDeadChannels.txt");
  
  for (int i=FirstRun;i<=LastRun;i++)
    {
      sprintf(FileName,"jgomez2-dflt-tag-%i.root",i);
      ptr_file=fopen(FileName,"r");
      if(ptr_file==NULL) return;
      
      TFile *f = new TFile(FileName);
      f->cd("histos/Bopper");
      
      TotalNumberOfRuns+=1.0;
      TH1 *h1 =(TH1*)gDirectory->FindObjectAny("fifoNIn");
      
      Int_t numberOfXBins= h1->GetXaxis()->GetNbins();
      bool FirstDeadChannel= true;
      
      for (int xbin=1;xbin<=numberOfXBins;xbin++)
	{
	  if (xbin==2 || xbin==3 || xbin==4 || xbin==17 || xbin==18 || xbin==19 || xbin==20 || xbin==33 || xbin==34 || xbin==35 || xbin==36|| xbin==39 || xbin==40 || xbin==79 || xbin==80) continue;
	  if (!h1->GetBinContent(xbin)) 
	    {
	      if (FirstDeadChannel) 
		{
		  myout<<"Run number was: "<<i<<" and the channel(s) were: "<<endl;
		  myout<<h1->GetXaxis()->GetBinLabel(xbin)<<endl; 
		  FirstDeadChannel= false;
		  RunsWithErrors+=1.0;
		}
	      else myout<<h1->GetXaxis()->GetBinLabel(xbin)<<endl;
	    }
	  
	}//end of loop over histogram bins
      
    }//end of loop over runs
  

  
  myout<<"The total number of runs was: "<<TotalNumberOfRuns<<" and the number of runs with errors was: "<<RunsWithErrors<<" For a percentage of: "<< RunsWithErrors/TotalNumberOfRuns<<endl;

myout.close();
 
}//End of whole thing
