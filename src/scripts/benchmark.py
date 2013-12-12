#module with benchmark related functions and classes

import numpy
from matplotlib import pyplot 
import sys
from itertools import chain
import re

class benchmark_result(object):
    def __init__(self,t,title,data):
        
        self.type = t
        self.data = data
        self.title = title

    def min(self):
        min_vals = []

        for v in self.data.values():
            min_vals.append(v.min())

        return min(min_vals)

    def max(self):
        max_vals = []
        
        for v in self.data.values():
            max_vals.append(v.max())

        return max(max_vals)



def get_result(fname):
    #first we have to read the header information
    f = open(fname,"r")
    t      = f.readline()[1:].strip()
    title  = f.readline()[1:].strip()
    header = f.readline()[1:].strip()
    f.close()

    #parse the header line
    header = re.split("\s+",header)

    #load numerical data - skip tow header lines
    data = numpy.loadtxt(fname,skiprows=3)

    data_dict = {}
    for i in range(0,data.shape[1]):
        data_dict[header[i]] = data[:,i]

    return benchmark_result(t,title,data_dict)

def get_result_range(*results):
    all_max = []
    all_min = []

    for r in results:
        all_max.append(r.max())
        all_min.append(r.min())

    return (min(all_min),max(all_max))



