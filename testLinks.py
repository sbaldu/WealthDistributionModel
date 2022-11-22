import matplotlib.pyplot as plt
import numpy
import network as n

net = n.network(1,5,5)
net.createLinks(4)
print(net.getAdjacency())
print(len(net.getAdjacency()))
net.printMatrix()
