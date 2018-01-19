//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pni-benchmarks.
//
// pni-benchmarks is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pni-benchmarks is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pni-benchmarks.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: May 30, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <iostream>
#include <iomanip>
#include <map>

#include <common/types.hpp>
#include <common/utils.hpp>

#include "benchmark_type_selectors.hpp"

//!
//! \brief binary benchmark runners
//! 
//! This function creates the map with benchmarks for binary arithmetic 
//! benchmarks.
//! \return benchmark map with binary benchmark runners
//!
BenchmarkRunners create_binary_benchmarks();

//-----------------------------------------------------------------------------
//!
//! \brief set binary functions
//! 
//! Store binary benchmark functions in a map with appropriate names. 
//! 
//! \param add binary add function
//! \param sub binary subtract function
//! \param div binary division function
//! \param mult binary multiplication function
//! \param all more complex expression of binary operators
//! \return map with functions
//! 
BenchmarkFunctions create_binary_functions(const FunctionType &add,
                                        const FunctionType &sub,
                                        const FunctionType &div,
                                        const FunctionType &mult,
                                        const FunctionType &all);

//-----------------------------------------------------------------------------
//!
//! \brief create unary benchmarks
//! 
//! Returns a map with benchmark runners with a specific name. 
//! The return value is a map with runners for the different benchmarks 
//! which have to be performed for unary operations.
//! 
//! \return map with runners
//!
BenchmarkRunners create_unary_benchmarks();

//-----------------------------------------------------------------------------
//!
//! \brief create unary functions
//! 
//! Create a map with benchmark functions for unary benchmarks. 
//! 
//! \param add_array unary array addition
//! \param sub_array unary array subtraction
//! \param mult_array unary array multiplication
//! \param div_array unary array division
//! \param add_scalar unary array-scalar addition
//! \param sub_scalar unary array-scalar subtraction
//! \param mult_scalar unary array-scalar multiplication
//! \param div_scalar unary array-scalar division
//! \return map with functions
//!
BenchmarkFunctions create_unary_functions(const FunctionType &add_array,
                                          const FunctionType &sub_array,
                                          const FunctionType &mult_array,
                                          const FunctionType &div_array,
                                          const FunctionType &add_scalar,
                                          const FunctionType &sub_scalar,
                                          const FunctionType &mult_scalar,
                                          const FunctionType &div_scalar);


//-----------------------------------------------------------------------------
template<bool use_ptr_flag,typename ATYPE> 
void run_inplace_benchmark(size_t nruns,const pni::core::shape_t &shape,std::ostream &o)
{
    //define benchmark type
    using BenchmarkType = typename InplaceBenchmarkType<ATYPE,use_ptr_flag>::BenchmarkType;

    
    //run array benchmarks
    BenchmarkType benchmark(shape);


    FunctionType allocate_data = std::bind(&BenchmarkType::allocate,&benchmark);
    FunctionType deallocate_data = std::bind(&BenchmarkType::deallocate,&benchmark);

    //run benchmarks
    BenchmarkRunners runners = create_unary_benchmarks();
    setup_benchmarks(runners,allocate_data,deallocate_data);
    
    //create the benchmark functions
    BenchmarkFunctions functions = create_unary_functions(
    FunctionType(std::bind(&BenchmarkType::add_array,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::sub_array,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::mult_array,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::div_array,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::add_scalar,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::sub_scalar,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::mult_scalar,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::div_scalar,&benchmark)));


    run_benchmarks(nruns,runners,functions);

    //print benchmark results 
    write_result(runners,o);
}

//-----------------------------------------------------------------------------

//!
//! \brief run binary arithmetics benchmark
//! 
//! This template function runs the binary arithmetics benchmark. 
//! 
//! \tparam use_ptr_flag true if pointer version should be used
//! \tparam ATYPE array type
//! \param nruns number of runs 
//! \param a instance of ATYPE with initial data
//! \param o output stream for benchmark results
//!
template<
         bool use_ptr_flag,
         typename ATYPE
        > 
void run_binary_benchmark(size_t nruns,const pni::core::shape_t &shape,std::ostream &o)
{
    //define benchmark type
    using BenchmarkType = typename BinaryBenchmarkType<ATYPE,use_ptr_flag>::BenchmarkType;

    BenchmarkType benchmark(shape);

    FunctionType allocate_data = std::bind(&BenchmarkType::allocate,&benchmark);
    FunctionType deallocate_data = std::bind(&BenchmarkType::deallocate,&benchmark);

    BenchmarkRunners runners = create_binary_benchmarks();
    setup_benchmarks(runners,allocate_data,deallocate_data);
    //define benchmark functions
    BenchmarkFunctions funcs = create_binary_functions(
    FunctionType(std::bind(&BenchmarkType::add,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::sub,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::div,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::mult,&benchmark)),
    FunctionType(std::bind(&BenchmarkType::all,&benchmark)));

   
    run_benchmarks(nruns,runners,funcs);

    write_result(runners,o);
}

//-----------------------------------------------------------------------------
void run_binary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o);

//-----------------------------------------------------------------------------
void run_unary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o);
