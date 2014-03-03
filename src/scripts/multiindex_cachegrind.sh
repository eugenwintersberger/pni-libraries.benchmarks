#!/bin/bash

TOOL="valgrind --tool=cachegrind"

NRUNS=10
CMD="multiindexbm -r$NRUNS"

$TOOL --cachegrind-out-file=cg_mindex_darray_pointer.out $CMD -tdarray -apointer
$TOOL --cachegrind-out-file=cg_mindex_darray_variadic.out $CMD -tdarray -avariadic
$TOOL --cachegrind-out-file=cg_mindex-darray_array.out $CMD -tdarray -aarray
$TOOL --cachegrind-out-file=cg_mindex_darray_vector.out $CMD -tdarray -avector

