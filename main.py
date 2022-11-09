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
plt.savefig("prova_0.png")
plt.clear()

net = network.network(1,100,100)
n = 10**6
for i in range(n):
    net.evolveUniform()

#hist = plt.hist(net.playersMoney())
plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')

# plt.show(hist,best_fit_line)
plt.yscale("log")
plt.show()
plt.savefig("prova_1.png")
plt.clear()

net = network.network(1,100,100)
n = 10**7
for i in range(n):
    net.evolveUniform()

#hist = plt.hist(net.playersMoney())
plt.plot(data(net.playersMoney())[0],data(net.playersMoney())[1],'bo')

# plt.show(hist,best_fit_line)
plt.yscale("log")
plt.show()
plt.savefig("prova_2.png")
plt.clear()

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
plt.savefig("prova_3.png")
plt.clear()

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
plt.savefig("prova_4.png")
plt.clear()

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
plt.savefig("prova_5.png")
plt.clear()

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
plt.savefig("prova_6.png")
plt.clear()