import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
T = np.loadtxt(sys.argv[1])

X = T[:,0]
Y = T[:,2] / T[:,1]

fig,ax = plt.subplots()
ax.xaxis.set_major_formatter(FuncFormatter(lambda x,pos: '{}'.format(int(x))))

plt.plot(X,Y)
plt.show()
