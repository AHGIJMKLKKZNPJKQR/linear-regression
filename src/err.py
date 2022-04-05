import matplotlib
matplotlib.use("pgf")
matplotlib.rcParams.update({
    "pgf.texsystem": "pdflatex",
    'font.family': 'serif',
    'text.usetex': True,
    'pgf.rcfonts': False,
})
import matplotlib.pyplot as plt
import numpy as np
import sys

if len(sys.argv) < 3:
    print("Please provide a base function name and regularization type.")
    exit(1)

file = open(f"out/{sys.argv[2]}.dump.{sys.argv[1]}", 'r')

data = np.array([[np.double(x) for x in l.strip().split()] for l in list(file)])

x = data[:, 0]

fig, ax = plt.subplots()
fig.set_size_inches(w=4.5, h = 3.5)
ax.set_xlabel('Regularization parameter')
ax.set_ylabel('Average error squared')

y = data[:, data.shape[1] - 1]
ymin = y.min()
yargmin = y.argmin()

ax.plot(x, y)

# ax.scatter(x[yargmin], ymin, color = "red")

plt.xscale("log")
# plt.show()
plt.savefig(f"regularization-{sys.argv[1]}-{sys.argv[2]}.pgf", format="pgf")