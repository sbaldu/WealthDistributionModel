import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
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

gStyle.SetOptFit(1111)

df = pd.read_csv("./data/adult_cleaned.csv")
data = df['fnlwgt'].values.tolist()

nBins = 500

min_tail = 3*10**5
max_tail = max(data)
h1 = ROOT.TH1F("h1", "Tail", nBins, min_tail, max_tail)
for i in range(len(data)):
    if data[i] >= min_tail and data[i] <= max_tail:
        h1.Fill(data[i])

f = ROOT.TF1("f", "[0]*x^[1]", min_tail, max_tail)
h1.Fit("f", "R")
print("ChiSquare/NDF = " + str(round(f.GetChisquare()/f.GetNDF(), 3)))
print("p-value = " + str(round(f.GetProb(), 3)))

fitX = np.arange(min_tail, max_tail, 1000)
fitY = f.GetParameter(0)*(fitX**f.GetParameter(1))
plt.plot(fitX, fitY, color="red")
plt.hist(data, range=(min_tail,max_tail))

plt.yscale("log")
plt.xscale("log")
# plt.xlim([2,200])
plt.xlabel('Capital (US dollars)')
plt.ylabel('Frequency (a.u.)')
plt.savefig("./tex/img/realData_tail.pgf")
print("Contant: ", str(round(f.GetParameter(0), 3)))
print("Slope: ", str(round(f.GetParameter(1), 3)))
