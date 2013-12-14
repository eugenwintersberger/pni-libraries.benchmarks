#!/bin/bash

NRUNS=1000000
CMD=./index_map_bm
$CMD -n$NRUNS -m"old_cmap" &> old_cmap.dat
$CMD -n$NRUNS -m"new_cmap" &> new_cmap.dat
$CMD -n$NRUNS -m"old_static_cmap" &> old_static_cmap.dat
$CMD -n$NRUNS -m"new_static_cmap" &> new_static_cmap.dat
