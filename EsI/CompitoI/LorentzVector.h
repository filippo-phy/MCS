#ifndef _LORENTZVECTOR
#define _LORENTZVECTOR
#endif
#include "Vector3.h"

class LorentzVector: public Vector3{
 public:
  using Vector3::Vector3;
  LorentzVector(double tempo, Vector3 v):Vector3(v), m_t(tempo){};//costruttore
  LorentzVector(double tempo=0, double x=0, double y=0, double z=0): Vector3(x, y, z), m_t(tempo){};//costruttore di default

  double T(); //getter per variabile tempo
  void T(double); //setter per variabile tempo

  double LorentzMod(); //Modulo invariante
  
  //definizione operazioni base tra quadrivettori
  LorentzVector operator+(LorentzVector v);
  LorentzVector operator-();// - unario
  LorentzVector operator-(LorentzVector v);// - binario
  LorentzVector operator*(double alpha); //prodotto per scalare
  double operator*(LorentzVector v);//prodotto scalare 
 
 private:
  double m_t;//variabile privata per il tempo
};

LorentzVector operator*(double alpha, LorentzVector v);//scalare per quadrivettore

//stampa e riempimento di quadrivettori tramite terminale
std::ostream& operator<<(std::ostream& output, LorentzVector v);
std::istream& operator>>(std::istream& input, LorentzVector& v);
  
