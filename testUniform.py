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
# FAIR GAME
####################################################################################################

net = network.network(5,100,100)
n = 10**6
for i in tqdm(range(n)):
    net.evolveUniform()

x = data(net.playersMoney())[0][1::].tolist()
y = data(net.playersMoney())[1][1::].tolist()
y = [i/sum(y) for i in y] # normalization

h = ROOT.TH1F("h", "Fair Game", len(x), 0, max(x))
for i in range(len(x)):
    h.Fill(x[i], y[i])

# fitting and extracting fit function
h.Fit("expo")
f = h.GetListOfFunctions().FindObject("expo")
print("ChiSquare/NDF = " + str(round(f.GetChisquare()/f.GetNDF(), 3)))
print("p-value = " + str(round(f.GetProb(), 3)))

plt.plot(x,y,'.',markersize=12)
fitX = np.arange(min(x), max(x), 0.1)
fitY = np.exp(f.GetParameter("Constant")+f.GetParameter("Slope")*fitX)
plt.plot(fitX, fitY, color="red")
plt.yscale("log")
plt.xlabel('Capital (a. currency)')
plt.ylabel('Frequency (a.u.)')
plt.legend(['Simulated data','Fit line'], fontsize=12)
plt.savefig("./tex/img/expo.pgf")
print("Contant: ", str(round(np.exp(f.GetParameter("Constant")), 3)))
print("Slope: ", str(round(f.GetParameter("Slope"), 3)))
