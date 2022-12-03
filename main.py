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

# net = network.network(5,100,100)
# n = 10**6
# for i in tqdm(range(n)):
#     net.evolveUniform()

# x = data(net.playersMoney())[0][1::].tolist()
# y = data(net.playersMoney())[1][1::].tolist()
# y = [i/sum(y) for i in y] # normalization

# h = ROOT.TH1F("h", "Fair Game", len(x), 0, max(x))
# for i in range(len(x)):
#     h.Fill(x[i], y[i])

# # fitting and extracting fit function
# h.Fit("expo")
# f = h.GetListOfFunctions().FindObject("expo")

# plt.plot(x, y ,'bo')
# fitX = np.arange(min(x), max(x), 0.1)
# fitY = np.exp(f.GetParameter("Constant")+f.GetParameter("Slope")*fitX)
# plt.plot(fitX, fitY, color="red")
# plt.yscale("log")
# # plt.show()
# plt.savefig("./tex/img/expo.pgf")

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
print("ChiSquare/NDF = " + str(f.GetChisquare()/f.GetNDF()))
print("p-value = " + str(f.GetProb()))

# plt.plot(x, y ,'bo')
plt.hist(x, weights=y, bins=nBins, range=(1, max(x)))
fitX = np.arange(min(x), max(x), 0.1)
fitY = f.GetParameter(0)*(fitX**f.GetParameter(1))
plt.plot(fitX, fitY, color="red")

plt.yscale("log")
plt.xscale("log")
plt.savefig("./tex/img/pow.pgf")

###################################################################################
### MODEL WITH SAVINGS
###################################################################################
# net = network.network(50,100,100)
# n = 15*10**4
# for i in tqdm(range(n)):
#     net.evolveSavings()

# x = data(net.playersMoney())[0][1::].tolist()
# fitX = np.arange(min(x), max(x), 0.1)
# y = data(net.playersMoney())[1][1::].tolist()
# y = [i/sum(y) for i in y] # normalization

# h = ROOT.TH1F("h", "Fair Game", len(x), min(x), max(x))
# for i in range(len(x)):
#     h.Fill(x[i], y[i])

# # fitting and extracting fit function
# h.Fit("expo")

# f = h.GetListOfFunctions().FindObject("expo")
# fitY = np.exp(f.GetParameter("Constant")+f.GetParameter("Slope")*fitX)

# g = ROOT.TF1("g", "[0]*x^[1]", 40, max(x))
# h.Fit("g", "R")

# # plt.plot(x, y ,'bo')
# plt.hist(net.getPlayers(), density=True)
# plt.plot(fitX, fitY, color="red")
# fitX = np.arange(40, max(x), 0.1)
# fitY = g.GetParameter(0)*(fitX**g.GetParameter(1))
# plt.plot(fitX, fitY, color="green")
# plt.yscale("log")
# # plt.xscale("log")
# plt.show()

###################################################################################
### MODEL WITH FIXED NETWORK
###################################################################################

# net = network.network(1,40,40)
# adjacency = net.getAdjacency()
# net.createLinks(9)

# n = 10**4
# for i in tqdm(range(n)):
#     matrix_el = np.random.choice(list(net.getAdjacency().keys()))
#     net.evolveFixed(matrix_el)
# print(net.getPoors())

# plt.hist(net.getPoors(),bins=50)
# plt.show()
# plt.hist(net.getPlayers())
# plt.show()

# canv = ROOT.TCanvas("canv", "canv", 800, 600)
# canv.SetLogy()
# canv.SetLogx()

# h.Draw()