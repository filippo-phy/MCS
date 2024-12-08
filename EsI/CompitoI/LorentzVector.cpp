#include "LorentzVector.h"

double LorentzVector::T(){//getter di m_t
  return m_t;
}

void LorentzVector::T(double t){//setter di m_t
  m_t=t;
}

//Implementazione metodi:
//somma
LorentzVector LorentzVector::operator+(LorentzVector vec){
  LorentzVector sum(m_t+vec.T(), vec.X()+(*this).X(), vec.Y()+(*this).Y(), vec.Z()+(*this).Z());
  return sum;
}

//meno unario
LorentzVector LorentzVector::operator-(){
  LorentzVector res(-m_t, -(*this).X(), -(*this).Y(), -(*this).Z());
  return res;
}

//meno binario
LorentzVector LorentzVector::operator-(LorentzVector v){
  return (*this)+(-v);
}

//prodotto per scalare
LorentzVector LorentzVector::operator*(double alpha){
  LorentzVector res(m_t*alpha, alpha*(*this).X(), alpha*(*this).Y(), alpha*(*this).Z());
  return res;
}

LorentzVector operator*(double alpha, LorentzVector v){
  return v*alpha;
}

//prodotto scalare
double LorentzVector::operator*(LorentzVector v){
  double res = ((*this).T())*v.T()-(*this).Vector3::operator*(v);
  return res;
}  

//modulo invariante
double LorentzVector::LorentzMod(){
  double mod=(*this)*(*this);
  return mod;
}

//scrittura/lettura tramite terminale
std::ostream& operator<<(std::ostream& output, LorentzVector v){
  output << "(" << v.T() << "," << v.X() << "," << v.Y() << "," << v.Z() << ")";
  return output;
}

std::istream& operator>>(std::istream& input, LorentzVector& v){
  double t,x,y,z;
  input >> t >> x >> y >> z;
  v.T(t); v.X(x); v.Y(y); v.Z(z);
  return input;
}




  
  
  

  
