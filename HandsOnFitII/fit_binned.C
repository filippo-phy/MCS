void fit_binned(){
  ifstream file("dati.dat");
  double x;
  TH1D *h=new TH1D("h", "titolo", 100, 0, 40);//isto dinamico
  while(file>>x){//riempo l'istogramma
    h->Fill(x);
  }

  h->SetMarkerStyle(20);
  h->Draw("E");//stampa con errori
 
  TF1 *fe=new TF1("fe", "[0]*([3]*TMath::Gaus(x, [1],[2],1)+(1-[3])/[4]*exp(-x/[4]))", 0, 40);//pdf -> gaussiana + exp, 3 varia tra 0 e 1
  fe->SetParameter(1, 15);
  fe->SetParameter(2, 1.0);
  fe->SetParameter(4, 10);
  fe->SetParameter(3, 0.5);

  /*
  fe->FixParameter(0, 1); //il parametro è fissato per tutta l'interazione
  h->Fit("fe", "0MULTI"); //likeliohood non estesa
  fe->SetParameter(0, h->GetEntries()*h->GetBinWidth(0));
  fe->Draw("SAME");
  */

  fe->SetParameter(0, h->GetEntries()*h->GetBinWidth(0));
  h->Fit("fe", "L"); //likeliohood estesa
  fe->Draw("SAME");
  
}

