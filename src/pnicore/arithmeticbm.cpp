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

#include <common/types.hpp>
#include "benchmark_runners.hpp"


int main(int argc,char **argv)
{
    //program configuration 
    configuration conf;
    
    conf.add_option(config_option<bool>("help","h",
                "show help text",false));
    conf.add_option(config_option<size_t>("nx","x",
                "channels along first dimension",4096));
    conf.add_option(config_option<size_t>("ny","y",
                "channels along second dimension",4096));
    conf.add_option(config_option<size_t>("nruns","r",
                "number of benchmark runs",1));
    conf.add_option(config_option<bool>("use-ptr","p",
                    "use raw pointer code",false));
    conf.add_option(config_option<bool>("binary","b",
                    "run binary arithmetics",false));
    conf.add_option(config_option<string>("logfile","l",
                "write to logfile instead of stdout"));
    conf.add_option(config_option<string>("atype",
                "a","array type (fixed, or dynamic","dynamic"));
    conf.add_option(config_option<bool>("fortran","f",
                "use Fortran 90 functions to do the job",false));
   
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
    auto array_type = conf.value<string>("atype");

    //get output stream
    std::ostream *ostream = &std::cout;
    if(conf.has_option("logfile"))
        ostream = new std::ofstream(conf.value<string>("logfile"));

    if(conf.value<bool>("binary"))
    {
        *ostream<<"#Binary Arithmetics"<<std::endl;
        //run single threaded binary benchmark
        if((conf.value<bool>("use-ptr"))&&(!conf.value<bool>("fortran")))
        {
            //with pointers
            if (array_type == "dynamic")
            {
                *ostream<<"#C++ ptr. dyn. arr.";
                *ostream<<std::endl;
                run_binary_benchmark<true,dynamic_array<float64>>(nruns,shape,*ostream);
            }
            else if(array_type == "fixed")
            {
                *ostream<<"#C++ ptr. fix. arr.";
                *ostream<<std::endl;
                run_binary_benchmark<true,fixed_dim_array<float64,2> >(nruns,shape,*ostream);
            }
        }
        else if(conf.value<bool>("fortran"))
        {
            *ostream<<"#Fortran";
            *ostream<<std::endl;
            run_binary_fortran_benchmark(nruns,nx,ny,*ostream);
        }
        else
        {
            //with operators
            if (array_type == "dynamic")
            {
                *ostream<<"#C++ exp. temp. dyn. arr.";
                *ostream<<std::endl;
                run_binary_benchmark<false,dynamic_array<float64>>(nruns,shape,*ostream);
            }
            else if(array_type == "fixed")
            {
                *ostream<<"#C++ exp. temp. fix. arr.";
                *ostream<<std::endl;
                run_binary_benchmark<false,fixed_dim_array<float64,2>>(nruns,shape,*ostream);
            }
        }
    }
    else
    {
        //run single threaded inplace benchmark
        if((conf.value<bool>("use-ptr"))&&(!conf.value<bool>("fortran")))
        {
            if(array_type == "dynamic")
                run_inplace_benchmark<true,dynamic_array<float64>>(nruns,shape,*ostream);
            else if(array_type == "fixed")
                run_inplace_benchmark<true,fixed_dim_array<float64,2>>(nruns,shape,*ostream);
        }            
        else if(conf.value<bool>("fortran"))
        {
            run_unary_fortran_benchmark(nruns,nx,ny,*ostream);
        }
        else
        {
            if(array_type == "dynamic")
                run_inplace_benchmark<false,dynamic_array<float64>>(nruns,shape,*ostream);
            else if(array_type == "fixed")
                run_inplace_benchmark<false,fixed_dim_array<float64,2>>(nruns,shape,*ostream);
        }            
    }

    return 0;
}
