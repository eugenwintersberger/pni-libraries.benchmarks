/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 12, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <iostream>
#include <fstream>
#include <chrono>
#include <ratio>
#include <ctime>
#include <pni/core/container_iterator.hpp>
#include <pni/core/dbuffer.hpp>
#include <pni/core/darray.hpp>
#include <pni/core/arrays.hpp>

#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/benchmark_result.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>

#include "linear_io_pointer_benchmark.hpp"
#include "linear_io_container_iterator.hpp"

using namespace pni::core;

template<typename CLKT,typename BMARKT> 
void run_benchmark(size_t nruns,const BMARKT &bmark,std::ostream &o)
{
    std::cout<<"Benchmark: "<<bmark.name()<<std::endl;
    std::cout<<"Timer: "<<CLKT::name<<std::endl;

    //create benchmark functions from the benchmark object
    benchmark_runner::function_t write_func,read_func;
    write_func = std::bind(&BMARKT::write_data,bmark);
    read_func  = std::bind(&BMARKT::read_data,bmark);

    benchmark_runner write_bm,read_bm;
    write_bm.run<CLKT>(nruns,write_func);
    read_bm.run<CLKT>(nruns,read_func);

    o<<"#write\tread"<<std::endl;
    for(auto witer = write_bm.begin(),
             riter = read_bm.begin();
        witer!=write_bm.end();
        ++witer,++riter)
        o<<std::scientific<<
           witer->time()<<"\t"<<
           riter->time()<<std::endl;
}


typedef chrono_timer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

int main(int argc,char **argv)
{
    configuration conf;

    conf.add_option(config_option<bool>("help","h","show help text",false));
    conf.add_option(config_option<size_t>("size","n",
                    "number of double elements to allocate",size_t(0)));
    conf.add_option(config_option<size_t>("nruns","r",
                    "number of runs",1));
    conf.add_option(config_option<string>("logfile","l",
                    "write data to logfile instead of stdout"));
    conf.add_option(config_option<string>("type","t",
                    "container type","dbuffer"));

    parse(conf,cliargs2vector(argc,argv));

    if(conf.value<bool>("help"))
    {
        std::cerr<<conf<<std::endl;
        return 1;
    }

    if(conf.value<size_t>("size")==0)
    {
        std::cerr<<"cannot allocate 0 MBytes of memory"<<std::endl;
        return 1;
    }

    //define container types
    typedef dbuffer<float64>          dbuffer_t;
    typedef darray<float64,dbuffer_t> darray_t;
    typedef numarray<darray_t>        narray_t;

    //define container benchmark types
    typedef linear_io_container_iterator<dbuffer_t> dbuffer_bm_t;
    typedef linear_io_container_iterator<darray_t>  darray_bm_t;
    typedef linear_io_container_iterator<narray_t>  narray_bm_t;
    typedef linear_io_pointer_benchmark<double>     ptr_bm_t;

    //obtain basic benchmark parameters
    size_t size = conf.value<size_t>("size");
    size_t nruns = conf.value<size_t>("nruns");
    //shape for array types
    shape_t shape{2,size/2};

    //determine output stream
    std::ostream *ostream = &std::cout;
    if(conf.has_option("logfile"))
    {
        ostream = new std::ofstream(conf.value<string>("logfile"));
    }
   
    //run the benchmarks
    if(conf.value<string>("type")=="ptr")
        run_benchmark<bmtimer_t>(nruns, ptr_bm_t(size),*ostream);
    else if(conf.value<string>("type")=="dbuffer")
        run_benchmark<bmtimer_t>(nruns,dbuffer_bm_t(dbuffer_t(size)),*ostream);
    else if(conf.value<string>("type")=="darray")
        run_benchmark<bmtimer_t>(nruns,darray_bm_t(darray_t(shape)),*ostream);
    else if(conf.value<string>("type")=="numarray")
        run_benchmark<bmtimer_t>(nruns,narray_bm_t(narray_t(shape)),*ostream);
    else
    {
        std::cerr<<"unknow storage container!"<<std::endl;
        return 1;
    }

    return 0;
}


