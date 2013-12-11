#!/bin/bash

#start with the fortran reference
arithmeticbm -b --fortran -r500 -x3000 -y3000 &> bin_arithmetic_fortran.dat
arithmeticbm -b -p -r500 -x3000 -y3000 &> bin_arithmetic_cpp_pointer.dat
arithmeticbm -b -r500 -x3000 -y3000 &> bin_arithmetic_cpp_operator_dynamic.dat
arithmeticbm -b -afixed -r500 -x3000 -y3000 &> bin_arithmetic_cpp_operator_fixed.dat

