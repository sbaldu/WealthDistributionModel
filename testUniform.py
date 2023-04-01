import numpy as np
import matplotlib.pyplot as plt
import network
from tqdm import tqdm
from scipy.optimize import curve_fit

def exponential(x, A, a):
    return A*np.exp(-a*x)

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

x = data(net.playersMoney())[0][1::]
y = data(net.playersMoney())[1][1::]
y = y/sum(y)

# fitting and extracting fit function
parameters, covariance = curve_fit(exponential, x, y)
fit_A = parameters[0]
fit_a = parameters[1]
std_A = np.sqrt(covariance[0][0])
std_a = np.sqrt(covariance[1][1])

fitY = [exponential(x_val, fit_A, fit_a) for x_val in x]
plt.plot(x, fitY, 'red')
plt.plot(x, y, '.', markersize=12)
plt.yscale("log")
plt.xlabel('Capital (a. currency)')
plt.ylabel('Frequency (a.u.)')
plt.legend(['Simulated data','Fit line'], fontsize=12)
plt.grid(linestyle='--', linewidth=0.2)
# plt.savefig("./tex/img/expo.pgf")
print(f"Constant: {fit_A} +- {std_A}")
print(f"Slope: {fit_a} +- {std_a}")
plt.show()
