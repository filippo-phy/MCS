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

double Resistenza(vector<double> V, vector<double> I){//funzione implementata per calcolare la resistenza R0
  //la funzione prende in entrata due vettori con la stessa dimensione, uno con le misure di corrente, l'altro con quelle di tensione
  double R;
  double somma=0;

  for (int i=0; i<V.size(); i++){//dati i due vettori calcola la resistenza risultante dai valori di tensione e corrente per ogni componente 
    R=V[i]/I[i];
    somma += R; //somma di tutte le resistenze calcolate
  }

  return somma/V.size();//restituzione della resistenza media, in numero di resistenze è dato dalla dimensione di un dei vector.
}

double Temperatura(double R0, double V, double I){//funzione per il calcolo della temperatura
  double alfa = 4.82e-3; //costante alfa
  double beta = 6.67e-7; //costante beta
  double R = V/I; 

  double T = 273 + (1/(2*beta))*(sqrt(pow(alfa, 2) + 4*beta*((R/R0) -1)) - alfa); //calcolo della temperatura

  return T;//restituisce la temperatura
}

  

int main() {
   /* ATTENZIONE: l'istruzione che segue serve per far funzionare i grafici
    *             di ROOT e deve essere la prima istruzione del programma.
    *             Non aggiungete codice prima di questa istruzione
    */
   TApplication app("app", 0, 0);

   string File_Name; 
   cout << "inserire il nome del file di input: " << flush;
   cin >> File_Name; //assegnazione da tastiera del nome di un file alla stringa.

   ifstream ifile(File_Name); //stream del file di input chiamato da tastiera

   if (! ifile.good()){//controllo che la lettura del file avvenga nel modo corretto: in caso negativo restituisce un messaggio di errore
     cerr << "errore nella lettura del file '" << File_Name << "'" << endl;
     return 1;
   }

   vector<double> Corrente, Tensione;//dichiarazione di due vector per contenere i valori dell'intensità di corrente e della tensione
   double V, I, eI, eV; 
   double R0;

   while (ifile >> I >> V >> eI >> eV){//stream del file riga per riga e assegnazione dei valori letti alle rispettive variabili
     Corrente.push_back(I);//aggiunge il valore assegnato a I (intensità di corrente) al vector Corrente
     Tensione.push_back(V);//aggiunge il valore assegnato a V (tensione) al vector Tensione
   }

   if (Tensione.size()!= Corrente.size()){//controlla che i vector appena riempiti abbiano la stessa dimensione, in caso negativo ritorna errore
     cerr << "errore nella lettura dei dati: ad ogni tensione non corrisponde una corrente" << endl;
     return 1;
   }
   //se i vector hanno la stessa dimensione il programma continua, altrimenti termina.

   R0 = Resistenza(Tensione, Corrente);//uso della funzione R0. 

   ifstream file("resistenza_highV.dat");//stream del file omonimo

   if (! file.good()){//controllo lettura del file
     cerr << "errore nella lettura del file 'resistenza_highV.dat'" << endl;
     return 1;
   }

   TGraphErrors graph;//dichiarazione di un oggetto della classe TGraphErrors.h, per la creazione di grafici con errori sulle x e sulle y.
   
   double V_h, I_h, eI_h, eV_h;//dichiarazione di variabili di tensione e corrente per il file di input (_highV)
   int i=0; //contatore

   while (file >> I_h >> V_h >> eI_h >> eV_h){//stream del file 
     double T = Temperatura(R0, V_h, I_h); //calcolo della temperatura per mezzo della funzione sopra implementata
     double P = V_h*I_h;//calcolo della potenza P=V*I
     double eP = abs(I_h)*eV_h + abs(V_h)*eI_h;//calcolo dell'errore assoluto su P. eP = |I|*eV + |V|*eI

     graph.SetPoint(i, T, P);//assegnazione dei valori di T e P agli assi x e y
     graph.SetPointError(i, 1, eP);//assegnazione dell'incertezze assolute associate a T e P agli assi
     i++;
   }

   graph.GetXaxis()->SetTitle("Temperatura (K)");//Assegnazione del nome all'asse x
   graph.GetYaxis()->SetTitle("Potenza (W)");//assegnazione del nome all'asse y
   graph.SetMarkerStyle(8);//assegnazione dello stile dei punti del grafico
   graph.Draw("ap");//metodo che disegna il grafico per punti e assi

   TF1 f("f", "[0]*(pow(x, [1]) - pow(293, [1]))");//dihiarazione di un oggetto della classe TF1 (f) e della funzione di fit
   f.SetParameter(0, 0.5*5.67e-8);//inizializzazione del parametro 0
   f.SetParameter(1, 4);//inizializzazione del parametro 1

   graph.Fit("f");//tracciamento del fit

   //chiamata dei valori del fit tramite i  metodi della classe TF1
   double p0 = f.GetParameter(0);
   double e_p0 = f.GetParError(0);
   double p1 = f.GetParameter(1);
   double e_p1 = f.GetParError(1);
   double NDF = f.GetNDF();
   double Chi2 = f.GetChisquare();
   double prob_Chi2 = f.GetProb();

   int opzione;

   cout << endl;
   cout << "====================" << endl;
   cout <<"Digitare 1 se si vuole che i valori del fit siano stampati su schermo, altrimenti digitare 0: " << flush;
   cin >> opzione;

   if(opzione == 1){//stampa su schermo dei valori del fit
     cout << endl;
     cout << "a = " << p0 << " +/- " << e_p0 <<endl;
     cout << "n = " << p1 << " +/- " << e_p1 << endl;
     cout << "Chi^2 = " << Chi2 << endl;
     cout << "probabilità del Chi^2 = " << prob_Chi2 << endl;
     cout << "NDF = " << NDF << endl;
   }


   else if(opzione == 0){//stampa dei valori del fit su un file di output inserito da tastiera 

       string Nome_File;
       cout << "inserire il nome del file di output: " << flush;
       cin >> Nome_File;

       ofstream ofile(Nome_File);//apertura del file di output
       ofile << "a = " << p0 << " +/- " << e_p0 <<endl;
       ofile << "n = " << p1 << " +/- " << e_p1 << endl;
       ofile << "Chi^2 = " << Chi2 << endl;
       ofile << "probabilità del Chi^2 = " << prob_Chi2 << endl;
       ofile << "NDF = " << NDF << endl;

       ofile.close();// chiusura del file di output
     }

   else {//restituisce errore se sul terminale è stata digitato un numero diverso da quelli richiesti.
     cerr << "numero inserito non valido: digitare 1 o 0" << endl;
     return 1;
   }
   
   
   /* ATTENZIONE: l'istruzione che segue serve per far funzionare i grafici
    *             di ROOT e deve essere l'ultima istruzione del programma.
    *             Non aggiungete codice dopo questa istruzione
    */
   app.Run();
   return 0;
}
