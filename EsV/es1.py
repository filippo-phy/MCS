from ROOT import *
import math as m

rnd=TRandom3()
rnd.SetSeed(123456789)

h=TH1D("h", "tempi dec", 100,0,3)
hm=TH1D("hm", "tempi misurati", 100,0,3)

tau1=0.1
tau2=1.0
f=0.3
tau_acc=0.01

n=10000

#evento binomiale
for i in range(0,n):
    if rnd.Rndm() < f:
        tau=tau1
    else:
        tau=tau2

    t = -tau*m.log(1-rnd.Rndm())#visto a lezione
    h.Fill(t)

    if rnd.Rndm()<(1-m.exp(-t/tau_acc)):

        hm.Fill(t)

h.Draw()
hm.SetLineColor(kRed)
hm.Draw("SAME")
gApplication.Run(True)





    
