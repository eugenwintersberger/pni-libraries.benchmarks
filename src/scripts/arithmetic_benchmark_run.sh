#!/bin/bash

NRUNS=1000
NX=200
NY=200

#start with the fortran reference
echo "Binary Fortran arithmetic benchmark ...."
arithmeticbm -b --fortran -r$NRUNS -x$NX -y$NY &> bin_arithmetic_fortran.dat
echo "Binary C++ arithmetic benchmark with pointers ..."
arithmeticbm -b -p -r$NRUNS -x$NX -y$NY &> bin_arithmetic_cpp_pointer.dat
echo "Binary C++ arithmetic benchmark with expr. templates and dyn. arrays ..."
arithmeticbm -b -r$NRUNS -x$NX -y$NY &> bin_arithmetic_cpp_operator_dynamic.dat
echo "Binary C++ arithmetic benchmark with expr. templates and fixed arrays ..."
arithmeticbm -b -afixed -r$NRUNS -x$NX -y$NY &> bin_arithmetic_cpp_operator_fixed.dat

