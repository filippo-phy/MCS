from   ROOT import *
import matplotlib.pyplot as plt
import numpy as np
import math
import random as ran

#Funzione per il calcolo delle derivate nel pto di match
def der(psi):
    return (psi[nmatch+1]-psi[nmatch-1])/(2*h)

#Funzione per il calcolo dell'integrale di |psi|^2 tramite metodo Monte Carlo
def IntegralDensity(psi, n):
    rnd = TRandom3() #generatore numeri casuali di Root
    rnd.SetSeed(123456789)
    ran.seed(123456789)
    N = 10000
    nacc = 0
    psi2 = np.absolute(psi)**2

    for i in range(0,N):
        x=ran.randint(1,14000)-7000 #generazione delle ascisse tra -7000 e 7000 (solo numeri interi)
        y=rnd.Rndm()*max(psi2) #generazione delle ordinate

        if y<psi2[x]:
            nacc=nacc+1

    return n*max(psi2)*nacc/float(N)
    
#Potenziale quadratico
def V(xi):
    return xi*xi

#Calcolo di b a partire dall'energia normalizzata eps, della coordinata normalizzata xi e dallo passo h (variabile globale)
def b(eps,xi):
    K = 2*eps-V(xi)
    return (h*h*K)/12.0

#Funzione Numerov che riempe i valori di psi(xi) dall'indice n1 all'indice n2 (entrambi compresi)
def numerov(n1,n2,eps):
    psi = np.array(xi)*0  
    j   = 1
    j = np.sign(n2-n1)
    psi[n1] = 0.0
    psi[n1+j] = 1.0e-4
    for i in range(n1+2*j, n2+j, j):
        psi[i] = ((2*psi[i-j]*(1-5*b(eps,xi[i-j])))-psi[i-2*j]*(1+b(eps, xi[i-2*j])))/(1+b(eps, xi[i]))

    return psi

#Funzione per valutare la continuità della derivata prima a destra e sinistra del punto di match
def evalDerivative(eps):
    global psir,psil
    psil = numerov(0,nmatch+1,eps)
    psir = numerov(n-1,nmatch-1,eps)
    psir = psir*(psil[nmatch]/psir[nmatch])
    diff = der(psil)-der(psir)
    
    return diff


#Metodo di bisezione per trovare l'energia in cui la funzione evalDerivative e' nulla. Cioe' l'enegia per cui  la derivata sinistra e destra coincidono 
def findE(emin,emax,tol):
    if evalDerivative(emin)*evalDerivative(emax)>0:
          print("L'intervallo per la ricerca di zeri non è valido")
    while (emax-emin>tol):
        emed = (emin+emax)/2
        if evalDerivative(emin)*evalDerivative(emed)<0:
            emax = emed
        else:
            emin = emed
    return (emin+emax)/2;
 
''' 
  Codice principale: l'esecuzione dello script parte da qui
'''
n           = 14000
nmatch      = 10500
xi          = np.linspace(-7.,7,n)
h           = xi[1]-xi[0]
eps_min     = 0
eps_max     = 6
tol         = 0.0001
eps_change  = eps_min+0.1

Intervall   = np.array([])
Intervall   = np.append(Intervall, eps_min)
State       = np.array([])

#Adopero un ciclo while per scorrere l'intervallo di energie da 0 a eps_max, salvando gli intervalli in cui la funzione evalDerivative si annulla
while eps_change<eps_max:
  
    if evalDerivative(eps_min)*evalDerivative(eps_change)<0:
        e = findE(eps_min, eps_change, tol)
        Intervall=np.append(Intervall, eps_change)
        State=np.append(State, e)
        eps_min=eps_change

    eps_change=eps_change+0.1

print("*****************************************")
print("Energie corrispondenti a uno stato fisico nell'intervallo [0, %2.0f]: "%(2*eps_max))
print(State*2)
print("*****************************************")

#stampo le soluzioni dell'eqz d'onda a energie fissate
for i in range(0, np.size(State)):
    j=i+1
    psil = numerov(0,nmatch+1,State[i])
    psir = numerov(n-1,nmatch-1,State[i])
    psir = psir*(psil[nmatch]/psir[nmatch])
    psi = psil+psir
    psi[nmatch] = psi[nmatch]-psir[nmatch]
    psi[nmatch+1] = psi[nmatch+1]-psir[nmatch+1]
    psi[nmatch-1] = psi[nmatch-1]-psir[nmatch-1] 

    I=math.sqrt(IntegralDensity(psi, n))

    plt.subplot(2,3,j)
    plt.plot(xi, psi/I)
    plt.title("Psi normalizzata, n=%1.0f"%(i))
    plt.xlabel("Xi")
    plt.ylabel("Psi")

plt.tight_layout()                  
plt.show()


    
