#include "Electron.h"
#include "Proton.h"
#include "MatPoint.h"
#include <iostream>

using namespace std;

int main(){
  

  
  //Costruzione da particella "nota"
  MatPoint p(Proton(), Vector3(1,0,0));
  cout << p.Mass() << " " << p.Charge() << endl;
  cout << p.R() << endl;
  cout << p.V() << endl;
 

  

  //Costruzione punto materiale generico
  MatPoint pm(1,0,Vector3(1,0,0),Vector3(1,1,1));
  cout << pm.Mass() << " " << pm.Charge() << endl;
  cout << pm.R() << endl;
  cout << pm.V() << endl;


  // Calcolo Campo Gravitazionale
  Vector3 v = pm.GravField(Vector3(1.5,0,0));
  if (v.X()!=-4){
    cout << "Errore campo vettoriale:" << endl;
    cout << " valore aspettato -4, ottenuto " << v.X() << endl;
  }
  
  
}
