#!/usr/bin/env python

import numpy
from matplotlib import pyplot 
import sys
from itertools import chain
import re
from benchmark import get_result
from benchmark import get_result_range

import argparse


parser = argparse.ArgumentParser(description="Command line options")
parser.add_argument('--ptr-data','-p',
                    type=str,
                    action="store",
                    dest="pointer_file",
                    help="file with pointer access data")
parser.add_argument('--iter-data','-i',
                    type=str,
                    action="store",
                    dest="iterator_file",
                    help="file with iterator access data")
parser.add_argument('--view-data','-v',
                    type = str,
                    action = "store",
                    dest = "view_file",
                    help = "file with view iterator access data")
parser.add_argument('--bins','-b',
                    type = int,
                    action = "store",
                    dest = "nbins",
                    default = 10,
                    help = "number of bins for the histogram")
parser.add_argument('--logx',action="store_true",
                    dest="log_x",
                    help="plot x-axis on logarithmic scale")

args = parser.parse_args()

iter_result = get_result(args.iterator_file)
ptr_result  = get_result(args.pointer_file)
view_result = get_result(args.view_file)

nbins = args.nbins;

#===================plot write performance data================================
pyplot.figure()
ax = pyplot.subplot(111)
pyplot.title(iter_result.type + " write performance")
ax.hist(iter_result.data["write"],nbins,log=True,color='r')
ax.hist(ptr_result.data["write"],nbins,log=True,color='g')
ax.hist(view_result.data["write"],nbins,log=True,color='b')
pyplot.legend([iter_result.title,
               ptr_result.title,
               view_result.title],loc='best')

if args.log_x:
    ax.set_xscale('log')

pyplot.grid()

#==================plot read performance data==================================
pyplot.figure()
ax = pyplot.subplot(111)
pyplot.title(iter_result.type + " read performance")
ax.hist(iter_result.data["read"],nbins,log=True,color='r')
ax.hist(ptr_result.data["read"],nbins,log=True,color='g')
ax.hist(view_result.data["read"],nbins,log=True,color='b')
pyplot.legend([iter_result.title,
               ptr_result.title,
               view_result.title],loc='best')

if args.log_x:
    ax.set_xscale('log')

pyplot.grid()

#plot the images
pyplot.show()

