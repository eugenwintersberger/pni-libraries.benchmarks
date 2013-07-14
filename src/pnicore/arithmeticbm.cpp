/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Dec 28, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <iostream>
#include <fstream>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/math/mt_inplace_arithmetics.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include <pni/core/config/library_config.hpp>

#include "benchmark_runners.hpp"

using namespace pni::core;

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
    conf.add_option(config_option<string>("logfile","l",
                "write to logfile instead of stdout"));
   
    std::vector<string> args = cliargs2vector(argc,argv);
    parse(conf,args,true);

    if(conf.value<bool>("help"))
    {
        std::cerr<<conf<<std::endl;
        return 1;
    }

    //obtain basic benchmark parameters
    auto nx = conf.value<size_t>("nx");
    auto ny = conf.value<size_t>("ny");
    shape_t shape{nx,ny};
    size_t nruns = conf.value<size_t>("nruns");

    //get output stream
    std::ostream *ostream = &std::cout;
    if(conf.has_option("logfile"))
        ostream = new std::ofstream(conf.value<string>("logfile"));

    //type definitions
    typedef numarray<darray<float64> > nf64array;
    typedef numarray<darray<float64>,int,mt_inplace_arithmetics,true> nf64array_mt;

    if(conf.value<size_t>("nthreads") == 1)
    {
        nf64array a(shape);

        if(conf.value<bool>("binary"))
        {
            //run single threaded binary benchmark
            if(conf.value<bool>("use-ptr"))
                //with pointers
                run_binary_benchmark<true>(nruns,a,*ostream);
            else
                //with arrays
                run_binary_benchmark<false>(nruns,a,*ostream);
        }
        else
        {
            //run single threaded inplace benchmark
            if(conf.value<bool>("use-ptr"))
                //with pointers
                run_inplace_benchmark<true>(nruns,std::move(a),*ostream);
            else
                //with arrays
                run_inplace_benchmark<false>(nruns,std::move(a),*ostream);
        }
    }
    else
    {
        //no multithreaded testing with pointers - should be implemented later
        if(conf.value<bool>("use-ptr"))
        {
            std::cerr<<"multithreading benchmarks do not support pointers!"<<std::endl;
            return 1;
        }

        //set the number of threads given by the user
        pnicore_config.n_arithmetic_threads(conf.value<size_t>("nthreads"));
        //allocate memory
        nf64array_mt a(shape);
        if(conf.value<bool>("binary"))
        {
            //run multithreaded binary benchmark with arrays
            run_binary_benchmark<false>(nruns,a,*ostream);
        }
        else
            //run multithreaded inplace benchmark with arrays
            run_inplace_benchmark<false>(nruns,std::move(a),*ostream);
    }

    return 0;
}
