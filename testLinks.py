import matplotlib.pyplot as plt
import numpy as np
import network as n
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

net = n.network(5, 50, 50)
net.createLinks(12)

n = 2*10**5
for i in tqdm(range(n)):
    net.evolvebyLink()

x = data(net.players())[0][1::]
y = data(net.players())[1][1::]
y = [i/sum(y) for i in y] # normalization

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
plt.legend(['Fit line', 'Simulated data'], fontsize=12)
plt.grid(linestyle='--', linewidth=0.2)
print(f"Constant: {fit_A} +- {std_A}")
print(f"Slope: {fit_a} +- {std_a}")
plt.show()

# calculating the probabilities of having links, in general and given 
# that the two individuals are poor
probabilities = net.calcProb(net.getPoors())
prob_linked_and_poor = probabilities[0]
prob_linked = probabilities[1]
print("Probability of having a link given their poorness: " + str(round(prob_linked_and_poor*100, 2)) + "%")
print("Probability of having a link in general: " + str(round(prob_linked*100, 2)) + "%")
