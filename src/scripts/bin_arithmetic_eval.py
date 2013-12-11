#!/usr/bin/env python

import numpy
from matplotlib import pyplot 
import sys
from itertools import chain

def read_data(fname):
    data = numpy.loadtxt(fname,skiprows=1)

    add = data[:,0]
    sub = data[:,1]
    div = data[:,2]
    mul = data[:,3]
    mix = data[:,4]

    return (add,sub,div,mul,mix)

def plot_hists(ax,data):

    for i in range(0,5): ax.hist(data[i],log=True)

    pyplot.legend(("add","sub","div","mul","mix"))

def get_x_range(*args):
    all_max = []
    all_min = []

    for a in args:
        all_max.append(a.max())
        all_min.append(a.min())

    return (min(all_min),max(all_max))

f_file = sys.argv[1] #fortran file
p_file = sys.argv[2] #pointer file
o_file = sys.argv[3] #C++ object file
af_file = sys.argv[4] #C++ object with fixed dim array

f_data = read_data(f_file)
p_data = read_data(p_file)
o_data = read_data(o_file)
af_data = read_data(af_file)

#need minimum and maximum of the data
(xmin,xmax) = get_x_range(*chain(f_data,p_data,o_data,af_data))

pyplot.figure()
pyplot.subplots_adjust(hspace=0.001)

ax1 = pyplot.subplot(411)
plot_hists(ax1,f_data)
ax_limits = ax1.axis()
ax1.axis((xmin,xmax,ax_limits[2],ax_limits[3]))

ax2 = pyplot.subplot(412,sharex=ax1)
plot_hists(ax2,p_data)

ax3 = pyplot.subplot(413,sharex=ax1)
plot_hists(ax3,o_data)

ax4 = pyplot.subplot(414,sharex=ax1)
plot_hists(ax4,af_data)

pyplot.show()




