/*ODE e calcolo numerico (vedi slide)

§DERIVATE: si possono calcolare sfruttando serie di Taylor troncate al prim'ordine (definizione di rapporto incrementale, o(n))
           se vado al terz'ordine ed espando f(h+x), f(h-x) e le sottraggo ottengo che f'(x)=(f(x+h)-f(x-h))/2h (differenza centrale, o(n2)).

           E h?, dev'essere più piccola possibile: il minimo che posso scegliere è eps=10^-16, ma le variabili hanno rappresentazione finita, 
           quindi al diminuire di h l'errore di rappresantazione aumenta:
                                                                                E_calc=eps*f/h
                                                                           
           però troncando la serie ad un certo ordine commetto un altro errore:
                                                                                   E_tay=(f'''(x)*h^2)/6
     
           È ragionevole sceglire h in modo tale da avere che i due contributi siano uguali:
                                                                                                 h^3=6eps


           Per la derivata seconda espando in serie di taylor all'ordine 4 e ottengo che f''(x)=(f(x+h)+f(x-h))/h^2 (o(n2))


§INTEGRALI: somme superiori e inferiori (errore o(w), w larghezza rettangoli)
            metodo dei trapezi, occhio all'implementazione (ricalcolo della funzione) (errore o(w2))
            metodo di simpson, usando una parabola (o(w5))
            in generale si fissa la precisione e si adatta il numero di bin, confrontando il risultato di integrazioni successivi: eps=|I_1-I_2|*/

#include <iostream>
#include <cmath>

double fun(double x){//funzione da integrare
  return pow(x, 3);
}

double integN(double f(double), double a, double b, double n){//trapezi
  double w=(b-a)/n; //larghezza intervallo
  double val=(f(a)+f(b))*w/2;
  for(int i=1; i<n; i++){
    double x=a+w*i;
    val += w*f(x);
  }

  return val;
}

double integPrec(double f(double), double a, double b, double prec){
  int n=2;
  double val0;
  double val1=integN(fun, a, b, n);
  do{
    val0=val1;
    val1=integN(fun, a, b, 2*n);
    n=n*2;
  }while(fabs(val0-val1)>prec);
  
  return val1;
}

int main(){
  std::cout<<integN(fun, 0, 1, 100)<<std::endl;
  std::cout<<integPrec(fun, 0, 1, 0.001)<<std::endl;
  
  return 0;
}


/*
§RICERCA DI ZERI: teorema degli zeri, metodo di bisezione (vedi foto)

§RICERCA DI MAX/MIN: derivate, oppure metodi iterativi
                     algoritmo golden search (funzioni continue)
