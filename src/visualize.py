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

FILENAME="data/norm.data"

if len(sys.argv) < 2:
    print("Please provide a coordinate number.")
    exit(1)

coord = int(sys.argv[1])

file = open(FILENAME, 'r')

data = np.array([[np.double(x) for x in l.strip().split()] for l in list(file)])

x = data[:, coord]
y = data[:, data.shape[1] - 1]

fig, ax = plt.subplots()
fig.set_size_inches(w=4.5, h = 1.6)
ax.set_xlabel('X coordinate value')
# ax.set_ylabel('Coordinate importance')
ax.set_ylabel('Y value')

# for i in range(2, data.shape[1] - 1):
    # ax.plot(x, data[:, i], label=f'x{i-1}')
ax.scatter(x, y, label = "Data")
ax.scatter(x, 456 - 370 * np.sin(3.6 * (x - 2.7)), label = "Fitted function")
ax.legend()
# plt.show()
plt.savefig(f'fitted-func.pgf', format="pgf")