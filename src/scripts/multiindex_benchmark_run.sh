#!/bin/bash

NRUNS=1000
CMD=multiindexbm

#===============benchmark run for darray=======================================
echo "darray - variadic access"
$CMD -r$NRUNS -tdarray -avariadic &> mindex_darray_variadic.dat
echo "darray - vector access"
$CMD -r$NRUNS -tdarray -avector   &> mindex_darray_vector.dat
echo "darray - array access"
$CMD -r$NRUNS -tdarray -aarray   &> mindex_darray_array.dat
echo "darray - pointer access"
$CMD -r$NRUNS -tdarray -apointer   &> mindex_darray_pointer.dat

echo "darray view - variadic access"
$CMD -r$NRUNS -tdarray -v -avariadic &> mindex_darray_view_variadic.dat
echo "darray view - vector access"
$CMD -r$NRUNS -tdarray -v -avector   &> mindex_darray_view_vector.dat
echo "darray view - array access"
$CMD -r$NRUNS -tdarray -v -aarray   &> mindex_darray_view_array.dat

#===============benchmark run for farray=======================================
echo "farray - variadic access"
$CMD -r$NRUNS -tfarray -avariadic &> mindex_farray_variadic.dat
echo "farray - vector access"
$CMD -r$NRUNS -tfarray -avector   &> mindex_farray_vector.dat
echo "farray - array access"
$CMD -r$NRUNS -tfarray -aarray   &> mindex_farray_array.dat
echo "farray - pointer access"
$CMD -r$NRUNS -tfarray -apointer   &> mindex_farray_pointer.dat

echo "farray view - variadic access"
$CMD -r$NRUNS -tfarray -v -avariadic &> mindex_farray_view_variadic.dat
echo "farray view - vector access"
$CMD -r$NRUNS -tfarray -v -avector   &> mindex_farray_view_vector.dat
echo "farray view - array access"
$CMD -r$NRUNS -tfarray -v -aarray   &> mindex_farray_view_array.dat

#===============benchmark run for sarray=======================================
echo "sarray - variadic access"
$CMD -r$NRUNS -tsarray -avariadic &> mindex_sarray_variadic.dat
echo "sarray - vector access"
$CMD -r$NRUNS -tsarray -avector   &> mindex_sarray_vector.dat
echo "sarray - array access"
$CMD -r$NRUNS -tsarray -aarray   &> mindex_sarray_array.dat
echo "sarray - pointer access"
$CMD -r$NRUNS -tsarray -apointer   &> mindex_sarray_pointer.dat

echo "sarray view - variadic access"
$CMD -r$NRUNS -tsarray -v -avariadic &> mindex_sarray_view_variadic.dat
echo "sarray view - vector access"
$CMD -r$NRUNS -tsarray -v -avector   &> mindex_sarray_view_vector.dat
echo "sarray view - array access"
$CMD -r$NRUNS -tsarray -v -aarray   &> mindex_sarray_view_array.dat
