#!/bin/bash

rm -f hdf5.nxs pniio.nxs
CALLGRIND="valgrind --tool=callgrind"
echo "Running HDf5 benchmark ..."
$CALLGRIND --callgrind-out-file=hdf5.out.profile pniiobm -n1000 -r1 -bhdf5 -lhdf5.nxs -oram/output.h5
echo "Running PNIIO benchmark ..."
$CALLGRIND --callgrind-out-file=pniio.out.profile pniiobm -n1000 -r1 -bpniio -lpniio.nxs -oram/output.h5

