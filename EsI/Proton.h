#ifndef _PROTON
#define _PROTON
#endif
#ifndef _VECTOR3
#define _VECTOR3
#endif
#include "Particle.h"
class Proton: public Particle{

 public:
  using Particle::Particle;
 Proton():Particle(1.67E-27, 1.66E-19){};
};
  
