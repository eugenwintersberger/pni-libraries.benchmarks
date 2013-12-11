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

#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>

#include "benchmark_type_selectors.hpp"

using namespace pni::core;

//define the timer 
typedef chrono_timer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;


//create a scalar function
#define SFUNC(bmt,bmi,fname,argt,arg) \
    std::bind((void(bmt::*)(argt))&bmt::fname,bmi,argt(arg))

#define AFUNC(f,bmt,bmi,fname,a,atype,arg) \
    std::fill(a.begin(),a.end(),atype(arg)); \
    f =  std::bind((void(bmt::*)(const ATYPE&))&bmt::fname,bmi,std::cref(a))

/*!
\brief collate runners 

Collates several runners for arithmetic benchmarks. One runner dedicated for
each arithmetic operation. 
*/
struct arithmetic_runners
{
    benchmark_runner add;  //!< runner for addition benchmark
    benchmark_runner mult; //!< runner for multiplication benchmark
    benchmark_runner div;  //!< runner for division benchmark
    benchmark_runner sub;  //!< runner for subtraction benchmark

};

struct binary_arithmetic_runners
{
    benchmark_runner add;
    benchmark_runner sub;
    benchmark_runner div;
    benchmark_runner mult;
    benchmark_runner all;
};

//-----------------------------------------------------------------------------
/*! 
\brief plot inplace results

Write the benchmark results from inplace operations to a stream. 
\param s inplace scalar results
\param a inplace array results
\param o output stream
*/
void plot_inplace_result(const arithmetic_runners &s,
                         const arithmetic_runners &a,
                         std::ostream &o);

//-----------------------------------------------------------------------------
template<bool use_ptr_flag,typename ATYPE> 
void run_inplace_benchmark(size_t nruns,const shape_t &shape,std::ostream &o)
{
    //define benchmark type
    typedef ATYPE array_type;
    typedef typename inplace_benchmark_type<array_type,use_ptr_flag>::benchmark_type 
                     benchmark_type; 
    typedef typename array_type::value_type value_type;
    typedef benchmark_runner::function_t function_type;
    typedef array_factory<array_type> array_factory;
    
    //run benchmarks
    arithmetic_runners array_run,scalar_run;

    //scalar benchmark functions
    function_type bm_function;

    //run array benchmarks
    auto b = array_factory::create(shape);
    benchmark_type benchmark(array_factory::create(shape));

    //run scalar benchmark functions
    bm_function = SFUNC(benchmark_type,benchmark,add,value_type,100);
    scalar_run.add.run<bmtimer_t>(nruns,bm_function);
    
    bm_function = SFUNC(benchmark_type,benchmark,sub,value_type,10);
    scalar_run.sub.run<bmtimer_t>(nruns,bm_function);

    bm_function = SFUNC(benchmark_type,benchmark,div,value_type,10);
    scalar_run.div.run<bmtimer_t>(nruns,bm_function);

    bm_function = SFUNC(benchmark_type,benchmark,mult,value_type,1.23);
    scalar_run.mult.run<bmtimer_t>(nruns,bm_function);

    //run array benchmarks
    AFUNC(bm_function,benchmark_type,benchmark,add,b,value_type,100);
    array_run.add.run<bmtimer_t>(nruns,bm_function);

    AFUNC(bm_function,benchmark_type,benchmark,sub,b,value_type,10);
    array_run.sub.run<bmtimer_t>(nruns,bm_function);

    AFUNC(bm_function,benchmark_type,benchmark,div,b,value_type,10);
    array_run.div.run<bmtimer_t>(nruns,bm_function);

    AFUNC(bm_function,benchmark_type,benchmark,mult,b,value_type,1.23);
    array_run.mult.run<bmtimer_t>(nruns,bm_function);

    //print benchmark results 
    plot_inplace_result(scalar_run,array_run,o);
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
    typedef ATYPE array_type;
    typedef typename array_type::value_type value_type;
    typedef typename binary_benchmark_type<array_type,use_ptr_flag>::benchmark_type 
                     benchmark_type; 
    typedef benchmark_runner::function_t function_type;
    typedef array_factory<array_type> array_factory;

    function_type add_func,mult_func,div_func,sub_func,all_func;
    benchmark_type benchmark(array_factory::create(shape));

    //define benchmark functions
    add_func = std::bind(&benchmark_type::add,benchmark);
    sub_func = std::bind(&benchmark_type::sub,benchmark);
    div_func = std::bind(&benchmark_type::div,benchmark);
    mult_func = std::bind(&benchmark_type::mult,benchmark);
    all_func = std::bind(&benchmark_type::all,benchmark);
    
    //define benchmark runners
    benchmark_runner add_bm,mult_bm,div_bm,sub_bm,all_bm;

    //run the benchmarks
    add_bm.run<bmtimer_t>(nruns,add_func);
    sub_bm.run<bmtimer_t>(nruns,sub_func);
    div_bm.run<bmtimer_t>(nruns,div_func);
    mult_bm.run<bmtimer_t>(nruns,mult_func);
    all_bm.run<bmtimer_t>(nruns,all_func);

    //output result
    o<<"#c=a+b\tc=a-b\tc=a/b\tc=a*b\tc=a*b+(d-e)/f"<<std::endl;
    o<<std::scientific<<std::setprecision(16);
    for(auto add_iter = add_bm.begin(),sub_iter = sub_bm.begin(),
             div_iter = div_bm.begin(),mul_iter = mult_bm.begin(),
             all_iter = all_bm.begin();
        add_iter != add_bm.end();
        ++add_iter,++sub_iter,++div_iter,++mul_iter,++all_iter)
        o<<add_iter->time()<<"\t"<<sub_iter->time()<<"\t"<<
           div_iter->time()<<"\t"<<mul_iter->time()<<"\t"<<
           all_iter->time()<<std::endl;
}

//-----------------------------------------------------------------------------
void run_binary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o);
