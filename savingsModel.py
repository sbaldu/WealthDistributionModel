import newModel
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from tqdm import tqdm

def data(vec):
    x = np.arange(0, int(max(vec))+1)
    y = np.zeros(int(max(vec))+1)
    for element in vec:
        y[int(element)] += 1
    return x,y

net = newModel.newModel(5,10**5)
n = 1.0*10**6
for i in tqdm(range(int(n))):
    net.evolveSavings()

sns.distplot(net.getPlayers(), hist=False)
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Capital (a. currency)')
plt.ylabel('Frequency (a.u.)')
plt.ylim([10**(-5),10**(1)])
plt.savefig("./tex/img/savings.pgf")
plt.show()
