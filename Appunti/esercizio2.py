import ROOT
import math

#c1.Divide(2,1)
#c1.Draw()

c1=ROOT.TCanvas()
#c1.Divide(2,1)
c1.Draw()
#c1.cd(1)
fun1=ROOT.TF1('f', 'sin(x)/x', -10*math.pi, 10*math.pi)
fun1.Draw()

c2=ROOT.TCanvas()
c2.Draw()
fun2=ROOT.TF1('g', 'TMath::Gaus(x,0,1)', -3, 3)
fun2.Draw()

ROOT.gApplication.Run()

"""
import matpointlib.pyplot as plt
import numpy as np
import math as m
import scipy.stats as sc

fig, (ax1, ax2)=plt subplots(1, 2) # 1 riga e 2 colonne

x = np.linspace(-10*m.pi, 10*m.pi, 100)
y=np.sin(x)/x

x2=np.linspace(-3, 3, 100)
y2=sc.norm(0,1).pdf(x2)
fig.set_size_inches

ax1.set_title("Plot 1")
ax1.set_label("asse x")
ax1.plot(x,y)

ax2.set_title("Plot 1")
ax2.set_label("asse x")
ax2.plot(x,y)

plt.show()
"""




