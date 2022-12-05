import matplotlib.pyplot as plt
import numpy as np
import network as n
from tqdm import tqdm
import ROOT
from ROOT import gStyle
from ROOT import gPad
import matplotlib

matplotlib.use("pgf")
matplotlib.rcParams.update({
    "pgf.texsystem": "pdflatex",
    'font.family': 'serif',
    'text.usetex': True,
    'pgf.rcfonts': False,
})

def data(vec):
    x = np.arange(0, max(vec)+1)
    y = np.zeros(max(vec)+1)
    for element in vec:
        y[element] += 1
    return x,y

net = n.network(5,50,50)
adjacency = net.getAdjacency()
net.createLinks(4)

n = 2*10**5
for i in tqdm(range(n)):
    matrix_el = np.random.choice(list(net.getAdjacency().keys()))
    net.evolveFixed(matrix_el)

x = data(net.getPlayers())[0][1::].tolist()
y = data(net.getPlayers())[1][1::].tolist()
y = [i/sum(y) for i in y] # normalization

h = ROOT.TH1F("h", "Fair Game", len(x), 0, 32)
for i in range(len(x)):
    h.Fill(x[i], y[i])

# fitting and extracting fit function
h.Fit("expo")
f = h.GetListOfFunctions().FindObject("expo")
print("ChiSquare/NDF = " + str(f.GetChisquare()/f.GetNDF()))
print("p-value = " + str(f.GetProb()))

plt.plot(x,y,'.',markersize=12)
fitX = np.arange(min(x), 32, 0.1)
fitY = np.exp(f.GetParameter("Constant")+f.GetParameter("Slope")*fitX)
plt.plot(fitX, fitY, color="red")
plt.yscale("log")
plt.xlabel('Wealth')
plt.ylabel('Distribution')
plt.xlim([0,35])
plt.savefig("./tex/img/fixedExpo.pgf")


poor_map = net.getPoors()
for poor in poor_map.keys():








