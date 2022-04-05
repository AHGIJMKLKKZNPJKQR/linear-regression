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


if len(sys.argv) < 2:
    print("Please provide a base function name and scaling type.")
    exit(1)


fig, ax = plt.subplots()
fig.set_size_inches(w=4.2, h = 2.1)
ax.set_xlabel('Training data subset')
ax.set_ylabel('Average error squared')

def getData(filename):
    file = open(filename)
    ret = np.array([[np.double(x) for x in l.strip().split()] for l in list(file)])
    file.close()
    return (ret[:, 0], ret[:, 1], ret[:, 2], ret[:, 3])

def plotVals(x, ymin, yavg, ymax, color, label, type):
    if type:
        ax.fill_between(x, ymin, ymax, color = color, facecolor = "none", alpha = 0.5, label = label, hatch = "///", zorder = 1)
    else:
        ax.fill_between(x, ymin, ymax, color = color, alpha = 0.1, label = label, zorder = 1)
    ax.plot(x, yavg, color = color, zorder = 2)


xspec = np.array([0.01, 0.02, 0.03, 0.125, 0.625, 1])

if len(sys.argv) == 2 or sys.argv[2] == "ridge":
    x, ymin, yavg, ymax = getData(f"std/ridge.err.{sys.argv[1]}")
    plotVals(x, ymin, yavg, ymax, "red", "Ridge standardized", False)
    yspec = np.array([yavg[i] for i in [0, 1, 2, 4, 9, 13]])
    ax.scatter(xspec, yspec, color="darkred", zorder = 3)
    x, ymin, yavg, ymax = getData(f"norm/ridge.err.{sys.argv[1]}")
    plotVals(x, ymin, yavg, ymax, "blue", "Ridge normalized", True)
    yspec = np.array([yavg[i] for i in [0, 1, 2, 4, 9, 13]])
    ax.scatter(xspec, yspec, color="darkblue", zorder = 3)

elif sys.argv[2] == "lasso":
    x, ymin, yavg, ymax = getData(f"std/lasso.err.{sys.argv[1]}")
    plotVals(x, ymin, yavg, ymax, "red", "Lasso standardized", False)
    yspec = np.array([yavg[i] for i in [0, 1, 2, 4, 9, 13]])
    ax.scatter(xspec, yspec, color="darkred", zorder = 3)
    x, ymin, yavg, ymax = getData(f"norm/lasso.err.{sys.argv[1]}")
    plotVals(x, ymin, yavg, ymax, "blue", "Lasso normalized", True)
    yspec = np.array([yavg[i] for i in [0, 1, 2, 4, 9, 13]])
    ax.scatter(xspec, yspec, color="darkblue", zorder = 3)
else:
    x, ymin, yavg, ymax = getData(f"std/elastic.err.{sys.argv[1]}")
    plotVals(x, ymin, yavg, ymax, "red", "Elastic net standardized", False)
    yspec = np.array([yavg[i] for i in [0, 1, 2, 4, 9, 13]])
    ax.scatter(xspec, yspec, color="darkred", zorder = 3)
    x, ymin, yavg, ymax = getData(f"norm/elastic.err.{sys.argv[1]}")
    plotVals(x, ymin, yavg, ymax, "blue", "Elastic net normalized", True)
    yspec = np.array([yavg[i] for i in [0, 1, 2, 4, 9, 13]])
    ax.scatter(xspec, yspec, color="darkblue", zorder = 3)

ax.legend()
# plt.xscale("log")
# plt.show()
plt.savefig(f'learning-{sys.argv[1]}-{sys.argv[2]}.pgf', format="pgf")