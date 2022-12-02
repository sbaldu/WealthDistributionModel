import numpy as np
import matplotlib.pyplot as plt
import network
import ROOT
from ROOT import gStyle
from ROOT import gPad
# import matplotlib
from tqdm import tqdm

# matplotlib.use("pgf")
# matplotlib.rcParams.update({
#     "pgf.texsystem": "pdflatex",
#     'font.family': 'serif',
#     'text.usetex': True,
#     'pgf.rcfonts': False,
# })

# gStyle.SetOptFit(1111)

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


# net = network.network(5,100,100)
# n = 1*10**6
# net.createLinks(4)
# for i in tqdm(range(n)):
#     net.evolvePrefAtt()
#     if i % 5*10**4 == 0:
#         net.flatTax(1)
# x = data(net.playersMoney())[0][1::].tolist()
# y = data(net.playersMoney())[1][1::].tolist()
# y = [i/sum(y) for i in y] # normalization

# h = ROOT.TH1F("h", "Unfair Game", int(len(x)/2), 0, max(x))
# for i in range(len(x)):
#     h.Fill(x[i], y[i])

# f = ROOT.TF1("f", "[0]*x^[1]", min(x), max(x))
# h.Fit("f", "R")

# plt.plot(x, y ,'bo')
# fitX = np.arange(min(x), max(x), 0.1)
# fitY = f.GetParameter(0)*(fitX**f.GetParameter(1))
# plt.plot(fitX, fitY, color="red")

# plt.yscale("log")
# plt.xscale("log")
# plt.savefig("prova.pgf")

# canv = ROOT.TCanvas("canv", "canv", 800, 600)
# canv.SetLogy()
# canv.SetLogx()

# h.Draw()

# net = network.network(5,50,50)
# n = 10**6
# for i in tqdm(range(n)):
#     net.evolvePrefAttNoTax()
# x = data(net.playersMoney())[0][1::].tolist()
# y = data(net.playersMoney())[1][1::].tolist()
# y = [i/sum(y) for i in y] # normalization

# h = ROOT.TH1F("h", "Unfair Game", len(x), 0, max(x))
# for i in range(len(x)):
#     h.Fill(x[i], y[i])

# f = ROOT.TF1("f", "[0]*x^[1]", min(x), max(x))
# h.Fit("f", "R")

# plt.plot(x, y ,'bo')
# fitX = np.arange(min(x), max(x), 0.1)
# fitY = f.GetParameter(0)*(fitX**f.GetParameter(1))
# plt.plot(fitX, fitY, color="red")

# plt.yscale("log")
# plt.xscale("log")
# plt.title("10% flat tax every 1500 iterations")
# plt.savefig("prova.pgf")

# net = network.network(1,100,100)
# n = 10**6
# for i in range(n):
#     net.evolvePrefAtt()
#     if i % 1000 == 0:
#         net.flatTax(10)
# plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')
# plt.yscale("log")
# plt.xscale("log")
# plt.title("10% flat tax every 1000 iterations")
# # plt.savefig("./plots/1000-10.png")
# plt.show()

# net = network.network(1,100,100)
# for i in range(n):
#     net.evolvePrefAtt()
#     if i % 2000 == 0:
#         net.flatTax(10)
# plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')
# plt.yscale("log")
# plt.xscale("log")
# plt.title("10% flat tax every 2000 iterations")
# # plt.savefig("./plots/2000-10.png")
# plt.show()

# net = network.network(1,100,100)
# for i in range(n):
#     net.evolvePrefAtt()
#     if i % 500 == 0:
#         net.flatTax(10)
# plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')
# plt.yscale("log")
# plt.xscale("log")
# plt.title("10% flat tax every 500 iterations")
# # plt.savefig("./plots/500-10.png")
# plt.show()

# ####################################################################################################
# # UNFAIR GAME WITHOUT REDISTRIBUTION THROUGH FLAT TAX
# ####################################################################################################

# net = network.network(5,50,50)
# n = 1*10**7
# for i in range(n):
#     net.evolvePrefAttNoTax()
# x = data(net.playersMoney())[0][1::].tolist()
# y = data(net.playersMoney())[1][1::].tolist()
# y = [i/sum(y) for i in y] # normalization

# h = ROOT.TH1F("h", "Unfair Game", len(x), 0, max(x))
# # h = ROOT.TH1F("h", "Unfair Game", len(x), 0, 9)
# for i in range(len(x)):
#     h.Fill(x[i], y[i])

# f = ROOT.TF1("f", "[0]*x^[1]", min(x), max(x))
# h.Fit("f", "R")

# plt.plot(x, y ,'bo')
# fitX = np.arange(min(x), max(x), 0.1)
# fitY = f.GetParameter(0)*(fitX**f.GetParameter(1))
# plt.plot(fitX, fitY, color="red")

# plt.yscale("log")
# plt.xscale("log")
# plt.savefig("prova.pgf")

# canv = ROOT.TCanvas("canv", "canv", 800, 600)
# canv.SetLogy()
# canv.SetLogx()

# h.Draw()

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

net = network.network(1,40,40)
adjacency = net.getAdjacency()
net.createLinks(9)

n = 10**4
for i in tqdm(range(n)):
    matrix_el = np.random.choice(list(net.getAdjacency().keys()))
    net.evolveFixed(matrix_el)
print(net.getPoors())

plt.hist(net.getPoors(),bins=50)
plt.show()
plt.hist(net.getPlayers())
plt.show()