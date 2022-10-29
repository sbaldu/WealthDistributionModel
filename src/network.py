import random
import matplotlib.pyplot as plt
import numpy as np

class network:
    def __init__(self,rows=10,cols=10,initialCapital=10):
        self.players = [initialCapital for i in range(rows*cols)]
        self.rows = rows
        self.cols = cols
        self.nPlayers = len(self.players)
    def couples(self,player):
        players = [i for i in range(self.nPlayers) if i != player and self.players[i] > 0]
        second = random.choice(players)
        return [player,second]
    def gamble(self,first,second):
        r = random.random()
        if r > 0.5:
            self.players[first] += 1  
            self.players[second] -= 1  
        else:
            self.players[second] += 1  
            self.players[first] -= 1  
    def evolve(self,nCouples):
        players = [i for i in range(self.nPlayers) if self.players[i] > 0]
        for i in range(nCouples):
            first = random.choice(players)
            couple = self.couples(first)
            self.gamble(couple[0],couple[1])
    def graph(self):
        j = 0
        for i in range(self.nPlayers):
            print(self.players[i],end=' ')
            j += 1
            if j % self.cols == 0:
                print('\n')
    def plot(self):
        plt.hist(self.players)
        plt.show()

n = network(10,10,50)
for i in range(10**4):
    n.evolve(10)
n.graph()
n.plot()
