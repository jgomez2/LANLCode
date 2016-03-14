{

  //Define X,Y bins for First Histogram                                                                                                  
  Float_t firstXbins[5]={0,15,100,300,1000};
  Float_t firstYbins[5]={0,2,4,8,16};

  //Define X,Y bins for Second Histogram                                                                                                 
  Float_t secondXbins[5]={0,15,100,300,1000};
  Float_t secondYbins[5]={0,8,10,20,200};

  //Define X,Y bins for Third Histogram                                                                                                  
  Float_t thirdXbins[5]={0,15,100,300,1000};
  Float_t thirdYbins[5]={0,16,32,64,1000};

  
  //Now Define the histograms                                                                                                            
  TH2F *first = new TH2F("first","",4,firstXbins,4,firstYbins);
  gStyle->SetOptStat(0);
 
  
  TH2F *second = new TH2F("second","",4,secondXbins,4,thirdYbins);
  //second->GetYaxis()->SetTitle("Some Y Title");
  //second->GetYaxis()->CenterTitle(1);
 
  
  TH2F *third = new TH2F("third","",4,thirdXbins,4,thirdYbins);
  third->GetXaxis()->SetTitle("Gamma Energy (MeV)");
  third->GetXaxis()->CenterTitle(1);
  //CAN Play with title Size
  //  third->GetXaxis()->SetTitleSize(0.01);
  ///can also set the tick length if you want
  third->GetXaxis()->SetTickLength(0.02);
  

  TCanvas *c1 = new TCanvas("c1","John's Canvas",10,10,700,700);
  
  TPad *p1 = new TPad("p1", "p1", 0.05, 0.6425, 0.95, 0.95, 22);
  //p1->SetTopMargin(0);
  p1->SetBottomMargin(0);
  p1->SetTickx(1);
  p1->Draw();
  

  TPad *p2 = new TPad("p2", "p2", 0.05, 0.3575, 0.95, 0.6425, 18);
  p2->SetTopMargin(0);
  p2->SetBottomMargin(0);
  p2->SetTickx(1);
  p2->Draw();

  TPad *p3 = new TPad("p3", "p3", 0.05, 0.05, 0.95, 0.3575, 21);
  p3->SetTopMargin(0);
  p3->SetTickx(1);
  p3->Draw();
  

  p1->cd(); first->Draw();
  p2->cd(); second->Draw();
  p3->cd(); third->Draw();
  
  

  















}
