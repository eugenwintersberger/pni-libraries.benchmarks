/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Dec 28, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/math/mt_inplace_arithmetics.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include <pni/core/config/library_config.hpp>

#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/benchmark_result.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>
#include <pni/core/benchmark/clock_timer.hpp>

#include "inplace_arithmetic_benchmark.hpp"
#include "inplace_arithmetic_benchmark_ptr.hpp"
#include "binary_arithmetic_benchmark.hpp"
#include "binary_arithmetic_benchmark_ptr.hpp"

using namespace pni::core;

typedef chrono_timer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

template<typename ATYPE,bool use_ptr_flag> struct inplace_benchmark_type;
template<typename ATYPE> struct inplace_benchmark_type<ATYPE,true>
{
    typedef inplace_arithmetic_benchmark_ptr<ATYPE> benchmark_type;
};

template<typename ATYPE> struct inplace_benchmark_type<ATYPE,false>
{
    typedef inplace_arithmetic_benchmark<ATYPE> benchmark_type;
};

//-----------------------------------------------------------------------------
template<typename ATYPE,bool use_ptr_flag> struct binary_benchmark_type;
template<typename ATYPE> struct binary_benchmark_type<ATYPE,true>
{
    typedef binary_arithmetic_benchmark_ptr<ATYPE> benchmark_type;
};

template<typename ATYPE> struct binary_benchmark_type<ATYPE,false>
{
    typedef binary_arithmetic_benchmark<ATYPE> benchmark_type;
};

//-----------------------------------------------------------------------------
std::ostream &print_result(std::ostream &stream,benchmark_runner bm)
{
    benchmark_result av = average(bm);
    benchmark_result error = standard_deviation(bm);

    float64 percent = (error.time()*100.)/av.time();

    stream<<std::scientific<<av.time()*1.e-9<<"\t(+-)"<<error.time()*1.e-9<<"\t"<<av.unit();
    stream<<"\t(+-)"<<std::fixed<<percent<<"%";
    return stream;
}

//-----------------------------------------------------------------------------
template<bool use_ptr_flag,typename ATYPE> 
void run_inplace_benchmark(size_t nruns,ATYPE &&a)
{
    //define benchmark type
    typedef typename inplace_benchmark_type<ATYPE,use_ptr_flag>::benchmark_type bm_t; 
    typedef typename ATYPE::value_type value_type;
    
    //run benchmarks
    benchmark_runner add_bm_scalar,mult_bm_scalar,div_bm_scalar,sub_bm_scalar;
    benchmark_runner add_bm_array,mult_bm_array,div_bm_array,sub_bm_array;

    //scalar benchmark functions
    benchmark_runner::function_t bm_function;

    //run array benchmarks
    ATYPE b(a.template shape<shape_t>());
    //setup benchmark
    bm_t benchmark(std::move(a));

    //run scalar benchmark functions
    bm_function = std::bind((void(bm_t::*)(value_type))&bm_t::add,benchmark,value_type(100));
    add_bm_scalar.run<bmtimer_t>(nruns,bm_function);
    
    bm_function = std::bind((void(bm_t::*)(value_type))&bm_t::sub,benchmark,10);
    sub_bm_scalar.run<bmtimer_t>(nruns,bm_function);

    bm_function = std::bind((void(bm_t::*)(value_type))&bm_t::div,benchmark,10);
    div_bm_scalar.run<bmtimer_t>(nruns,bm_function);

    bm_function = std::bind((void(bm_t::*)(value_type))&bm_t::mult,benchmark,1.23);
    mult_bm_scalar.run<bmtimer_t>(nruns,bm_function);

    
    std::fill(b.begin(),b.end(),100);
    bm_function = std::bind((void(bm_t::*)(const ATYPE&))&bm_t::add,
                             benchmark,std::cref(b));
    add_bm_array.run<bmtimer_t>(nruns,bm_function);

    std::fill(b.begin(),b.end(),10);
    bm_function = std::bind((void(bm_t::*)(const ATYPE&))&bm_t::sub,
                            benchmark,std::cref(b));
    sub_bm_array.run<bmtimer_t>(nruns,bm_function);

    std::fill(b.begin(),b.end(),10);
    bm_function = std::bind((void(bm_t::*)(const ATYPE&))&bm_t::div,
                            benchmark,std::cref(b));
    div_bm_array.run<bmtimer_t>(nruns,bm_function);

    std::fill(b.begin(),b.end(),1.23);
    bm_function = std::bind((void(bm_t::*)(const ATYPE&))&bm_t::mult,
                            benchmark,std::cref(b));
    mult_bm_array.run<bmtimer_t>(nruns,bm_function);

    //print benchmark results 

    std::cout<<"array <OP>= scalar"<<std::endl;
    std::cout<<"Inplace add:\t"; print_result(std::cout,add_bm_scalar); 
    std::cout<<std::endl;

    std::cout<<"Inplace sub:\t"; print_result(std::cout,sub_bm_scalar); 
    std::cout<<std::endl;

    std::cout<<"Inplace div:\t"; print_result(std::cout,div_bm_scalar); 
    std::cout<<std::endl;

    std::cout<<"Inplace mult:\t"; print_result(std::cout,mult_bm_scalar);
    std::cout<<std::endl;
    
    std::cout<<std::endl<<"array <OP>= array"<<std::endl;
    std::cout<<"Inplace add:\t"; print_result(std::cout,add_bm_array);
    std::cout<<std::endl;

    std::cout<<"Inplace sub:\t"; print_result(std::cout,sub_bm_array);
    std::cout<<std::endl;

    std::cout<<"Inplace div:\t"; print_result(std::cout,div_bm_array);
    std::cout<<std::endl;

    std::cout<<"Inplace mult:\t"; print_result(std::cout,mult_bm_array);
    std::cout<<std::endl;

}

//-----------------------------------------------------------------------------

template<typename ATYPE> void reset_array(ATYPE &a)
{
    std::fill(a.begin(),a.end(),typename ATYPE::value_type(0));
}

template<bool use_ptr_flag,typename ATYPE> 
void run_binary_benchmark(size_t nruns,ATYPE &a)
{
    //define benchmark type
    typedef typename binary_benchmark_type<ATYPE,use_ptr_flag>::benchmark_type bm_t; 

    benchmark_runner::function_t add_func,mult_func,div_func,sub_func,all_func;
    bm_t benchmark(a);

    //define benchmark functions
    add_func = std::bind(&bm_t::add,benchmark);
    sub_func = std::bind(&bm_t::sub,benchmark);
    div_func = std::bind(&bm_t::div,benchmark);
    mult_func = std::bind(&bm_t::mult,benchmark);
    all_func = std::bind(&bm_t::all,benchmark);
    
    //run benchmarks
    benchmark_runner add_bm,mult_bm,div_bm,sub_bm,all_bm;

    add_bm.run<bmtimer_t>(nruns,add_func);
    sub_bm.run<bmtimer_t>(nruns,sub_func);
    div_bm.run<bmtimer_t>(nruns,div_func);
    mult_bm.run<bmtimer_t>(nruns,mult_func);
    all_bm.run<bmtimer_t>(nruns,all_func);
    
    //print benchmark results 
    std::cout<<"c=a+b:           "; print_result(std::cout,add_bm)<<std::endl;
    std::cout<<"c=a-b:           "; print_result(std::cout,sub_bm)<<std::endl;
    std::cout<<"c=a/b:           "; print_result(std::cout,div_bm)<<std::endl;
    std::cout<<"c=a*b:           "; print_result(std::cout,mult_bm)<<std::endl;
    std::cout<<"c=a*b + (d-e)/f: "; print_result(std::cout,all_bm)<<std::endl;

}
//-----------------------------------------------------------------------------
int main(int argc,char **argv)
{
    //program configuration 
    configuration conf;
    
    conf.add_option(config_option<bool>("help","h",
                "show help text",false));
    conf.add_option(config_option<size_t>("nx","x",
                "channels along first dimension",1024));
    conf.add_option(config_option<size_t>("ny","y",
                "channels along second dimension",1024));
    conf.add_option(config_option<size_t>("nruns","r",
                "number of benchmark runs",1));
    conf.add_option(config_option<bool>("use-ptr","p",
                    "use raw pointer code",false));
    conf.add_option(config_option<bool>("binary","b",
                    "run binary arithmetics",false));
    conf.add_option(config_option<size_t>("nthreads","",
                    "number of threads",1));
   
    std::vector<string> args = cliargs2vector(argc,argv);
    parse(conf,args,true);

    if(conf.value<bool>("help"))
    {
        std::cerr<<conf<<std::endl;
        return 1;
    }


    //type definitions
    typedef numarray<darray<float64> > nf64array;
    typedef numarray<darray<float64>,mt_inplace_arithmetics,true> nf64array_mt;

    if(conf.value<size_t>("nthreads") == 1)
    {
        nf64array a(shape_t({conf.value<size_t>("nx"),conf.value<size_t>("ny")}));

        if(conf.value<bool>("binary"))
        {
            if(conf.value<bool>("use-ptr"))
                run_binary_benchmark<true>(conf.value<size_t>("nruns"),a);
            else
                run_binary_benchmark<false>(conf.value<size_t>("nruns"),a);
        }
        else
        {
            if(conf.value<bool>("use-ptr"))
                run_inplace_benchmark<true>(conf.value<size_t>("nruns"),std::move(a));
            else
                run_inplace_benchmark<false>(conf.value<size_t>("nruns"),std::move(a));
        }
    }
    else
    {
        pnicore_config.n_arithmetic_threads(conf.value<size_t>("nthreads"));
        if(conf.value<bool>("use-ptr"))
        {
            std::cerr<<"multithreading benchmarks do not support pointers!"<<std::endl;
            return 1;
        }

        //set the number of threads in the library configuration
        pnicore_config.n_arithmetic_threads(conf.value<size_t>("nthreads"));

        //allocate memory
        nf64array_mt a(shape_t({conf.value<size_t>("nx"),
                               conf.value<size_t>("ny")}));
        if(conf.value<bool>("binary"))
        {
            nf64array_mt b(a.shape<shape_t>());
            nf64array_mt c(a.shape<shape_t>());
            run_binary_benchmark<false>(conf.value<size_t>("nruns"),a);
        }
        else
            run_inplace_benchmark<false>(conf.value<size_t>("nruns"),std::move(a));
    }

    return 0;
}
