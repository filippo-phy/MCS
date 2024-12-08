namespace data{
  vector<double>  x, y, ex, ey;
}

double fun(const double *x,const double *par){
  return par[1]*(*x)+par[0];
}

void fcn(int &npar,double *gin,double &f,double *par,int iflag){
  f = 0.0;
  for (int i=0;i<data::x.size();i++){
    f += pow(data::y[i]-fun(&data::x[i],par)/data::ey[i],2);//no return perchè f è modificato visto che è passato per referenza
    // Calcolo del Minimi Quadrati
    
  }
}

void fitlin(){
  ifstream file("pendolo.dat");
  double x,y,ex,ey;
  while (file >> x >> y >> ex >> ey){
    data::x.push_back(x); data::y.push_back(y); data::ex.push_back(ex); data::ey.push_back(ey);
  }

  // Define the minimization problem
  TMinuit *minuit = new TMinuit(2); // numero di parametri  
  minuit->SetFCN(fcn);
  minuit->SetErrorDef(1);
    // per ogni indice inserisco nome, valore iniziale, step, minimo, massimo del parametro
  minuit->DefineParameter(0,"b",0,0.01,0.0,0.0);
  minuit->DefineParameter(1,"a",4,0.01,0.0,0.0);

  // Minimize
  minuit->Command("MIGRAD"); // Comando di minimizzazione

  // Get result
  double a, b, ea, eb;
  minuit->GetParameter(0,b,eb);
  minuit->GetParameter(1,a,ea);
  // per ogni indice estraggo il valore del parametro e del suo errore
  minuit->GetParameter(0, b, eb);
  minuit->GetParameter(1, a, ea);

  //stampa matrice covarianza
  double cov[2][2];
  minuit->mnemat(&cov[0][0],2);
  std::cout<<cov[0][0] << "  " << cov[0][1] << std::endl;
  std::cout<<cov[1][0] << "  " << cov[1][1] << std::endl;

  //contour
  minuit->SetErrorDef(4);
  TGraph *gr = (TGraph *)minuit->Contour(100,0,1);
  gr->Draw("AC");
  minuit->SetErrorDef(1);
  TGraph *gr2 = (TGraph *)minuit->Contour(100,0,1);//Contour ritorna tOBject, allora è necessaria la conversione del type
  gr2->Draw("C");
  
  
  

}
