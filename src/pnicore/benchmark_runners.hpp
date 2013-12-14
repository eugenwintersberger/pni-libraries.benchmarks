/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pni-benchmarks.
 *
 * pni-benchmarks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pni-benchmarks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pni-benchmarks.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: May 30, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <iostream>
#include <iomanip>
#include <map>

#include <common/types.hpp>
#include <common/utils.hpp>

#include "benchmark_type_selectors.hpp"

/*!
\brief binary benchmark runners

This function creates the map with benchmarks for binary arithmetic benchmarks.
\return benchmark map with binary benchmark runners
*/
benchmark_runners create_binary_benchmarks();

//-----------------------------------------------------------------------------
/*!
\brief set binary functions

Store binary benchmark functions in a map with appropriate names. 

\param add binary add function
\param sub binary subtract function
\param div binary division function
\param mult binary multiplication function
\param all more complex expression of binary operators
\return map with functions
*/
benchmark_funcs create_binary_functions(const function_type &add,
                                        const function_type &sub,
                                        const function_type &div,
                                        const function_type &mult,
                                        const function_type &all);

//-----------------------------------------------------------------------------
/*!
\brief create unary benchmarks

Returns a map with benchmark runners with a specific name. 
The return value is a map with runners for the different benchmarks which have
to be performed for unary operations.

\return map with runners
*/
benchmark_runners create_unary_benchmarks();

//-----------------------------------------------------------------------------
/*!
\brief create unary functions

Create a map with benchmark functions for unary benchmarks. 

\param add_array unary array addition
\param sub_array unary array subtraction
\param mult_array unary array multiplication
\param div_array unary array division
\param add_scalar unary array-scalar addition
\param sub_scalar unary array-scalar subtraction
\param mult_scalar unary array-scalar multiplication
\param div_scalar unary array-scalar division
\return map with functions
*/
benchmark_funcs create_unary_functions(const function_type &add_array,
                                       const function_type &sub_array,
                                       const function_type &mult_array,
                                       const function_type &div_array,
                                       const function_type &add_scalar,
                                       const function_type &sub_scalar,
                                       const function_type &mult_scalar,
                                       const function_type &div_scalar);


//-----------------------------------------------------------------------------
template<bool use_ptr_flag,typename ATYPE> 
void run_inplace_benchmark(size_t nruns,const shape_t &shape,std::ostream &o)
{
    //define benchmark type
    typedef typename inplace_benchmark_type<ATYPE,use_ptr_flag>::benchmark_type 
                     benchmark_type; 
    
    //run array benchmarks
    benchmark_type benchmark(shape);


    function_type allocate_data = std::bind(&benchmark_type::allocate,&benchmark);
    function_type deallocate_data = std::bind(&benchmark_type::deallocate,&benchmark);

    //run benchmarks
    benchmark_runners runners = create_unary_benchmarks();
    setup_benchmarks(runners,allocate_data,deallocate_data);
    
    //create the benchmark functions
    benchmark_funcs functions = create_unary_functions(
    function_type(std::bind(&benchmark_type::add_array,&benchmark)),
    function_type(std::bind(&benchmark_type::sub_array,&benchmark)),
    function_type(std::bind(&benchmark_type::mult_array,&benchmark)),
    function_type(std::bind(&benchmark_type::div_array,&benchmark)),
    function_type(std::bind(&benchmark_type::add_scalar,&benchmark)),
    function_type(std::bind(&benchmark_type::sub_scalar,&benchmark)),
    function_type(std::bind(&benchmark_type::mult_scalar,&benchmark)),
    function_type(std::bind(&benchmark_type::div_scalar,&benchmark)));


    run_benchmarks(nruns,runners,functions);

    //print benchmark results 
    write_result(runners,o);
}

//-----------------------------------------------------------------------------

/*!
\brief run binary arithmetics benchmark

This template function runs the binary arithmetics benchmark. 

\tparam use_ptr_flag true if pointer version should be used
\tparam ATYPE array type
\param nruns number of runs 
\param a instance of ATYPE with initial data
\param o output stream for benchmark results
*/
template<bool use_ptr_flag,typename ATYPE> 
void run_binary_benchmark(size_t nruns,const shape_t &shape,std::ostream &o)
{
    //define benchmark type
    typedef typename binary_benchmark_type<ATYPE,use_ptr_flag>::benchmark_type 
                     benchmark_type; 

    benchmark_type benchmark(shape);

    function_type allocate_data = std::bind(&benchmark_type::allocate,&benchmark);
    function_type deallocate_data = std::bind(&benchmark_type::deallocate,&benchmark);

    benchmark_runners runners = create_binary_benchmarks();
    setup_benchmarks(runners,allocate_data,deallocate_data);
    //define benchmark functions
    benchmark_funcs funcs = create_binary_functions(
    function_type(std::bind(&benchmark_type::add,&benchmark)),
    function_type(std::bind(&benchmark_type::sub,&benchmark)),
    function_type(std::bind(&benchmark_type::div,&benchmark)),
    function_type(std::bind(&benchmark_type::mult,&benchmark)),
    function_type(std::bind(&benchmark_type::all,&benchmark)));

   
    run_benchmarks(nruns,runners,funcs);

    write_result(runners,o);
}

//-----------------------------------------------------------------------------
void run_binary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o);

void run_unary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o);
