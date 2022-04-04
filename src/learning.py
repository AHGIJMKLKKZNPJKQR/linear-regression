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
ax.set_xlabel('Training data subset')
ax.set_ylabel('Average error squared')

y = data[:, 1]# ymin = y.min()

ax.plot(x, y)
ax.scatter(x, y, color="red")

# plt.xscale("log")
plt.show()