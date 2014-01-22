#!/bin/bash

NRUNS=1000
CMD=indexmapbm

#start with the fortran reference
echo "dynamic index map"
$CMD -n$NRUNS -mdynamic &> dynamic_map.dat
echo "fixed dim index map"
$CMD -n$NRUNS -mfixed &> fixed_map.dat
echo "static index map"
$CMD -n$NRUNS -mstatic &> static_map.dat

