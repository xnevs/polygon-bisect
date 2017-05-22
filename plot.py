import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon

P = np.loadtxt(sys.argv[1],delimiter=',')
polygon = Polygon(P,False)

fig,ax = plt.subplots()
ax.add_patch(polygon)
plt.autoscale()
plt.show()
