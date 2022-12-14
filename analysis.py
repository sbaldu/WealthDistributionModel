import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
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

df = pd.read_csv("./data/adult_cleaned.csv")
data = df['fnlwgt'].values.tolist()

nBins = 200
n, Bins, patches = plt.hist(data, bins=nBins, density=True)
plt.xlabel('Capital (US dollars)')
plt.ylabel('Frequency')
plt.savefig("./tex/img/global_real_distribution.pgf")
plt.yscale('log')
plt.savefig("./tex/img/real_head.pgf")
plt.clf()

min_ = 3
nBins = 100 
data_fit = [x for x in data if x >= min_]

h = ROOT.TH1F("h", "savings preferential", nBins, min_, max(data))
for x in data_fit:
    h.Fill(x)

f = ROOT.TF1("f", "[0]*x^[1]", min_, max(data))
h.Fit("f", "R")

fitX = np.arange(min_, max(data), 1)
fitY = f.GetParameter(0)*(fitX**f.GetParameter(1))

# fitY = [y/20000 for y in fitY]

plt.plot(fitX, fitY, color="red")

print("Contant: ", str(round(f.GetParameter(0), 3)))
print("Slope: ", str(round(f.GetParameter(1), 3)))

sns.distplot(data, hist=False)
plt.xlabel('Capital (US dollars)')
plt.ylabel('Frequency (a.u.)')
plt.yscale('log')
plt.xscale('log')
plt.savefig("./tex/img/real_tail.pgf")
