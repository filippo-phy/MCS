#include <iostream>
#include "LorentzVector.h"

int main(){

  //costruttore di default
  LorentzVector V;

  std::cout<<"Verifica costruttore di default: (" << V.T() << "," << V.X() << "," << V.Y() <<  "," << V.Z() << ")"<< std::endl;

  //costruttore tramite Vector3
  Vector3 v(1, 2, 1);
  LorentzVector A(1, v);

  std::cout<<"A = " << A << " [atteso: (1,1,2,1)]" <<std::endl;


  //operatori
  LorentzVector B(1, 3, 4);
  B.T(6);

  std::cout<<"B = " << B <<" [atteso: (6,3,4,0)]" << std::endl;
  
  LorentzVector C=A+B;

  std::cout<<"A+B = " << C <<" [atteso: (7,4,6,1)]" << std::endl;

  LorentzVector D=A-B;

  std::cout<<"A-B = " << D <<" [atteso: (-5,-2,-2,1)]" << std::endl;
  
  LorentzVector E=3*A;
  LorentzVector F=A*3;

  std::cout<<"3A = " << E <<"     " << "A*3 = " << F <<" [atteso: (3,3,6,3)]" <<std::endl;

  //norma invariante

  std::cout<<"||A|| = " << A.LorentzMod() <<" [atteso: -5]" << std::endl;
  
  //inserimento delle componenti da terminale
  LorentzVector W;
  std::cout<<"inserire le coordinate del quadrivettore W " <<std::endl;
  std::cin>>W;
  std::cout<<"W = " << W <<std::endl;
 
  return 0;
}
