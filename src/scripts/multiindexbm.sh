#!/bin/bash

cmd=./multiindexbm
nruns=1000000
size="-x100 -y100"

$cmd --array-type=ptr -r$nruns $size &> multiindexbm_ptr_100x100.dat
$cmd --array-type=darray -r$nruns $size &> multiindexbm_darray_100x100.dat
$cmd -tdarray --nruns=$nruns $size &> multiindexbm_ndarray_100x100.dat
$cmd -tsarray --nruns=$nruns $size &> multiindexbm_sarray_100x100.dat
