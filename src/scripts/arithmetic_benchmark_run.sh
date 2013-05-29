#!/bin/bash

./farithmeticbm -r9000 -x3000 -y3000 &> fortran_benchmark_result.log
./arithmeticbm -b -r9000 -x3000 -y3000 &> cpp_benchmark_result.log
