import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("./data/adult_cleaned.csv")
data = df['fnlwgt'].values.tolist()

nBins = 200
plt.hist(data, bins=nBins)
plt.xlabel('Capital (US dollars)')
plt.ylabel('Frequency')
plt.savefig("./tex/img/global_real_distribution.pgf")
plt.yscale('log')
plt.savefig("./tex/img/real_head.pgf")
plt.xscale('log')
plt.savefig("./tex/img/real_tail.pgf")
# plt.show()
