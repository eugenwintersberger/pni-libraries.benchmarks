#!/bin/bash

rm -f hdf5.nxs pniio.nxs
rm -f output.h5
nruns=100
nframes=1000
echo "Running PNIIO benchmark ..."
time pniiobm -n$nframes -r$nruns -bpniio -lpniio.nxs -oram/output.h5

rm -f output.h5

echo "Running HDf5 benchmark ..."
time pniiobm -n$nframes -r$nruns -bhdf5 -lhdf5.nxs -oram/output.h5

