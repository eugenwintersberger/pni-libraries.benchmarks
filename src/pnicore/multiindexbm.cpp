//iterator benchmark

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
#include <utility>

#include <pni/core/arrays.hpp>
#include <pni/core/benchmark/benchmark_result.hpp>
#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>
#include <pni/core/benchmark/clock_timer.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>

#include "multiindex_io_pointer.hpp"
#include "multiindex_io_array.hpp"

using namespace pni::core;

//timer type for benchmark
typedef chrono_timer<std::chrono::high_resolution_clock,
                     std::chrono::nanoseconds> timer_type;

//benchmark function type
typedef benchmark_runner::function_t function_type;

template<typename BMARKT> void run_benchmark(size_t nruns,BMARKT &&bmark)
{
    //create benchmark functions from the benchmark object
    function_type write_func = std::bind(&BMARKT::write_data,&bmark);
    function_type read_func  = std::bind(&BMARKT::read_data,&bmark);

    benchmark_runner write_bm,read_bm;
    write_bm.run<timer_type>(nruns,write_func);
    read_bm.run<timer_type>(nruns,read_func);

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

//define som array types
typedef dynamic_array<float64> darray_type;
typedef fixed_dim_array<float64,2> farray_type;
typedef static_array<float64,500,500> sarray_type;

typedef array_factory<darray_type> dfactory_type;
typedef array_factory<farray_type> ffactory_type;
typedef array_factory<sarray_type> sfactory_type;

//darray multiindex benchmark type
typedef multiindex_io_array<darray_type>  darray_bm_type; 
//fixed dim multiindex benchmark type
typedef multiindex_io_array<farray_type>  farray_bm_type; 
//static array multiindex benchmark type
typedef multiindex_io_array<sarray_type>  sarray_bm_type;
//pointer access benchmark
typedef multiindex_io_pointer<float64>    pointer_bm_type;    



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
    shape_t shape{config.value<size_t>("nx"),config.value<size_t>("ny")};

    //-----------------------------run benchmarks------------------------------ 
    if(type=="ptr") 
        run_benchmark(nruns,pointer_bm_type(shape[0],shape[1]));
    else if(type == "darray")
        run_benchmark(nruns,darray_bm_type(dfactory_type::create(shape)));
    else if(type == "fdarray")
        run_benchmark(nruns,farray_bm_type(ffactory_type::create(shape)));
    else if(type == "sarray")
        run_benchmark(nruns,sarray_bm_type(sarray_type()));
    else
        std::cerr<<"Unknown benchmark type"<<std::endl;


    return 0;
}


