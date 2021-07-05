import matplotlib.pyplot as plt
import numpy as np

from utils import extract_from_file

mean_conv = extract_from_file("../logs/map_mean_convergence.txt")
plt.figure()
plt.plot(mean_conv)
plt.savefig("images/max_mean_conv.eps")

plt.figure()
plt.plot(mean_conv[0:300])
plt.savefig("images/max_mean_conv_zoom.eps")
plt.show()

mean_conv = extract_from_file("../logs/ts_mean_convergence.txt")
plt.figure()
plt.plot(mean_conv)
plt.savefig("images/ts_max_mean_conv.eps")
plt.show()

