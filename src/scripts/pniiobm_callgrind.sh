#!/bin/bash

rm -f hdf5.nxs pniio.nxs
CALLGRIND="valgrind --tool=callgrind"
echo "Running HDf5 benchmark ..."
nframes=1000
nruns=2
echo "Running HDF5 pniio benchmark ..."
$CALLGRIND --callgrind-out-file=callgrind.hdf5.out pniiobm -n$nframes -r$nruns -bhdf5 -lhdf5.nxs -oram/output.h5
echo "Running PNIIO benchmark ..."
$CALLGRIND --callgrind-out-file=callgrind.pniio.out pniiobm -n$nframes -r$nruns -bpniio -lpniio.nxs -oram/output.h5

