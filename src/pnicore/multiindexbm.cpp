//iterator benchmark

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
#include <pni/core/container_iterator.hpp>
#include <pni/core/dbuffer.hpp>
#include <pni/core/darray.hpp>
#include <pni/core/arrays.hpp>

#include <pni/core/benchmark/benchmark_result.hpp>
#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>
#include <pni/core/benchmark/clock_timer.hpp>

#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>

#include "multiindex_io_pointer.hpp"
#include "multiindex_io_array.hpp"

#include <utility>
using namespace pni::core;

template<typename CLKT,typename BMARKT> 
void run_benchmark(size_t nruns,const BMARKT &bmark)
{
    std::cout<<bmark.name()<<std::endl;
    //create benchmark functions from the benchmark object
    benchmark_runner::function_t write_func,read_func;
    write_func = std::bind(&BMARKT::write_data,bmark);
    read_func  = std::bind(&BMARKT::read_data,bmark);

    benchmark_runner write_bm,read_bm;
    write_bm.run<CLKT>(nruns,write_func);
    read_bm.run<CLKT>(nruns,read_func);

    string write_unit = write_bm.begin()->unit();
    string read_unit = read_bm.begin()->unit();
    std::cout<<"#write ("<<write_unit<<")\tread ("<<read_unit<<")"<<std::endl;
    for(auto wit=write_bm.begin(),rit=read_bm.begin();
        wit!=write_bm.end() && rit != read_bm.end();
        ++wit,++rit)
    {
        std::cout<<wit->time()<<"\t"<<rit->time()<<std::endl;
    }
}


typedef chrono_timer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

int main(int argc,char **argv)
{
    typedef darray<double,dbuffer<double> > darray_t; //DArray type
    typedef sarray<double,5000,5000> sarray_t;
    typedef numarray<darray_t> ndarray_t;             //numerical array type
    typedef multiindex_io_array<darray_t> darray_bm_t;  //darray multiindex benchmark type
    typedef multiindex_io_array<ndarray_t> narray_bm_t; //ndarray multiindex benchmark type
    typedef multiindex_io_array<sarray_t> sarray_bm_t;
    typedef multiindex_io_pointer<double> ptr_bm_t;     //pointer muldiindex benchmark type

    //-------------------setup user configuration-----------------------------
    configuration config;
    config.add_option(config_option<string>("array-type","t",
                      "array type to be used","darray"));
    config.add_option(config_option<size_t>("nx","x",
                      "number of elements along first dimension",100));
    config.add_option(config_option<size_t>("ny","y",
                      "number of elements along second dimension",100));
    config.add_option(config_option<size_t>("nruns","r",
                      "number of runs",1));
    config.add_option(config_option<bool>("help","h",
                      "show program help",false));
                      

    parse(config,cliargs2vector(argc,argv));

    if(config.value<bool>("help"))
    {
        std::cerr<<"multindexbm - benchmark program to test performance of";
        std::cerr<<" multiindex data access."<<std::endl<<std::endl;
        std::cerr<<config<<std::endl;
        return 1;
    }

    string type = config.value<string>("array-type");
    size_t nruns = config.value<size_t>("nruns");
    size_t nx = config.value<size_t>("nx");
    size_t ny = config.value<size_t>("ny");
    std::cout<<"Array size: "<<nx<<" "<<ny<<std::endl;
    std::cout<<"allocating "<<nx*ny*sizeof(double)/1024/1024<<" MByte of memory!";
    std::cout<<std::endl;

    //-----------------------------run benchmarks------------------------------ 
    if(type=="ptr") run_benchmark<bmtimer_t>(nruns,ptr_bm_t(nx,ny));
    else if(type == "darray")
        run_benchmark<bmtimer_t>(nruns,darray_bm_t(darray_t(shape_t{nx,ny})));
    else if(type == "ndarray")
        run_benchmark<bmtimer_t>(nruns,narray_bm_t(ndarray_t(shape_t{nx,ny})));
    else if(type == "sarray")
        run_benchmark<bmtimer_t>(nruns,sarray_bm_t(sarray_t()));
    else
        std::cerr<<"Unknown benchmark type"<<std::endl;


    return 0;
}


