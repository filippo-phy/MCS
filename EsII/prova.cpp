  vector<TGraph> gr(ode.N());
vector<TGraph> Verlet_mom(ode.N());
  TCanvas c("c","",10,10,500,500);
  
  //Preparazione grafico delle coordinate dei pianeti
  double au = 1.5e8;   // unita' astronimica in km
  double size = 5*au;  // 5 unita' astronimiche
  gPad->DrawFrame(-size,-size,size,size);
  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2};
  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(0,ode.GetMatPoint(i).R().X(),ode.GetMatPoint(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerStyle(20); gr[i].SetMarkerSize(0.1);
    if (i==0) gr[i].SetMarkerSize(1);
    gr[i].Draw("P");
  }
for (unsigned int i=0;i<ode.N();i++){
  double Verlet_mom=ode.GetMatPoint(i).R()*ode.GetMatPoint(i).V();
    Verlet_mom[i].SetPoint(0,0,Verlet_mom);
    Verlet_mom[i].SetMarkerColor(color[i]); Verlet_mom[i].SetMarkerStyle(20); Verlet_mom[i].SetMarkerSize(0.1);
    if (i==0) Verlet_mom[i].SetMarkerSize(1);
    Verlet_mom[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();
  app.Run(true);

  //Run del metodo numerico + grafico in tempo reale delle coordinate e del mom. angolare totale
  int contatore=0;
  while (ode.T()<365*giorno){
    ode.Step();
    for (unsigned int i=0;i<ode.N();i++){
      //STEP 4 riempimento delle grafico gr[i] con le coordinate aggiornate dei pianeti
      // * accedere al MatPoint i-esimo, al vettore di coordinate spaziali, alla coordinata voluta
      MatPoint planet = ode.GetMatPoint(i);
      Vector3 R_planet = planet.R();
      double X_planet = R_planet.X();
      double Y_planet = R_planet.Y();
      double momentum=ode.GetMatPoint(i).R()*ode.GetMatPoint(i).V();
      

      

      // * inserire nel grafico gr[i] le coordinate X e Y
      // N.B. L'indice del nuovo punto da inserire è pari al numero di punti già presente in ciascun grafico
      gr[i].SetPoint(contatore, X_planet, Y_planet);
      Verlet_mom[i].SetPoint(contatore, contatore,Verlet_mom);
      
    }
    contatore++;
    gPad->Modified(); gPad->Update();
    gSystem->ProcessEvents();
  }
  

  app.Run(true);

  return 0;
  
  
}

/*  vector<vector<double>> Momentum;
  for(unsigned int i=0; i<ode.N(); i++){
    vector<double> l;
    Momentum.push_back(l);
  }
  while (ode.T()<365*giorno){
    ode.Step();
    for (unsigned int i=0;i<ode.N();i++){
      //STEP 4 riempimento delle grafico gr[i] con le coordinate aggiornate dei pianeti
      // * accedere al MatPoint i-esimo, al vettore di coordinate spaziali, alla coordinata voluta
      MatPoint planet = ode.GetMatPoint(i);
      Vector3 R_planet = planet.R();
      double X_planet = R_planet.X();
      double Y_planet = R_planet.Y();

      Momentum[i].push_back(R_planet.Cross(ode.GetMatPoint(i).V()).Mod());

      

      // * inserire nel grafico gr[i] le coordinate X e Y
      // N.B. L'indice del nuovo punto da inserire è pari al numero di punti già presente in ciascun grafico
      gr[i].SetPoint(contatore, X_planet, Y_planet);
      
    }
    contatore++;
    gPad->Modified(); gPad->Update();
    gSystem->ProcessEvents();
  }

  app.Run(true);
 


  vector<TGraph> momentum(ode.N());
  TCanvas c2("c2","",10,10,500,500);

  gPad->DrawFrame(0, 0.9, 800, 1.02);
  unsigned int timer=1;

  //grafico momento
  
  for (unsigned int i=0;i<ode.N();i++){
    momentum[i].SetPoint(0,0,Momentum[i][0]);
    momentum[i].SetMarkerColor(color[i]); momentum[i].SetMarkerStyle(20); momentum[i].SetMarkerSize(0.5);
    if (i==0) momentum[i].SetMarkerSize(1);
    momentum[i].Draw("P");
  }

while(timer < Momentum[0].size()){
    for (unsigned int i=0; i<ode.N(); i++){
      momentum[i].SetPoint(timer,timer, Momentum[i][timer]/Momentum[i][0]);
    }

    timer++;
  
  gPad->Modified(); gPad->Update();
  gSystem->ProcessEvents();
  }
  
  app.Run(true);

  Momentum.clear(); 

  return 0;
  
  
}
*/
