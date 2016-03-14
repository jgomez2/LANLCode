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
  TH2F *first = new TH2F("first","Maybe An overall title",4,firstXbins,4,firstYbins);
  TH2F *second = new TH2F("second","",4,secondXbins,4,thirdYbins);
  second->GetYaxis()->SetTitle("Some Y Title");
  second->GetYaxis()->CenterTitle(1);

  TH2F *third = new TH2F("third","",4,thirdXbins,4,thirdYbins);
  third->GetXaxis()->SetTitle("Some Label Here");
  third->GetXaxis()->CenterTitle(1);
  //  third->GetXaxis()->SetTitleSize(0.2); ///Can fiddle with title size

  //Make a Canvas
  TCanvas *c1 = new TCanvas("c1","blah",10,10,700,700); //THIS CREATES A CANVAS WHOSE High value for x is 10, high value for y is 10, and it is 700pixels wide in each direction

  c1->SetFillColor(18);
  gStyle->SetOptStat(0); //turn off stat boxes...can still access mean and RMS info

  
  //Create the three pads that will hold our plots
  pad1 = new TPad("pad1","firstpad",0.05,0.5,0.95,0.95,21); //Top left corner  5% of width from left edge, 50% of height from low edge    //Top right corner  95% of width from left edge  95% of height from low edge
  pad1->Draw();

  pad2 = new TPad("pad2","secondpad",0.05,0.05,0.45,0.45,21);
  pad2->Draw();

  pad3 = new TPad("pad3","thirdpad",0.55,0.05,0.95,0.45,21);
  pad3->Draw();
  
  pad1->cd();
  first->Draw();

  pad2->cd();
  pad2->SetLogy(1);
  second->Draw();

  pad3->cd();
  third->Draw();




  ///////////////?ORRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
  TCanvas *c2 = new TCanvas("c2","c2",10,10,700,700);
  c2->SetFillColor(18);
  c2->cd();

  pad4 = new TPad("pad4","fourthpad",0.05,0.05,0.95,0.31,21);
  pad4->Draw();

  pad5 = new TPad("pad5","fifthpad",0.05,0.36,0.95,0.62,21);
  pad5->Draw();

  pad6 = new TPad("pad6","sixthpad",0.05,0.67,0.95,0.95,21);
  pad6->Draw();
  
  pad6->cd();
  first->Draw();

  pad5->cd();
  second->Draw();
  
  pad4->cd();
  third->Draw();



  ////////////////////OR TO BE REALLY FANCY
  TCanvas *c3 = new TCanvas("c3","c3",10,10,700,700);
  c3->cd();

  //Make a Histogram with random gaussian distribution
  TH1F *h1 = new TH1F("h1","hohum",100,-3,3);
  int i;
  for(i=0;i<10000;i++) h1->Fill(gRandom->Gaus(0,1));
  h1->Draw();
  c3->Update();

  //Make a second histogram which is the integral of h1
  TH1F *hint1 = new TH1F("hint1","h1 bins integral",100,-3,3);
  Float_t sum = 0;
  for (i=1;i<=100;i++) {
    sum += h1->GetBinContent(i);
    hint1->SetBinContent(i,sum);
  }

  // scale hint1 to the pad coordinates
  Float_t rightmax = 1.1*hint1->GetMaximum();
  Float_t scale = gPad->GetUymax()/rightmax;
  hint1->SetLineColor(kRed);
  hint1->Scale(scale);
  hint1->Draw("same");

  // draw an axis on the right side
  TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
			    gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
  axis->SetLineColor(kRed);
  axis->SetTextColor(kRed);
  axis->Draw();
  return c3;



  ////////// MOST STRAIGHT FORWARD METHOD/////////////////////
  /*
    c1->Divide(1,3);

  //Change to the first pad and draw
  c1->cd(1);
  first->Draw();

  //Change to the second pad and draw
  c1->cd(2);
  c1->GetPad(2)->SetLogy(1); //set log y ...can also do log X or whatever you want
  second->Draw(); //also worth mentioning is defining draw styles
  
  //Change to the third pad and draw
  c1->cd(3);
  third->Draw();
  */

  

  
}
