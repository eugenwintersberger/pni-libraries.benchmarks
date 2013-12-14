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
#include "linear_io_pointer.hpp"
#include "linear_io_iterator.hpp"

#include <common/types.hpp>
#include <common/utils.hpp>
#include <common/array_benchmark_data.hpp>
#include <common/view_benchmark_data.hpp>


//define some benchmark types
typedef array_benchmark_data<dynamic_array<float64>> darray_data;
typedef array_benchmark_data<fixed_dim_array<float64,2>> farray_data;
typedef array_benchmark_data<static_array<float64,512,512>> sarray_data;
typedef view_benchmark_data<dynamic_array<float64>> dview_data;
typedef view_benchmark_data<fixed_dim_array<float64,2>> fview_data;
typedef view_benchmark_data<static_array<float64,512,512>> sview_data;

typedef linear_io_iterator<darray_data> darray_iterator_bm;
typedef linear_io_iterator<farray_data> farray_iterator_bm;
typedef linear_io_iterator<sarray_data> sarray_iterator_bm;
typedef linear_io_iterator<dview_data>  dview_iterator_bm;
typedef linear_io_iterator<fview_data>  fview_iterator_bm;
typedef linear_io_iterator<sview_data>  sview_iterator_bm;

typedef linear_io_pointer<darray_data> darray_pointer_bm;
typedef linear_io_pointer<farray_data> farray_pointer_bm;
typedef linear_io_pointer<sarray_data> sarray_pointer_bm;


template<typename BMARKT> 
void run_benchmark(size_t nruns,const shape_t &shape,std::ostream &o)
{
    typedef BMARKT benchmark_type;

    benchmark_runners runners{{"write",benchmark_runner()},
                              {"read",benchmark_runner()}};

    benchmark_type benchmark(shape);
    function_type allocate_data = std::bind(&benchmark_type::allocate,&benchmark);
    function_type deallocate_data = std::bind(&benchmark_type::deallocate,&benchmark);

    setup_benchmarks(runners,allocate_data,deallocate_data);

    benchmark_funcs funcs{
        {"write",std::bind(&benchmark_type::write_data,&benchmark)},
        {"read",std::bind(&benchmark_type::read_data,&benchmark)}};

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
            run_benchmark<darray_pointer_bm>(nruns,shape,*ostream);
        }
        else if(conf.value<bool>("view"))
        {
            *ostream<<"iterator view access"<<std::endl;
            run_benchmark<dview_iterator_bm>(nruns,shape,*ostream);
        }
        else
        {
            *ostream<<"iterator access"<<std::endl;
            run_benchmark<darray_iterator_bm>(nruns,shape,*ostream);
        }
    }
    else if(bm_type == "farray")
    {
        *ostream<<"# farray - ";
        if(conf.value<bool>("ptr")&& !conf.value<bool>("view"))
        {
            *ostream<<"pointer access"<<std::endl;
            run_benchmark<farray_pointer_bm>(nruns,shape,*ostream);
        }
        else if(conf.value<bool>("view"))
        {
            *ostream<<"iterator view access"<<std::endl;
            run_benchmark<fview_iterator_bm>(nruns,shape,*ostream);
        }
        else
        {
            *ostream<<"iterator access"<<std::endl;
            run_benchmark<farray_iterator_bm>(nruns,shape,*ostream);
        }
    }
    else if(bm_type == "sarray")
    {
        *ostream<<"# sarray - ";
        if(conf.value<bool>("ptr") && !conf.value<bool>("view"))
        {
            *ostream<<"pointer access"<<std::endl;
            run_benchmark<sarray_pointer_bm>(nruns,shape,*ostream);
        }
        else if(conf.value<bool>("view"))
        {
            *ostream<<"iterator view access"<<std::endl;
            run_benchmark<sview_iterator_bm>(nruns,shape,*ostream);
        }
        else
        {
            *ostream<<"iterator access"<<std::endl;
            run_benchmark<sarray_iterator_bm>(nruns,shape,*ostream);
        }
    }
    else
    {
        std::cerr<<"unknow storage container!"<<std::endl;
        return 1;
    }

    return 0;
}


