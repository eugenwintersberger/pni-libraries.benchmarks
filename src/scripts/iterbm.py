#!/usr/bin/env python

from matplotlib import pyplot as plt
import numpy
import pandas
from pandas import Series,DataFrame

def load_data(fname):
    data = numpy.loadtxt(fname)/1.e+6
    return (data[:,0],data[:,1])


p_read,p_write = load_data("pointer_darray.dat")
di_read,di_write = load_data("iterator_darray.dat")
dv_read,dv_write = load_data("iterator_darray_view.dat")
fi_read,fi_write = load_data("iterator_farray.dat")
fv_read,fv_write = load_data("iterator_farray_view.dat")
si_read,si_write = load_data("iterator_sarray.dat")
sv_read,sv_write = load_data("iterator_sarray_view.dat")

frame_read = DataFrame({"dynamic array iter":di_read,
                        "dynamic array view":dv_read,
                        "fixed dim array iter":fi_read,
                        "fixed dim array view":fv_read,
                        "static array iter":si_read,
                        "static array view":sv_read,
                        "Pointer":p_read})

frame_write = DataFrame({"dynamic array iter":di_write,
                         "dynamic array view":dv_write,
                         "fixed dim array iter":fi_write,
                         "fixed dim array view":fv_write,
                         "static array iter":si_write,
                         "static array view":sv_write,
                         "Pointer":p_write})

read_mean = frame_read.mean()
write_mean = frame_write.mean()
read_ref = read_mean["Pointer"]
write_ref = write_mean["Pointer"]

print "reading performance"
print read_mean/read_ref
print 
print "writing performance"
print write_mean/write_ref




