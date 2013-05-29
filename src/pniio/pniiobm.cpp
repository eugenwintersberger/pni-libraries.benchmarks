/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jan 5, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <iostream>
#include <functional>
#include <chrono>
#include <fstream>
#include <pni/core/types.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>
#include <pni/core/benchmark/benchmark_runner.hpp>

#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include "benchmark_factory.hpp"
#include "file_io_benchmark.hpp"

using namespace pni::core;

void output_result(std::ostream &ostream,const benchmark_runner &r)
{
    ostream<<"#"<<r.begin()->unit()<<std::endl;
    for(auto iter=r.begin();iter!=r.end();++iter)
        ostream<<std::scientific<<iter->time()<<std::endl;
}

int main(int argc,char **argv)
{
    typedef chrono_timer<std::chrono::high_resolution_clock,
                        std::chrono::milliseconds> bm_timer_t;
    configuration config;
    //setup program configuration
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
    config.add_option(config_option<bool>("random-fill","f",
                      "fill array with random data",false));
                     
   
    //parse commmand line options 
    parse(config,cliargs2vector(argc,argv));
    if(config.value<bool>("help"))
    {
        std::cerr<<config<<std::endl;
        return 1;
    }

    //create the benchmark factory
    benchmark_factory factory(config.value<string>("output"),
                              config.value<size_t>("nx"),
                              config.value<size_t>("ny"),
                              config.value<size_t>("nframes"));

    //create the bechmark
    std::unique_ptr<file_io_benchmark> bmptr =
        factory.create(config.value<string>("type"),
                       config.value<string>("backend"),
                       config.value<bool>("random-fill"));

    //create the benchmark runner instance
    benchmark_runner runner;

    //set the benchmark function
    benchmark_runner::function_t f = std::bind(&file_io_benchmark::run,bmptr.get());
    //create the pre- and post-run functions
    benchmark_runner::function_t pre_run =
        std::bind(&file_io_benchmark::create,bmptr.get());
    benchmark_runner::function_t post_run = 
        std::bind(&file_io_benchmark::close,bmptr.get());

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
