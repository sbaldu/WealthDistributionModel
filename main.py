import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import network

def data(vec):
    x = np.arange(0, max(vec)+1)
    y = np.zeros(max(vec)+1)
    for element in vec:
        y[element] += 1
    return x,y

net = network.network(1,100,100)
n = 10**5
for i in range(n):
    net.evolveUniform()

#hist = plt.hist(net.playersMoney())
plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')

# plt.show(hist,best_fit_line)
plt.yscale("log")
plt.show()

net = network.network(1,100,100)
n = 10**6
for i in range(n):
    net.evolveUniform()

#hist = plt.hist(net.playersMoney())
plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')

# plt.show(hist,best_fit_line)
plt.yscale("log")
plt.show()

net = network.network(1,100,100)
n = 10**7
for i in range(n):
    net.evolveUniform()

#hist = plt.hist(net.playersMoney())
plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')

# plt.show(hist,best_fit_line)
plt.yscale("log")
plt.show()

net = network.network(1,100,100)
n = 10**6
for i in range(n):
    net.evolvePrefAtt()
    if i % 1000 == 0:
        net.flatTax(10)

#hist = plt.hist(net.playersMoney())
plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')

# plt.show(hist,best_fit_line)
plt.yscale("log")
plt.xscale("log")
plt.show()

net = network.network(1,100,100)
for i in range(n):
    net.evolvePrefAtt()
    if i % 1500 == 0:
        net.flatTax(10)

#hist = plt.hist(net.playersMoney())
plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')

# plt.show(hist,best_fit_line)
plt.yscale("log")
plt.xscale("log")
plt.show()

net = network.network(1,100,100)
for i in range(n):
    net.evolvePrefAtt()
    if i % 2000 == 0:
        net.flatTax(10)

#hist = plt.hist(net.playersMoney())
plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')

# plt.show(hist,best_fit_line)
plt.yscale("log")
plt.xscale("log")
plt.show()

net = network.network(1,100,100)
for i in range(n):
    net.evolvePrefAtt()
    if i % 500 == 0:
        net.flatTax(10)

#hist = plt.hist(net.playersMoney())
plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')

# plt.show(hist,best_fit_line)
plt.yscale("log")
plt.xscale("log")
plt.show()
