#!/bin/bash

NRUNS=1000
CMD=iteratorbm

#start with the fortran reference
echo "darray - iterator access"
$CMD -r$NRUNS -tdarray &> iterator_darray.dat
echo "darray view - iterator acess"
$CMD -r$NRUNS --view -tdarray &> iterator_darray_view.dat

echo "farray - iterator access"
$CMD -r$NRUNS -tfarray &> iterator_farray.dat
echo "farray view - iterator access"
$CMD -r$NRUNS --view -tfarray &> iterator_farray_view.dat

echo "sarray - iterator access"
$CMD -r$NRUNS -tsarray &> iterator_sarray.dat
echo "sarray view - iterator access"
$CMD -r$NRUNS --view -tsarray &> iterator_sarray_view.dat
