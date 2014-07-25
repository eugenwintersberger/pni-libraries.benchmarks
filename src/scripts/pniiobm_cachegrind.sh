#!/bin/bash

rm -f hdf5.nxs pniio.nxs
CACHEGRIND="valgrind --tool=cachegrind"
echo "Running HDf5 benchmark ..."
$CACHEGRIND --cachegrind-out-file=hdf5.out.profile pniiobm -n1000 -r1 -bhdf5 -lhdf5.nxs -oram/output.h5
echo "Running PNIIO benchmark ..."
$CACHEGRIND --cachegrind-out-file=pniio.out.profile pniiobm -n1000 -r1 -bpniio -lpniio.nxs -oram/output.h5

