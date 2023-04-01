import numpy as np
import matplotlib.pyplot as plt
import network
from tqdm import tqdm
from scipy.optimize import curve_fit

def power(x, A, a):
    return A*pow(x, -a)

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
x = data(net.players())[0][1::]
y = data(net.players())[1][1::]
y = y/sum(y)
nBins = int(len(x)/4)

# "Binned" scatter plot 
n, bins, patches = plt.hist(x, weights=y, bins=nBins, range=(1, max(x)), alpha=0.)
x = bins[:-1] + 0.5*(bins[1:] - bins[:-1])
y = n

# fitting and extracting fit function
parameters, covariance = curve_fit(power, x, y)
fit_A = parameters[0]
fit_a = parameters[1]
std_A = np.sqrt(covariance[0][0])
std_a = np.sqrt(covariance[1][1])

plt.plot(x, y, '.', markersize=12, color='C0')
fitY = [power(x_val, fit_A, fit_a) for x_val in x]
plt.plot(x, fitY, 'red')
plt.yscale("log")
plt.xscale("log")
plt.xlim([2,200])
plt.xlabel('Capital (a. currency)')
plt.ylabel('Frequency (a.u.)')
plt.legend(['Simulated data','Fit line'], fontsize=12)
plt.grid(linestyle='--', linewidth=0.2)
print(f"Contant: {fit_A} +- {std_A}")
print(f"Slope: {fit_a} +- {std_a}")
plt.show()
