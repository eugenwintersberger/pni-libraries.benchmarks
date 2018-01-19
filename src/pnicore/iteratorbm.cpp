//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Jul 12, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///
#include <iostream>
#include <fstream>
#include <pni/core/arrays.hpp>
#include <pni/core/configuration.hpp>
#include "linear_io_pointer.hpp"
#include "linear_io_iterator.hpp"

#include <common/types.hpp>
#include <common/utils.hpp>
#include <common/array_benchmark_data.hpp>
#include <common/view_benchmark_data.hpp>

using namespace pni::core;

//define some benchmark types
using DArrayData = ArrayBenchmarkData<dynamic_array<float64>>;
using FArrayData = ArrayBenchmarkData<fixed_dim_array<float64,2>>;
using SArrayData = ArrayBenchmarkData<static_array<float64,512,512>>;
using DViewData = ViewBenchmarkData<dynamic_array<float64>>;
using FViewData = ViewBenchmarkData<fixed_dim_array<float64,2>>;
using SViewData = ViewBenchmarkData<static_array<float64,512,512>>;

using DArrayIteratorBenchmark = LinearIOIterator<DArrayData>;
using FArrayIteratorBenchmark = LinearIOIterator<FArrayData>;
using SArrayIteratorBenchmark = LinearIOIterator<SArrayData>;
using DViewIteratorBenchmark = LinearIOIterator<DViewData>;
using FViewIteratorBenchmark = LinearIOIterator<FViewData>;
using SViewIteratorBenchmark = LinearIOIterator<SViewData>;

using DArrayPointerBenchmark = LinearIOPointer<DArrayData>;
using FArrayPointerBenchmark = LinearIOPointer<FArrayData>;
using SArrayPointerBenchmark = LinearIOPointer<SArrayData>;


template<typename BMARKT> 
void run_benchmark(size_t nruns,const shape_t &shape,std::ostream &o)
{
    using BenchmarkType = BMARKT;

    BenchmarkRunners runners{{"write",benchmark_runner()},
                              {"read",benchmark_runner()}};

    BenchmarkType benchmark(shape);
    FunctionType allocate_data = std::bind(&BenchmarkType::allocate,&benchmark);
    FunctionType deallocate_data = std::bind(&BenchmarkType::deallocate,&benchmark);

    setup_benchmarks(runners,allocate_data,deallocate_data);

    BenchmarkFunctions funcs{
        {"write",std::bind(&BenchmarkType::write_data,&benchmark)},
        {"read",std::bind(&BenchmarkType::read_data,&benchmark)}};

    run_benchmarks(nruns,runners,funcs);
    write_result(runners,o);
}



int main(int argc,char **argv)
{
    configuration conf;

    conf.add_option(config_option<bool>("help","h","show help text",false));
    conf.add_option(config_option<size_t>("nx","x",
                "number of elements along the first dimension",size_t(512)));
    conf.add_option(config_option<size_t>("ny","y",
                "number of elements along the second dimension",size_t(512)));
    conf.add_option(config_option<size_t>("nruns","r",
                "number of runs",size_t(1)));
    conf.add_option(config_option<string>("logfile","l",
                "write data to logfile instead of stdout"));
    conf.add_option(config_option<string>("type","t",
                "container type: pointer,darray,farray,sarray","darray"));
    conf.add_option(config_option<bool>("view","v",
                "Access via the view",false));
    conf.add_option(config_option<bool>("ptr","p",
                "Access via pointer"));

    parse(conf,cliargs2vector(argc,argv));

    if(conf.value<bool>("help"))
    {
        std::cerr<<conf<<std::endl;
        return 1;
    }

    auto nruns = conf.value<size_t>("nruns");
    auto nx = conf.value<size_t>("nx");
    auto ny = conf.value<size_t>("ny");
    shape_t shape{nx,ny};

    //determine output stream
    std::ostream *ostream = &std::cout;
    if(conf.has_option("logfile"))
        ostream = new std::ofstream(conf.value<string>("logfile"));
   
    //run the benchmarks
    auto bm_type = conf.value<string>("type");

    *ostream<<"# Iterator Benchmark"<<std::endl;
    if(bm_type == "darray")
    {
        *ostream<<"# darray - ";
        if(conf.value<bool>("ptr") && !conf.value<bool>("view"))
        {
            *ostream<<"pointer access"<<std::endl;
            run_benchmark<DArrayPointerBenchmark>(nruns,shape,*ostream);
        }
        else if(conf.value<bool>("view"))
        {
            *ostream<<"iterator view access"<<std::endl;
            run_benchmark<DViewIteratorBenchmark>(nruns,shape,*ostream);
        }
        else
        {
            *ostream<<"iterator access"<<std::endl;
            run_benchmark<DArrayIteratorBenchmark>(nruns,shape,*ostream);
        }
    }
    else if(bm_type == "farray")
    {
        *ostream<<"# farray - ";
        if(conf.value<bool>("ptr")&& !conf.value<bool>("view"))
        {
            *ostream<<"pointer access"<<std::endl;
            run_benchmark<FArrayPointerBenchmark>(nruns,shape,*ostream);
        }
        else if(conf.value<bool>("view"))
        {
            *ostream<<"iterator view access"<<std::endl;
            run_benchmark<FViewIteratorBenchmark>(nruns,shape,*ostream);
        }
        else
        {
            *ostream<<"iterator access"<<std::endl;
            run_benchmark<FArrayIteratorBenchmark>(nruns,shape,*ostream);
        }
    }
    else if(bm_type == "sarray")
    {
        *ostream<<"# sarray - ";
        if(conf.value<bool>("ptr") && !conf.value<bool>("view"))
        {
            *ostream<<"pointer access"<<std::endl;
            run_benchmark<SArrayPointerBenchmark>(nruns,shape,*ostream);
        }
        else if(conf.value<bool>("view"))
        {
            *ostream<<"iterator view access"<<std::endl;
            run_benchmark<SViewIteratorBenchmark>(nruns,shape,*ostream);
        }
        else
        {
            *ostream<<"iterator access"<<std::endl;
            run_benchmark<SArrayIteratorBenchmark>(nruns,shape,*ostream);
        }
    }
    else
    {
        std::cerr<<"unknow storage container!"<<std::endl;
        return 1;
    }

    return 0;
}


