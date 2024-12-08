import numpy as np
from ROOT import *
import matplotlib as mpl
#creo vett vuoti
x=np.array([])
y=np.array([])
ex=np.array([])
ey=np.array([])

file = open("pendolo.dat", "r")
for line in file:
    str=line.split() #divide la linea letta secondo il separatore di default (spazio)
    if len(str)>0:
        x=np.append(x, float(str[0]))#primo valore della prima colonna
        y=np.append(y, float(str[1]))
        ex=np.append(ex, float(str[2]))
        ey=np.append(ey, float(str[3]))

gr = TGraphErrors(len(x),x,y,ex,ey)
gr.Draw("AP")
gApplication.Run()

        