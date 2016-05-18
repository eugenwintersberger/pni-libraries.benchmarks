#!/usr/bin/env python

from matplotlib import pyplot as plt
import numpy
import pandas
from pandas import Series,DataFrame
import sys

def load_binary_data(fname):
    """
    
    return 
       (a*b,a*b+(d-e)/f,a+b,a-b,a/b)
    """
    data = numpy.loadtxt(fname)/1.e+6
    return {"a*b":data[:,0],
            "a*b+(d-e)/f":data[:,1],
            "a+b":data[:,2],
            "a-b":data[:,3],
            "a/b":data[:,4]}

def load_unary_data(fname):
    """
    return 
       (a*=b,a*=s,a+=b,a+=s,a-=b,a-=s,a/=b,a/=s)
    """
    data = numpy.loadtxt(fname)/1.e+6

    return {"a*=b":data[:,0],"a*=s":data[:,1],
            "a+=b":data[:,2],"a+=s":data[:,3],
            "a-=b":data[:,4],"a-=s":data[:,5],
            "a/=b":data[:,6],"a/=s":data[:,7]}


def get_unary_frame(dyn,fix,ptr,key):
    frame = DataFrame({"darray":dyn[key],"fixed":fix[key],"pointer":ptr[key]})
    frame = frame.mean()
    return DataFrame(frame/frame["pointer"]).T


def get_binary_frame(dyn,fix,ptr,fortran,key):
    frame = DataFrame({"darray":dyn[key],"fixed":fix[key],
                       "pointer":ptr[key],"fortran":fortran[key]})
    frame = frame.mean()
    return DataFrame(frame/frame["pointer"]).T

#load results for binary arithmetic
ptr_binary = load_binary_data("bin_arithmetic_cpp_pointer.dat")
for_binary = load_binary_data("bin_arithmetic_fortran.dat")
dyn_binary = load_binary_data("bin_arithmetic_cpp_operator_dynamic.dat")
fix_binary = load_binary_data("bin_arithmetic_cpp_operator_fixed.dat")


mult = get_binary_frame(dyn_binary,fix_binary,ptr_binary,for_binary,"a*b")
mixed = get_binary_frame(dyn_binary,fix_binary,ptr_binary,for_binary,"a*b+(d-e)/f")
add = get_binary_frame(dyn_binary,fix_binary,ptr_binary,for_binary,"a+b")
sub = get_binary_frame(dyn_binary,fix_binary,ptr_binary,for_binary,"a-b")
div = get_binary_frame(dyn_binary,fix_binary,ptr_binary,for_binary,"a/b")

collate = pandas.concat([add,sub,mult,div,mixed])

collate.index = ["a+b","a-b","a*b","a/b","a*b+\n(d-e)/f"]
print collate



#load data unary arithmetics
ptr_unary = load_unary_data("unary_arithmetic_cpp_pointer.dat")
dyn_unary = load_unary_data("unary_arithmetic_cpp_operator_dynamic.dat")
fix_unary = load_unary_data("unary_arithmetic_cpp_operator_fixed.dat")

mult_ab = get_unary_frame(dyn_unary,fix_unary,ptr_unary,"a*=b")
mult_as = get_unary_frame(dyn_unary,fix_unary,ptr_unary,"a*=s")

sub_ab = get_unary_frame(dyn_unary,fix_unary,ptr_unary,"a-=b")
sub_as = get_unary_frame(dyn_unary,fix_unary,ptr_unary,"a-=s")

add_ab = get_unary_frame(dyn_unary,fix_unary,ptr_unary,"a+=b")
add_as = get_unary_frame(dyn_unary,fix_unary,ptr_unary,"a+=s")

div_ab = get_unary_frame(dyn_unary,fix_unary,ptr_unary,"a/=b")
div_as = get_unary_frame(dyn_unary,fix_unary,ptr_unary,"a/=s")

unary_collate = pandas.concat([mult_ab,mult_as,div_ab,div_as,
                               add_ab,add_as,sub_ab,sub_as])
unary_collate.index=["a*=array","a*=scalar",
                     "a/=array","a/=scalar",
                     "a+=array","a+=scalar",
                     "a-=array","a-=scalar"]

print unary_collate

