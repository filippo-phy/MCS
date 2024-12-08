{
  TRandom3 rnd;
  rnd.SetSeed(123456789);

  double d=0.20;
  double L=0.01;

  int N=1000000;

  int Nacc=0;
  int Nacc2=0;

  for (int i=0; i<N; i++){
    //genero uniformemente in cos(theta) e phi (sen(theta)d_thetad_phi)
    double phi=rnd.Rndm()*2*TMath::Pi();
    double cthe = rnd.Rndm()*2-1;

    double the=acos(cthe);
    if (the < TMath::Pi()*0.5){
      double al=d/cthe;
      double x=al*sin(the)*cos(phi);
      double y=al*sin(the)*sin(phi);

      if (fabs(x)<L*0.5 && fabs(y)<L*0.5 ){ 
	Nacc++;
      }

      if ( fabs(x)<L*0.5 && fabs(y)<L*0.5){  //TMath::Abs(x)<L*0.5 && TMath::Abs(y)<L*0.5
	Nacc2++;
      }
    }

  }

    double p= (double) Nacc/N;
    double ep= sqrt(p*(1-p)/N);
    
    cout << "Efficienza " << p << endl;
    cout << "Valore approssimato " << L*L/(4*TMath::Pi()*d*d) << endl;

    double p2= (double) Nacc2/N;
    double ep2= sqrt(p2*(1-p2)/N);
    

    cout << "Efficienza " << p2 << endl;
    cout << "Valore approssimato " << L*L/(4*TMath::Pi()*d*d) << endl;


  
}

  
			
			
