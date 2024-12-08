#include <string>
#include <cmath>
#include <fstream>
#include <vector>

#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TSystem.h>

#include "OdeSolver.h"
#include "Vector3.h"
#include "MatPoint.h"

using namespace std;

Vector3 fInternal(unsigned int i,unsigned int j, double t, vector<MatPoint> p){
  //STEP 2 definizione forza interna
  // * ritorna la forza interna che il corpo j esercita su i
  MatPoint corpo_i=p[i];
  MatPoint corpo_j=p[j];
  Vector3 P=corpo_i.R();
  Vector3 F_int=(corpo_j.GravField(P))*corpo_i.Mass();
  
  return F_int;
}

Vector3 fExternal(unsigned int i, double t, vector<MatPoint> p){
  //STEP 2 definizione forza esterna
  // * ritorna la forza esterna sul corpo i
  Vector3 F_ext;

  return F_ext;
}

Vector3 AngularMomentum(unsigned int i, unsigned int polo, OdeSolver p){
  return p.GetMatPoint(i).Mass()*(p.GetMatPoint(i).R()-p.GetMatPoint(polo).R()).Cross(p.GetMatPoint(i).V()-p.GetMatPoint(polo).V());
}
								   

int main(){   
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  //Lettura dei dati dal file
  double mass;
  double x,y,z,vx,vy,vz;
  string metodo;
  ifstream f("fileInput.dat");

  // STEP 1 - opzione 1
  // * Creazione OdeSolver vuoto (senza passare vector<MatPoint>);
  // * Assegnazione dei MatPoint con il metodo AddMatPoint
  cout<<"Inserire il metodo di risoluzione dell'ODE (Eulero, Rk2, Verlet_V), oppure digitare 'confronto' per comparare i momenti angolari ottenuti tramite i metodi Runge Kutta (2) e Verlet velocity: " << flush;
  cin>>metodo;

  // STEP 1 - opzione 2
  // * Creazione e riempimento vector<MatPoint>
  // * Creazione di OdeSolver passando vector<MatPoint>

   if (metodo!="confronto" && metodo!="Eulero" && metodo!="Rk2" && metodo!="Verlet_V" ){//controllo input da terminale
     cerr << "metodo non implementato"<< endl;
     return 1;
   }

  if(metodo!="confronto"){

    OdeSolver ode(metodo);
    
    while (f >> mass >> x >> y >> z >> vx >> vy >> vz){
      Vector3 R(x, y, z);
      Vector3 V(vx, vy, vz);
      MatPoint planet(mass,0, R, V);
      ode.AddMatPoint(planet); 
    }

    // Creazione classe OdeSolver (per la soluzione dell'equ. diff.)
    double giorno = 86400; // giorno in secondi
    ode.fInternal = fInternal;
    ode.fExternal = fExternal;
    ode.DeltaT(giorno*0.5);
  
    //Creazione dei grafici (uno per pianeta)
    vector<TGraph> gr(ode.N());
    TCanvas c("c","Orbite dei pianeti",10,10,500,500);

    Vector3 L_tot;
    Vector3 L_tot_0;
    vector<double> Momentum;
  
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
      L_tot_0 = L_tot_0+AngularMomentum(i, 0, ode);
      
    }

    gPad->Modified(); gPad->Update();
    app.Run(true);

    //Run del metodo numerico + grafico in tempo reale delle coordinate e del mom. angolare totale
    int contatore=0;
    Momentum.push_back(L_tot_0.Mod());
 
    while (ode.T()<365*giorno){
      ode.Step();
      for (unsigned int i=0;i<ode.N();i++){
	//STEP 4 riempimento delle grafico gr[i] con le coordinate aggiornate dei pianeti
	// * accedere al MatPoint i-esimo, al vettore di coordinate spaziali, alla coordinata voluta
	MatPoint planet = ode.GetMatPoint(i);
	Vector3 R_planet = planet.R();
	Vector3 R_sole;
	if (i==0) {
	  R_sole = R_planet;
	}
	double X_planet = R_planet.X();
	double Y_planet = R_planet.Y();
      

	L_tot = L_tot+AngularMomentum(i, 0, ode);   

	// * inserire nel grafico gr[i] le coordinate X e Y;
	// N.B. L'indice del nuovo punto da inserire è pari al numero di punti già presente in ciascun grafico
	gr[i].SetPoint(contatore, X_planet, Y_planet);
      
      }

      Momentum.push_back(L_tot.Mod());
    
      contatore++;
      L_tot=0;
      gPad->Modified(); gPad->Update();
      gSystem->ProcessEvents();
    }

    app.Run(true);
 


    TGraph momentum;
    TCanvas c2("c2","Momento angolare totale del sistema",10,10,500,500);
  
    //grafico momento
    for (unsigned int i=0; i<Momentum.size(); i++){
      momentum.SetPoint(i, i, Momentum[i]/Momentum[0]);
      momentum.Draw("AP");
      momentum.SetMarkerSize(1);

      gPad->Modified(); gPad->Update();
      gSystem->ProcessEvents();
    }
  
    app.Run(true);
  }



  else{

    //Creazione di un vector di OdeSolver per la soluzione in parallelo delle eqz. diff. con metodi distinti
    vector<OdeSolver> ODE;
    OdeSolver ode_rk2("Rk2"), ode_verlet("Verlet_V");

    ODE.push_back(ode_rk2);
    ODE.push_back(ode_verlet);

    //Set dei dati iniziali e degli altri parametri del problema
    while (f >> mass >> x >> y >> z >> vx >> vy >> vz){
      Vector3 R(x, y, z);
      Vector3 V(vx, vy, vz);
      MatPoint planet(mass,0, R, V);
      for(int j=0; j<2; j++){
	ODE[j].AddMatPoint(planet);
      } 
    }

    double giorno = 86400; // giorno in secondi

    for(int j=0; j<2; j++){
      ODE[j].fInternal = fInternal;
      ODE[j].fExternal = fExternal;
      ODE[j].DeltaT(giorno*0.5);
    }

    //Dichiarazione e inizializzazione di un vector per memorizzare i momenti angolari calcolati ad ogni step per ciascun metodo
    vector<Vector3> L_tot;
    Vector3 l;
    for(int j=0; j<2; j++){
      L_tot.push_back(l);
    }

    //creazione del grafico dove visualizzare il confronto
    TGraph momentum;
    TCanvas c1("c1","CONFRONTO",10,10,500,500);

    for(int j=0; j<2; j++){//stato iniziale
      for(unsigned int i=0; i<ODE[j].N() ; i++){
	L_tot[j] = L_tot[j]+AngularMomentum(i, 0, ODE[j]);

      }
    }
    
    //momentum.SetPoint(0, 0, abs(L_tot[0].Mod()-L_tot[1].Mod()));

    momentum.SetPoint(0, 0, (L_tot[0].Mod())/(L_tot[1].Mod()));
    momentum.Draw("AP");
    momentum.GetXaxis()->SetTitle("Step");//Assegnazione del nome all'asse x
    momentum.GetYaxis()->SetTitle("L_RK2/L_Verlet");//assegnazione del nome all'asse y
    gPad->Modified(); gPad->Update();
    gSystem->ProcessEvents();
    app.Run(true);


    //Risoluzione del problema con i due metodi in parallelo
    int contatore=1;

    while (ODE[1].T()<365*giorno){
      for(int j=0; j<2; j++){
	ODE[j].Step();

	L_tot[j]=l;//pulizia dai dati precedenti

	for (unsigned int i=0;i<ODE[j].N();i++){

	  L_tot[j] = L_tot[j]+AngularMomentum(i, 0, ODE[j]);   
      
	}
      }

      //momentum.SetPoint(contatore, contatore, (L_tot[0]-L_tot[1]).Mod());
      momentum.SetPoint(contatore, contatore, (L_tot[0].Mod())/(L_tot[1].Mod()));
      gPad->Modified(); gPad->Update();
      gSystem->ProcessEvents();
      contatore++;
    }

    app.Run(true);
  
  }

  return 0;
}
