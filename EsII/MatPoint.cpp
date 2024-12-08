#include <cmath>
#include "MatPoint.h"

Vector3 MatPoint::R(){
  return m_r;
}
Vector3 MatPoint::V(){
  return m_v;
}
  
void MatPoint::R(Vector3 R){
  m_r=R;
}
void MatPoint::V(Vector3 V){
  m_v=V;
}

Vector3 MatPoint::GravField(Vector3 P){
  double mass=(*this).Mass();
  Vector3 R=(*this).R();
  double dist=(R-P).Mod();
  Vector3 ver=(P-R).Unit();
  Vector3 g=-(mass/pow(dist, 2))*ver;
 
  return g;

}
