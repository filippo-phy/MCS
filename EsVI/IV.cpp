#include <TApplication.h>
#include <iostream>
#include <fstream>
#include <TAxis.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
  TApplication app("app", 0, 0);


   ifstream ifile("out.dat"); //stream del file di input chiamato da tastiera

   vector<double> Corrente, Tensione;//dichiarazione di due vector per contenere i valori dell'intensità di corrente e della tensione
   double V, I, eI; 
   double R= 109.872;
   int i=0;
   TGraphErrors graph;
   double A= 3.9*pow(10,-3);
   double T=(R-100)/(A*100);

   while (ifile >> V >> I >> eI){//stream del file riga per riga e assegnazione dei valori letti alle rispettive variabili
     
     graph.SetPoint(i, V, I);//assegnazione dei valori di T e P agli assi x e y
     graph.SetPointError(i, 0, eI);//assegnazione dell'incertezze assolute associate a T e P agli assi
     i++;
   }

   TF1 f("f", "[0]*(exp([1]*x/(23+273.15))-1)");//dihiarazione di un oggetto della classe TF1 (f) e della funzione di fit
   f.SetParameter(0, 0.01);//inizializzazione del parametro 0
   f.SetParameter(1, 10000);//inizializzazione del parametro 1

   graph.Fit("f");//tracciamento del fit

   graph.Draw("ap");
 

   
   app.Run();
}


  
  
  
