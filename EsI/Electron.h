#ifndef _ELECTRON
#define _ELECTRON
#endif
#ifndef _VECTOR3
#define _VECTOR3
#endif
#include "Particle.h"
class Electron: public Particle{

 public:
  using Particle::Particle;
 Electron():Particle(9.10E-31, -1.66E-19){};
};
