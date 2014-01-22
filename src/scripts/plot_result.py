#!/usr/bin/env python

from matplotlib import pyplot
from benchmark import get_result 

import argparse

def plot_single_result(result,col_filter=None):
    """
    Plot a single result to a canvas. 
    """
    pyplot.figure()
    pyplot.title(r.type +": " +  r.title)
    ax = pyplot.subplot(111)

    keys = []
    if col_filter:
        keys = col_filter
    else:
        keys= result.data.keys()

    for k in keys: 
        ax.hist(result.data[k],nbins,log=logy_flag)

    pyplot.legend(keys,loc='best')

def plot_multiple_results(results,col_filter=None):
    pyplot.figure()
    pyplot.title(results[0].type)
    ax = pyplot.subplot(111)

    keys = []
    if col_filter:
        keys = col_filter
    else:
        keys= results[0].data.keys()

    l = []

    for r in results:
        for k in keys:
            l.append(r.title + ": "+k)
            ax.hist(r.data[k],nbins,log=logy_flag)

    pyplot.legend(l,loc='best')




parser = argparse.ArgumentParser(description="Command line options")
parser.add_argument('input_files',type=str,nargs="+",
                    help="Input files")
parser.add_argument('--bins','-b',
                    type = int,
                    action = "store",
                    dest = "nbins",
                    default = 10,
                    help = "number of bins for the histogram")
parser.add_argument('--logy',action="store_true",default=False,
                    dest="log_y",
                    help="plot y-axis on a logarithmic scale")
parser.add_argument('--logx',action="store_true",
                    dest="log_x",
                    help="plot x-axis on logarithmic scale")
parser.add_argument('--column','-c',default=None,
                    dest="columns",
                    action="append",
                    help="select columns to plot")
parser.add_argument('--collate',action="store_true",default=False,
                    dest="collate",
                    help="collate all data together")

args = parser.parse_args()

nbins = args.nbins
logx_flag = args.log_x
logy_flag = args.log_y

results = []
for f in args.input_files:
    results.append(get_result(f))


print args.columns

if args.collate:
    plot_multiple_results(results,args.columns)
else:
    for r in results:
        plot_single_result(r,args.columns)

pyplot.show()



