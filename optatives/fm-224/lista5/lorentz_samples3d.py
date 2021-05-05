import matplotlib.pyplot as plt
import numpy as np

from utils import extract_from_file

for tau in [9]:
	lorentz_ts = extract_from_file('lorentz_time_series.txt')
	xline = lorentz_ts[2*tau:len(lorentz_ts)]
	yline = lorentz_ts[tau:len(lorentz_ts) - tau]
	zline = lorentz_ts[0:len(lorentz_ts) - 2*tau]
	plt.figure()
	ax = plt.axes(projection='3d')
	plt.plot(xline, yline, zline, ',')
	plt.savefig('reconstructed_lorentz.eps')

