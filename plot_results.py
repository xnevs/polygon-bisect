import sys
import numpy as np
import matplotlib.pyplot as plt

T = np.loadtxt(sys.argv[1])

X = T[:,0]
Y = T[:,2] / T[:,1]

plt.plot(X,Y)
plt.show()
