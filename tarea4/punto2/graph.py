import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def readData(filename):
    columns = max(len(l.split()) for l in open(filename + '.dat'))

    df = pd.read_table(filename + '.dat',
                       delim_whitespace=True,
                       header=None,
                       usecols=range(columns),
                       engine='python')

    return np.array(df)


print('Reading data...')
print('Reading ts...')
ts = readData('t')
print('Reading rs...')
rs = readData('r')
print('Reading ps...')
ps = readData('p')

print('Plotting data...')
for i in range(len(ts)):
    plt.plot(ts[i, :], ps[i,:])
plt.xlabel("t (mins)")
plt.ylabel("Proteins")
plt.savefig("proteins.png")

plt.close()

for i in range(len(ts)):
    plt.plot(ts[i, :], rs[i,:])
plt.xlabel("t (mins)")
plt.ylabel("RNAs")
plt.savefig("rnas.png")
