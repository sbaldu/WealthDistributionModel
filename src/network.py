import matplotlib.pyplot as plt
import numpy as np
import random
import math

class network:
    def __init__(self,rows=10,cols=10,initialCapital=10):
        self.players = [initialCapital for i in range(rows*cols)]
        self.nPlayers = len(self.players)
        self.indexes = np.arange(0,self.nPlayers)
        self.capital = initialCapital
        self.rows = rows
        self.cols = cols
    def couples(self,first):
        players = self.indexes
        np.delete(players,first) # I remove the first player in order to not make him play with himself (that would be sad)
        second = np.random.choice(players)
        return second
    def evolve(self):
        first = np.random.choice(self.indexes)
        second = self.couples(first)
        
        r = random.random()
        if r > 0.5:
            if self.players[first] > 0:
                self.players[second] += 1
                self.players[first] -= 1
        if r < 0.5:
            if self.players[second] > 0:
                self.players[second] -= 1
                self.players[first] += 1
        sum_ = sum(self.players)
        assert sum_ == self.capital*self.rows*self.cols, f"the sum is {sum_}, so you have added energy to the system."
    def graph(self):
        j = 0
        for i in range(self.nPlayers):
            print(self.players[i],end=' ')
            j += 1
            if j % self.cols == 0:
                print('\n')
    def plot(self):
        x = np.arange(0, max(self.players)+1)
        y = np.zeros(max(self.players)+1)
        for element in self.players:
            y[element] += 1

        # plot the points and overlay the fit function 
        plt.scatter(x,y)
        plt.show()

n = network(100,100,1)
for i in range(10**5):
    n.evolve()
n.plot()
plt.hist(n.players,bins=1+max(n.players))
plt.show()
