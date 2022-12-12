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

nBins = 200

min_head = 2*10**5
max_head = 6*10**5
data = [x for x in data if x >= min_head and x <= max_head]
n,bins,patches = plt.hist(data, range=(min_head,max_head))

h2 = ROOT.TH1F("h2", "Fair Game", nBins, min_head, max_head)
for i in range(len(data)):
    h2.Fill(data[i])

# # fitting and extracting fit function
h2.Fit("expo")
f = h2.GetListOfFunctions().FindObject("expo")
print("ChiSquare/NDF = " + str(round(f.GetChisquare()/f.GetNDF(), 3)))
print("p-value = " + str(round(f.GetProb(), 3)))

fitX = np.arange(min_head, max_head, 0.1)
fitY = np.exp(f.GetParameter("Constant")+f.GetParameter("Slope")*fitX)

# For rinormalization reasons we shift the fit line upward
shift = np.log(n[0]) - np.log(fitY[0]) 
shift_ampl = np.exp(shift)
fitY = [shift_ampl*y for y in fitY]

plt.plot(fitX, fitY, color="red")
plt.yscale("log")
plt.xlabel('Capital (US dollars)')
plt.ylabel('Frequency')
plt.savefig("./tex/img/realData_head.pgf")
print("Contant: ", str(round(np.exp(f.GetParameter("Constant")), 3)))
print("Slope: ", str(round(f.GetParameter("Slope"), 3)))
