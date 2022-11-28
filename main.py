import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import network
import ROOT
from ROOT import gStyle
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

####################################################################################################
# FAIR GAME
####################################################################################################

net = network.network(5,100,100)
n = 10**6
for i in range(n):
    net.evolveUniform()

x = data(net.playersMoney())[0][1::].tolist()
y = data(net.playersMoney())[1][1::].tolist()
y = [i/sum(y) for i in y] # normalization

gStyle.SetOptFit(1111)

h = ROOT.TH1F("h", "10^6 iterations", 60, 0, 60)
for i in range(len(x)):
    h.Fill(x[i], y[i])

# fitting and extracting fit function
h.Fit("expo")
f = h.GetListOfFunctions().FindObject("expo")

plt.plot(x, y ,'bo')
fitX = np.arange(min(x), max(x), 0.1)
fitY = np.exp(f.GetParameter("Constant")+f.GetParameter("Slope")*fitX)
plt.plot(fitX, fitY, color="red")
plt.yscale("log")
plt.title("One million iterations")
plt.savefig("prova.pgf")

# canv = ROOT.TCanvas("canv", "canv", 800, 600)
# canv.SetLogy()

# h.Draw()



# net = network.network(5,100,100)
# n = 10**5
# for i in range(n):
#     net.evolveUniform()
# plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')
# plt.yscale("log")
# plt.title("10^5 iterations")
# # plt.savefig("./plots/105.png")
# plt.show()
# # plt.clear()

# net = network.network(5,100,100)
# n = 10**7
# for i in range(n):
#     net.evolveUniform()
# plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')
# plt.yscale("log")
# plt.title("10^7 iterations")
# # plt.savefig("./plots/107.png")
# plt.show()
# # plt.clear()

####################################################################################################
# UNFAIR GAME
####################################################################################################

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
#     if i % 1500 == 0:
#         net.flatTax(10)
# x = data(net.playersMoney())[0][1::]
# y = data(net.playersMoney())[1][1::]
# plt.plot(x,[2000/x_**2 for x_ in x])
# plt.yscale("log")
# plt.xscale("log")
# plt.title("10% flat tax every 1500 iterations")
# # plt.savefig("./plots/1500-10.png")
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

# net = network.network(1,100,100)
# for i in range(n):
#     net.evolvePrefAttNoTax()
#     if i % 1500:
#         net.flatTax(10)
# plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')
# plt.yscale("log")
# plt.xscale("log")
# plt.show()
