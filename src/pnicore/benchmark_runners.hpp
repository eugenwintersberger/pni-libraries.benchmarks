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

#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>

#include "benchmark_type_selectors.hpp"

using namespace pni::core;

//define the timer 
typedef chrono_timer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

//! benchmark function type
typedef benchmark_runner::function_t function_type;

//! map with an arbitrary number of benchmarks
typedef std::map<string,benchmark_runner> benchmark_runners;

//! map with benchmark functions
typedef std::map<string,function_type> benchmark_funcs;

//-----------------------------------------------------------------------------
/*!
\brief binary benchmark runners

This function creates the map with benchmarks for binary arithmetic benchmarks.
\return benchmark map with binary benchmark runners
*/
benchmark_runners create_binary_benchmarks();

benchmark_funcs create_binary_functions(const function_type &add,
                                        const function_type &sub,
                                        const function_type &div,
                                        const function_type &mult,
                                        const function_type &all);

benchmark_runners create_unary_benchmarks();

benchmark_funcs create_unary_functions(const function_type &add_array,
                                       const function_type &sub_array,
                                       const function_type &mult_array,
                                       const function_type &div_array,
                                       const function_type &add_scalar,
                                       const function_type &sub_scalar,
                                       const function_type &mult_scalar,
                                       const function_type &div_scalar);

//-----------------------------------------------------------------------------
/*!
\brief run binary benchmark 

Run a binary arithmetic benchmark.

*/
void run_benchmarks(size_t nruns,benchmark_runners &map,benchmark_funcs &funcs);


//-----------------------------------------------------------------------------
/*!
\brief setup binary runners

Setup the binary arithmetic runners with the appropriate pre- and postrun
functions. These function are basically responsible for memory reallocation and
initializiation before each run and cleaning up memory after each run.
\param pre pre-run function
\param post post-run function
\return instance of binary_arithmetic_runners 
*/
void setup_benchmarks(benchmark_runners &runners,const function_type &pre,
                      const function_type &post);

//-----------------------------------------------------------------------------
/*!
\brief write binary results
 
Writes the results for the binary arithmetic benchmark to an output stream. 
\param runners benchmark runners
\param o output stream
*/
void write_result(const benchmark_runners &runners, std::ostream &o);

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
