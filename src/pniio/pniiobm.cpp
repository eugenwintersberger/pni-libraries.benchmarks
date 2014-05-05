//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jan 5, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iostream>
#include <functional>
#include <chrono>
#include <fstream>
#include <pni/core/types.hpp>
#include <pni/core/benchmark.hpp>
#include <pni/core/configuration.hpp>
#include "benchmark_factory.hpp"
#include "file_io_benchmark.hpp"

using namespace pni::core;

void output_result(std::ostream &ostream,const benchmark_runner &r)
{
    ostream<<"#"<<r.begin()->unit()<<std::endl;
    for(auto iter=r.begin();iter!=r.end();++iter)
        ostream<<std::scientific<<iter->time()<<std::endl;
}

configuration create_config()
{
    configuration config;
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<string>("backend","b",
                      "HDF5 (=hdf5) or PNIIO (=pniio) backend","pniio"));
    config.add_option(config_option<size_t>("nx","x",
                      "number of point along first dimension",1024));
    config.add_option(config_option<size_t>("ny","y",
                      "number of points along second dimension",1024));
    config.add_option(config_option<string>("type","t",
                      "data type to use for writing","uint8"));
    config.add_option(config_option<size_t>("nframes","n",
                      "number of frames to write per run",10));
    config.add_option(config_option<size_t>("nruns","r",
                      "number of runs to perform for the benchmark",1));
    config.add_option(config_option<string>("output","o",
                      "name of output file","pniiobm.h5"));
    config.add_option(config_option<string>("logfile","l",
                      "name of a logfile"));
    config.add_option(config_option<size_t>("split","s",
                "split size for files",size_t(0)));

    return config;
}

//----------------------------------------------------------------------------
//                  MAIN PROGRAM
//----------------------------------------------------------------------------
int main(int argc,char **argv)
{
    typedef chrono_timer<std::chrono::high_resolution_clock,
                        std::chrono::milliseconds> bm_timer_t;
    typedef benchmark_factory::pointer_type pointer_type;
    typedef benchmark_runner::function_t function_type;

    //
    configuration config = create_config();
   
    //parse commmand line options 
    parse(config,cliargs2vector(argc,argv));
    if(config.value<bool>("help"))
    {
        std::cerr<<config<<std::endl;
        return 1;
    }

    pointer_type bm_ptr;
    //create the benchmark instance
    try
    {
        bm_ptr = benchmark_factory::create(config.value<string>("type"),
                                           config.value<string>("backend"));
    }
    catch(key_error &error)
    {
        std::cerr<<error<<std::endl;
        return -1;
    }

    //now we have to configure the benchmark according to the CLI arguments 
    //passed by the user
    bm_ptr->nx(config.value<size_t>("nx"));
    bm_ptr->ny(config.value<size_t>("ny"));
    bm_ptr->nframes(config.value<size_t>("nframes"));
    bm_ptr->filename(config.value<string>("filename"));
    bm_ptr->split_size(config.value<size_t>("split"));


    //create the benchmark runner instance
    benchmark_runner runner;

    //set the benchmark function
    function_type f = std::bind(&file_io_benchmark::run,bm_ptr.get());
    //create the pre- and post-run functions
    function_type pre_run = std::bind(&file_io_benchmark::create,bm_ptr.get());
    function_type post_run = std::bind(&file_io_benchmark::close,bm_ptr.get());

    //set the pre and post run functions
    runner.prerun(pre_run);
    runner.postrun(post_run);
    //run the benchmark
    runner.run<bm_timer_t>(config.value<size_t>("nruns"),f);

    
    //create the output stream
    if(config.has_option("logfile"))
    {
        //open log file for writting
        std::ofstream logfile(config.value<string>("logfile").c_str());
        output_result(logfile,runner);
    }
    else
        output_result(std::cout,runner);

    return 0;
}
