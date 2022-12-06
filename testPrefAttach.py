import numpy as np
import matplotlib.pyplot as plt
import network
import ROOT
from ROOT import gStyle
from ROOT import gPad
import matplotlib
from tqdm import tqdm

matplotlib.use("pgf")
matplotlib.rcParams.update({
    "pgf.texsystem": "pdflatex",
    'font.family': 'serif',
    'text.usetex': True,
    'pgf.rcfonts': False,
})

gStyle.SetOptFit(1111)

def data(vec):
    x = np.arange(0, max(vec)+1)
    y = np.zeros(max(vec)+1)
    for element in vec:
        y[element] += 1
    return x,y

####################################################################################################
# UNFAIR GAME
####################################################################################################

net = network.network(5,100,100)
n = 40*10**5
net.createLinks(4)
for i in tqdm(range(n)):
    net.evolvePrefAtt()
x = data(net.playersMoney())[0][1::].tolist()
y = data(net.playersMoney())[1][1::].tolist()
y = [i/sum(y) for i in y] # normalization
nBins = int(len(x)/4)

h = ROOT.TH1F("h", "Unfair Game", nBins, 0, max(x))
for i in range(len(x)):
    h.Fill(x[i], y[i])

f = ROOT.TF1("f", "[0]*x^[1]", min(x), max(x))
h.Fit("f", "R")
print("ChiSquare/NDF = " + str(round(f.GetChisquare()/f.GetNDF(), 3)))
print("p-value = " + str(round(f.GetProb(), 3)))

# plt.plot(x, y ,'bo')
plt.hist(x, weights=y, bins=nBins, range=(1, max(x)))
fitX = np.arange(min(x), max(x), 0.1)
fitY = f.GetParameter(0)*(fitX**f.GetParameter(1))
plt.plot(fitX, fitY, color="red")

plt.yscale("log")
plt.xscale("log")
plt.xlabel('Wealth')
plt.ylabel('Distribution')
plt.savefig("./tex/img/pow.pgf")
print("Contant: ", str(round(f.GetParameter(0), 3)))
print("Slope: ", str(round(f.GetParameter(1), 3)))