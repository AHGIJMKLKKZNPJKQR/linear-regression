import matplotlib.pyplot as plt
import numpy as np
import sys

if len(sys.argv) < 2:
    print("Please provide a file name.")
    exit(1)

file = open(sys.argv[1], 'r')

data = np.array([[np.double(x) for x in l.strip().split()] for l in list(file)])

x = data[:, 0]

fig, ax = plt.subplots()
ax.set_xlabel('Regularization parameter')
ax.set_ylabel('Coordinate importance')

for i in range(2, data.shape[1] - 1):
    ax.plot(x, data[:, i], label=f'x{i-1}')
ax.legend()
plt.xscale("log")
plt.show()