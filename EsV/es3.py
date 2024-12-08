from ROOT import *
import math as m

rnd=TRandom3()
rnd.SetSeed(123456789)

n=10000
R=1.0
nacc=0

for i in range(0,n):
    x=2*rnd.Rndm()-R
    y=2*rnd.Rndm()-R
    z=2*rnd.Rndm()-R

    r=m.sqrt(x*x+y*y+z*z)
    rcl=m.sqrt(x*x+y*y)

    if r<R and rcl>0.5*R:
        nacc=nacc+1

p=nacc/n
ep=m.sqrt(p*(1-p)/n)
V=p*(2*R)**3
V_sfera=4./3*m.pi*R**3

print("probabilità = %6.3f +/- %6.3f"%(p,ep))
print("volume = %6.3f +/- %6.3f"%(V,ep*V/p))
print("volume sfera = %6.3f +/-  %6.3f"%(V_sfera,ep*V_sfera/p))
