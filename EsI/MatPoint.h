#ifndef _MATPOINT
#define _MATPOINT
#endif
#include "Particle.h"
#include "Vector3.h"

class MatPoint: public Particle{

 public:
  using Particle::Particle;
 MatPoint(Particle p=Particle(), Vector3 R=Vector3(), Vector3 V=Vector3()):Particle(p), m_r(R), m_v(V){};
 MatPoint(double mass, double charge, Vector3 R, Vector3 V):Particle(mass, charge), m_r(R), m_v(V){};

  Vector3 R();
  void R(Vector3 R);
  Vector3 V();
  void V(Vector3 V);

  Vector3 GravField(Vector3);
  
 private:
  Vector3 m_r;
  Vector3 m_v;
};


