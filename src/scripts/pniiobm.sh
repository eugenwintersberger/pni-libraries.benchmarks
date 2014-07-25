#!/bin/bash

rm -f hdf5.nxs pniio.nxs
echo "Running HDf5 benchmark ..."
pniiobm -n1000 -r100 -bhdf5 -lhdf5.nxs -oram/output.h5
echo "Running PNIIO benchmark ..."
pniiobm -n1000 -r100 -bpniio -lpniio.nxs -oram/output.h5

