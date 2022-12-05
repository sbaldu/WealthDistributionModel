import newModel
import matplotlib.pyplot as plt
import numpy as np
from tqdm import tqdm

def data(vec):
    x = np.arange(0, int(max(vec))+1)
    y = np.zeros(int(max(vec))+1)
    for element in vec:
        y[int(element)] += 1
    return x,y

net = newModel.newModel(100,10**5)

ntot = sum(net.getPlayers())
n = 5.5*10**4
for i in tqdm(range(int(n))):
    print(i)
    net.evolveSavings()
    print(sum(net.getPlayers()))
    assert(sum(net.getPlayers()) == ntot)
# x = data(net.getPlayers())[0]
# y = data(net.getPlayers())[1]
# plt.plot(x,y)
# plt.plot(x,100/(x**1))
plt.hist(net.getPlayers(),bins=90)
plt.show()
