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
ax.set_ylabel('Average error squared')

y = data[:, data.shape[1] - 1]
ymin = y.min()
yargmin = y.argmin()

ax.plot(x, y)

ax.scatter(x[yargmin], ymin, color = "red")

plt.xscale("log")
plt.show()