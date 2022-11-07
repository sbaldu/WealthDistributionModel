import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data = []
with open("./histogram.dat") as file:
    for line in file:
        row = line.split()
        row = [float(x) for x in row]
        data.append(row)

df = pd.DataFrame(data,columns=["x","y"])
print(df)

plt.figure()
plt.hist(df["x"],weights=df["y"],bins=1+len(df["x"]), density=True, color='yellow', edgecolor='black', rwidth=0.85)

# plt.hist(x, density=True, color='yellow', edgecolor='black', rwidth=0.85)

plt.yscale("log")
plt.xscale("log")
plt.show()