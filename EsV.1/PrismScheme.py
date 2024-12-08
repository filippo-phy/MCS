from   ROOT import *
from   math import *
import numpy as np
import time 

#Parametri e misure
lambda1 = 579.1
lambda2 = 404.7
alpha   = pi/3
th0     = 1.5701
th1     = 2.6958
th2     = 2.7904
eth     = 0.0005

#Funzione 
def GetAB(th0,th1,th2):

    delta1=th1-th0
    delta2=th2-th0

    n1=sin((delta1+alpha)*0.5)/sin(0.5*alpha)
    n2=sin((delta2+alpha)*0.5)/sin(0.5*alpha)

    B=(n2-n1)*((lambda1**2)*(lambda2**2)/(lambda1**2-lambda2**2))
    A=n2-B/(lambda2**2)
    return A,B

#Main
# Assumendo errore gaussiano (eth/sqrt(3)) 
# a) calcolo dell'errore su A e su B tramite variazione della funzione
stat_eth=eth/sqrt(3)
eAB=np.array([])

'''
for i in range(0,2):
    eAB=np.append(eAB, sqrt((GetAB(th0+stat_eth,th1,th2)[i]-GetAB(th0,th1,th2)[i])**2+(GetAB(th0,th1+stat_eth,th2)[i]-GetAB(th0,th1,th2)[i])**2+(GetAB(th0,th1,th2+stat_eth)[i]-GetAB(th0,th1,th2)[i])**2))

    
eA=sqrt((GetAB(th0+stat_eth,th1,th2)[0]-GetAB(th0,th1,th2)[0])**2+(GetAB(th0,th1+stat_eth,th2)[0]-GetAB(th0,th1,th2)[0])**2+(GetAB(th0,th1,th2+stat_eth)[0]-GetAB(th0,th1,th2)[0])**2)

eB=sqrt((GetAB(th0+stat_eth,th1,th2)[1]-GetAB(th0,th1,th2)[1])**2+(GetAB(th0,th1+stat_eth,th2)[1]-GetAB(th0,th1,th2)[1])**2+(GetAB(th0,th1,th2+stat_eth)[1]-GetAB(th0,th1,th2)[1])**2)


print("Valori ricavati col metodo di variazione della funzione: ")
print("A = %6.3f +/- %6.5f"%(GetAB(th0,th1,th2)[0],eA))
print("B = %6.3f +/- %6.5f"%(GetAB(th0,th1,th2)[1],eB))
print(eAB)


#b) calcolo delle distribuzioni di A e B dell'errore su A, B e della loro correlazione

min=GetAB(th0-stat_eth,th1-stat_eth,th2-stat_eth)
max=GetAB(th0+stat_eth,th1+stat_eth,th2+stat_eth)
'''
rnd=TRandom3()
rnd.SetSeed(123456789)

'''
A=TH1D("A", "valore A", 100, 0, 0)
B=TH1D("B", "valore B", 100,0, 0)
AB=TH2D("AB" , "A vs B", 100, 0, 0, 100, 0, 0)

n=10000


for i in range(0,n):

    t0=rnd.Gaus(th0, stat_eth)
    t1=rnd.Gaus(th1, stat_eth)
    t2=rnd.Gaus(th2, stat_eth)

    A.Fill(GetAB(t0,t1,t2)[0])
    B.Fill(GetAB(t0,t1,t2)[1])
    AB.Fill(GetAB(t0,t1,t2)[0], GetAB(t0,t1,t2)[1])
    #AB.Fill(GetAB(t0,t1,t2)[0], n1)
print(" ")
print("Valori ricavati col metodo di Monte Carlo (Gauss): ")

print("A = %6.5f +/- %6.5f"%(A.GetMean(),A.GetStdDev()))
print("B = %6.5f +/- %6.5f"%(B.GetMean(),B.GetStdDev()))
print("R_xy = %6.5f"%(AB.GetCorrelationFactor()))
for i in range(1,3):
    for j in range(1,3):
        print(i, j)
        print(AB.GetCovariance(i,j))

c1=TCanvas()
A.Draw()
c2=TCanvas()
B.Draw()
c3=TCanvas()
AB.Draw()
gApplication.Run(True)
'''
n=10000
A2=TH1D("A2", "valore A", 100, 0, 0)
B2=TH1D("B2", "valore B", 100, 0, 0)
AB2=TH2D("AB2" , "A vs B", 100, 0, 0, 100, 0, 0)

for i in range(0,n):
    t0=(2*rnd.Rndm()*eth-eth)+th0
    t1=(2*rnd.Rndm()*eth-eth)+th1
    t2=(2*rnd.Rndm()*eth-eth)+th2

    A2.Fill(GetAB(t0,t1,t2)[0])
    B2.Fill(GetAB(t0,t1,t2)[1])
    AB2.Fill(GetAB(t0,t1,t2)[0], GetAB(t0,t1,t2)[1])

print(" ")
print("Valori ricavati col metodo di Monte Carlo (uniforme): ")

print("A = %6.5f +/- %6.5f"%(A2.GetMean(),A2.GetStdDev()))
print("B = %6.5f +/- %6.5f"%(B2.GetMean(),B2.GetStdDev()))
print("R_xy = %6.5f"%(AB2.GetCorrelationFactor()))

A_def=A2.GetMean()
B_def=B2.GetMean()

c4=TCanvas()
A2.Draw()
c5=TCanvas()
B2.Draw()
c6=TCanvas()
AB2.Draw()
gApplication.Run(True)




L1=TH1D("l1", "l1", 100, 0, 0)
L2=TH1D("l2", "l2", 100, 0, 0)
L3=TH1D("l3", "l3", 100, 0, 0)
L4=TH1D("l4", "l4", 100, 0, 0)

#L1234=TH4D("L1234" , "", 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0)


N2=10000
th1=
th2=
th3=
for i in range(0,n):
    t0=(2*rnd.Rndm()*eth-eth)+th0
    t1=(2*rnd.Rndm()*eth-eth)+th1
    t2=(2*rnd.Rndm()*eth-eth)+th2
    t3=(2*rnd.Rndm()*eth-eth)+th3
    t4=(2*rnd.Rndm()*eth-eth)+th4

    delta1=th1-th0
    delta2=th2-th0
    delta3=th3-th0
    delta4=th4-th0

    n1=sin((delta1+alpha)*0.5)/sin(0.5*alpha)
    n2=sin((delta2+alpha)*0.5)/sin(0.5*alpha)
    n3=sin((delta3+alpha)*0.5)/sin(0.5*alpha)
    n4=sin((delta4+alpha)*0.5)/sin(0.5*alpha)

    lambda1_inv=sqrt((n1-A_def)/B_def)
    lambda2_inv=sqrt((n2-A_def)/B_def)
    lambda3_inv=sqrt((n3-A_def)/B_def)
    lambda4_inv=sqrt((n4-A_def)/B_def)


    L1.Fill(lambda1_inv)
    L2.Fill(lambda2_inv)
    L3.Fill(lambda3_inv)
    L4.Fill(lambda4_inv)

    #L1234.Fill(lambda1_inv,lambda2_inv,lambda3_inv,lambda4_inv)

'''

for i in range(1,5):
    for j in range(1,5):
        print(i, j)
        print(L1234.GetCovariance(i,j))
'''

c7=TCanvas()
L1.Draw()
c8=TCanvas()
L2.Draw()
c9=TCanvas()
L3.Draw()
c10=TCanvas()
L4.Draw()
gApplication.Run(True)


'''



A=TH1D("A", "valore A", 100, 0, 0)
B=TH1D("B", "valore B", 100,0, 0)
AB=TH2D("AB" , "A vs B", 100, 0, 0, 100, 0, 0)

n=10000


for i in range(0,n):

    delta1=rnd.Gaus(th1-th0, 2*stat_eth)
    delta2=rnd.Gaus(th2-th0, 2+stat_eth)
    n1=sin((delta1+alpha)*0.5)/sin(0.5*alpha)
    n2=sin((delta1+alpha)*0.5)/sin(0.5*alpha)

    A.Fill(n1)
    B.Fill(n2)
    AB.Fill(n1, n2)
print(" ")
print("Valori ricavati col metodo di Monte Carlo (Gauss): ")

print("n1 = %6.5f +/- %6.5f"%(A.GetMean(),A.GetStdDev()))
print("n1 = %6.5f +/- %6.5f"%(B.GetMean(),B.GetStdDev()))
print("R_12 = %6.5f"%(AB.GetCorrelationFactor()))


c1=TCanvas()
A.Draw()
c2=TCanvas()
B.Draw()
c3=TCanvas()
AB.Draw()
gApplication.Run(True)
# Ripetere punto b) nel caso in cui invece si assuma distribuzione uniforme con larghezza +/-eth


  <--
N2=10000
ABn=TH3D("ABn" , "A vs B vs n", 100, 0, 0, 100, 0, 0, 100, 0, 0)

for i in range(0,N2):

    delta1=rnd.Gaus(th1-th0, 2*stat_eth)
    delta2=rnd.Gaus(th2-th0, 2+stat_eth)
    n1=sin((delta1+alpha)*0.5)/sin(0.5*alpha)
    n2=sin((delta1+alpha)*0.5)/sin(0.5*alpha)
    ABn.Fill(GetAB(t0,t1,t2)[0], GetAB(t0,t1,t2)[1], n1)

for i in range(1,4):
    for j in range(1,4):
        print(i, j)
        print(ABn.GetCovariance(i,j))

'''
    

    



