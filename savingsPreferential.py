import newModel
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
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

net = newModel.newModel(5,10**5)
n = 1.2*10**6
for i in tqdm(range(int(n))):
    net.evolvePreferential()

min_ = 3
nBins = 100 
data = net.getPlayers()
data = [x for x in data if x >= min_]

h = ROOT.TH1F("h", "savings preferential", nBins, min_, max(data))
for x in data:
    h.Fill(x)

f = ROOT.TF1("f", "[0]*x^[1]", min_, max(data))
h.Fit("f", "R")
# print("ChiSquare/NDF = " + str(round(f.GetChisquare()/f.GetNDF(), 3)))
# print("p-value = " + str(round(f.GetProb(), 3)))

fitX = np.arange(min_, max(data), 1)
fitY = f.GetParameter(0)*(fitX**f.GetParameter(1))

fitY = [y/20000 for y in fitY]

plt.plot(fitX, fitY, color="red")

print("Contant: ", str(round(f.GetParameter(0), 3)))
print("Slope: ", str(round(f.GetParameter(1), 3)))

sns.distplot(net.getPlayers(), hist=False)
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Capital (a. currency)')
plt.ylabel('Frequency (a.u.)')
plt.ylim([10**(-6),10])
plt.savefig("./tex/img/savingPreferential.pgf")
