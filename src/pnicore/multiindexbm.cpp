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

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
#include <utility>
#include <pni/core/configuration.hpp>

#include <common/types.hpp>
#include <common/utils.hpp>

#include "multiindex_io_array.hpp"

using namespace pni::core;

//define som array types
using DynamicArray = dynamic_array<float64>;
using FixedDimArray = fixed_dim_array<float64,2>;
using StaticArray = static_array<float64,500,500>;


//darray multiindex benchmark type
using DynamicArrayBenchmark = MultiindexIOArray<DynamicArray>;
//fixed dim multiindex benchmark type
using FixedDimArrayBenchmark = MultiindexIOArray<FixedDimArray>;
//static array multiindex benchmark type
using StaticArrayBenchmark = MultiindexIOArray<StaticArray>;

template<typename BMARKT>
BenchmarkFunctions setup_funcs(BMARKT &benchmark,const string &access,bool view_flag)
{
    using Benchmark = BMARKT;

    if(view_flag)
    {
        std::cout<<" view - ";
        if(access == "variadic")
        {
            std::cout<<"variadic access"<<std::endl;
            return BenchmarkFunctions{
            {"write",std::bind(&Benchmark::variadic_write_view,&benchmark)},
            {"read",std::bind(&Benchmark::variadic_read_view,&benchmark)}};
        }
        else if(access == "vector")
        {
            std::cout<<"vector access"<<std::endl;
            return BenchmarkFunctions{
            {"write",std::bind(&Benchmark::vector_write_view,&benchmark)},
            {"read",std::bind(&Benchmark::vector_read_view,&benchmark)}};
        }
        else if(access == "array")
        {
            std::cout<<"array access"<<std::endl;
            return BenchmarkFunctions{
            {"write",std::bind(&Benchmark::array_write_view,&benchmark)},
            {"read",std::bind(&Benchmark::array_read_view,&benchmark)}};
        }
        else if(access == "pointer")
        {
            std::cerr<<"Pointer access for views not available!"<<std::endl;
            //need to throw an exception here
        }
    }
    else
    {
        std::cout<<" - ";
        if(access == "variadic")
        {
            std::cout<<"variadic access"<<std::endl;
            return BenchmarkFunctions{
            {"write",std::bind(&Benchmark::variadic_write_array,&benchmark)},
            {"read",std::bind(&Benchmark::variadic_read_array,&benchmark)}};
        }
        else if(access == "vector")
        {
            std::cout<<"vector access"<<std::endl;
            return BenchmarkFunctions{
            {"write",std::bind(&Benchmark::vector_write_array,&benchmark)},
            {"read",std::bind(&Benchmark::vector_read_array,&benchmark)}};
        }
        else if(access == "array")
        {
            std::cout<<"array access"<<std::endl;
            return BenchmarkFunctions{
            {"write",std::bind(&Benchmark::array_write_array,&benchmark)},
            {"read",std::bind(&Benchmark::array_read_array,&benchmark)}};
        }
        else if(access == "pointer")
        {
            std::cout<<"pointer access"<<std::endl;
            return BenchmarkFunctions{
            {"write",std::bind(&Benchmark::pointer_write_array,&benchmark)},
            {"read",std::bind(&Benchmark::pointer_read_array,&benchmark)}};
        }

    }
}

template<typename BMARKT> 
void run_benchmark(size_t nruns,const shape_t &shape,const string &access,
                   bool view_flag)
{
    using Benchmark = BMARKT;

    Benchmark benchmark(shape);
    FunctionType allocate_data = std::bind(&Benchmark::allocate,&benchmark);
    FunctionType deallocate_data = std::bind(&Benchmark::deallocate,&benchmark);
    
    BenchmarkRunners runners{{"write",benchmark_runner()},
                             {"read",benchmark_runner()}};

    BenchmarkFunctions funcs = setup_funcs(benchmark,access,view_flag);

    run_benchmarks(nruns,runners,funcs);
    
    write_result(runners,std::cout);
}




int main(int argc,char **argv)
{

    //-------------------setup user configuration-----------------------------
    configuration config;
    config.add_option(config_option<string>("array-type","t",
                      "array type to be used (sarray, farray, or darray)","darray"));
    config.add_option(config_option<size_t>("nx","x",
                      "number of elements along first dimension",500));
    config.add_option(config_option<size_t>("ny","y",
                      "number of elements along second dimension",500));
    config.add_option(config_option<size_t>("nruns","r",
                      "number of runs",1));
    config.add_option(config_option<bool>("help","h",
                      "show program help",false));
    config.add_option(config_option<string>("access","a",
                "how to access data: variadic, array, vector, pointer","variadic"));
    config.add_option(config_option<bool>("view","v",
                "use view instead of the array instance",false));

    parse(config,cliargs2vector(argc,argv));

    if(config.value<bool>("help"))
    {
        std::cerr<<"multindexbm - benchmark program to test performance of";
        std::cerr<<" multiindex data access."<<std::endl<<std::endl;
        std::cerr<<config<<std::endl;
        return 1;
    }

    auto type = config.value<string>("array-type");
    auto nruns = config.value<size_t>("nruns");
    auto access = config.value<string>("access");
    auto view_flag = config.value<bool>("view");
    shape_t shape{config.value<size_t>("nx"),config.value<size_t>("ny")};

    //-----------------------------run benchmarks------------------------------ 
    std::cout<<"# Multiindex data access"<<std::endl;
    if(type == "darray")
    {
        std::cout<<"# darray";
        run_benchmark<DynamicArrayBenchmark>(nruns,shape,access,view_flag);
    }
    else if(type == "farray")
    {
        std::cout<<"# farray";
        run_benchmark<FixedDimArrayBenchmark>(nruns,shape,access,view_flag);
    }
    else if(type == "sarray")
    {
        std::cout<<"# sarray";
        run_benchmark<StaticArrayBenchmark>(nruns,shape,access,view_flag);
    }
    else
        std::cerr<<"Unknown benchmark type"<<std::endl;


    return 0;
}


