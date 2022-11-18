import matplotlib.pyplot as plt
import numpy
import network as n

net = n.network(1,100,100)
net.createLink()
print(net.getAdjacency())
