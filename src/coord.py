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
fig.set_size_inches(w=4.5, h = 2)
ax.set_xlabel('Regularization parameter')
ax.set_ylabel('Coordinate importance')

for i in range(2, data.shape[1] - 1):
    ax.plot(x, data[:, i], label=f'x{i-1}')
ax.legend()
plt.xscale("log")
plt.savefig(f"coordinates-{sys.argv[1]}-{sys.argv[2]}.pgf", format="pgf")
# plt.show()