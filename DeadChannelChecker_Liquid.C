{

Int_t FirstRun;
Int_t LastRun;
bool IsFiveBoards;
char FileName[128];
FILE *ptr_file;

  std::cout<<"What is the first run in the range?"<<std::endl;
  std::cin>>FirstRun;
  std::cout<<"What is the last run in the range?"<<std::endl;
  std::cin>>LastRun;
  std::cout<<"Are there five digitizer boards? Please enter 1 for 'yes' or 0 for 'no'"<<std::endl;
  std::cin>>IsFiveBoards;

ofstream myout;
myout.open("RunsWithDeadChannels.txt");

for (int i=FirstRun;i<=LastRun;i++)
{
  sprintf(FileName,"jgomez2-dflt-tag-%i.root",ThisRun);
  ptr_file=fopen(FileName,"r");
  if(ptr_file==NULL) return;

  TFile *f = new TFile(FileName);
  f->cd("histos/Bopper");

TH1 *h1 =(TH1*)gDirectory->FindObjectAny("fifoNIn");

Int_t numberOfXBins= h1->GetXaxis()->GetNbins();
bool FirstDeadChannel= true;

for (int xbin=1;xbin<=numberOfXBins;xbin++)
{
if (!h1->GetBinContent(xbin)) 
    {
      if (FirstDeadChannel) 
        {
          myout<<"Run number was: "<<i<<" and the channel(s) were: "<<endl;
          myout<<h1->GetXaxis()->GetBinLabel(xbin)<<endl; 
          FirstDeadChannel= false
        }
        else myout<<h1->GetXaxis()->GetBinLabel(xbin)<<endl;
    }

}//end of loop over histogram bins

}//end of loop over runs

myout.close();

}
