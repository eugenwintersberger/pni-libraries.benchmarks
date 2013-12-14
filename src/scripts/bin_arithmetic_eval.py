#!/usr/bin/env python

import numpy
from matplotlib import pyplot 
import sys
from itertools import chain
import re
from benchmark import get_result
from benchmark import get_result_range

def plot_hists(ax,result):

    legend_list = []
    for i in result.data.items():
        ax.hist(i[1],bins=100,log=False)
        legend_list.append(i[0])

    pyplot.legend(legend_list)


f_result = get_result(sys.argv[1])
p_result = get_result(sys.argv[2])
o_result = get_result(sys.argv[3])
af_result = get_result(sys.argv[4])


#need minimum and maximum of the data
(rmin,rmax) = get_result_range(f_result,p_result,o_result,af_result)

keys = f_result.data.keys()

t     = f_result.type
llist = [f_result.title,p_result.title,o_result.title,af_result.title]

log_flag = True
for k in keys:
    pyplot.figure()

    pyplot.subplots_adjust(hspace=0.001)
    ax1 = pyplot.subplot(411)
    ax1.hist(f_result.data[k],color='b',log=log_flag)
    pyplot.title(t+": "+k)
    pyplot.legend([f_result.title])
    r = pyplot.axis()
    pyplot.axis([rmin,rmax,r[2],r[3]])

    ax2 = pyplot.subplot(412,sharex=ax1)
    ax2.hist(p_result.data[k],color='c',log=log_flag)
    pyplot.legend([p_result.title])

    ax3 = pyplot.subplot(413,sharex=ax1)
    ax3.hist(o_result.data[k],color='r',log=log_flag)
    pyplot.legend([o_result.title])


    ax4 = pyplot.subplot(414,sharex=ax1)
    pyplot.hist(af_result.data[k],color='g',log=log_flag)
    pyplot.legend([af_result.title])

    xlabels = ax1.get_xticklabels()+ax2.get_xticklabels()+ax3.get_xticklabels()
    pyplot.setp(xlabels,visible=False)


pyplot.show()




