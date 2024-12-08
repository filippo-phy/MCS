from ROOT import *

fe=TF1("fe", "[0]*([3]*TMath::Gaus(x, [1],[2],1)+(1-[3])/[4]*exp(-x/[4]))",0, 40)
fe.SetParameter(1, 15)
fe.SetParameter(2, 1.0)
fe.SetParameter(4, 10)
fe.SetParameter(3, 0.5)
fe.FixParameter(0, 1)

tree = TTree();
tree.ReadFile("dati.dat", "x/D")
h=TH1D("h", "h", 80,0,40)
tree.UnbinnedFit("fe", "x")

tree.Draw("x>>h")
fe.SetParameter(0, h.GetEntries()*h.GetBinWidth(1))
fe.Draw("SAME")
gApplication.Run(True)

