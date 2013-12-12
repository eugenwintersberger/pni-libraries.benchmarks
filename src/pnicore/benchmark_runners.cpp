/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: May 30, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "benchmark_runners.hpp"
#include "fortran_arithmeticbm.hpp"


void write_result(const benchmark_runners &runners, std::ostream &o)
{
    typedef benchmark_runner::const_iterator iterator_type;

    o<<"# ";
    for(auto runner: runners) o<<runner.first<<"\t";

    o<<std::endl;
    o<<std::scientific<<std::setprecision(16);

    std::vector<iterator_type> iterators;

    //generate a list of iterators
    iterator_type stop_iter;
    for(auto &runner: runners) 
    {
        iterators.push_back(runner.second.begin());
        stop_iter = runner.second.end();
    }

    //loop over each line 
    while(iterators.back() != stop_iter)
    {
        //loop over each column
        for(auto &iter: iterators) o<<iter++->time()<<"\t";

        o<<std::endl;
    }
}

//-----------------------------------------------------------------------------
void setup_benchmarks(benchmark_runners &runners,const function_type &pre,
                                         const function_type &post)
{
    for(auto &runner: runners)
    {
        runner.second.prerun(pre);
        runner.second.postrun(post);
    }
}

//-----------------------------------------------------------------------------
benchmark_runners create_binary_benchmarks()
{
    return benchmark_runners{{"c=a+b",benchmark_runner()},
                             {"c=a-b",benchmark_runner()},
                             {"c=a/b",benchmark_runner()},
                             {"c=a*b",benchmark_runner()},
                             {"c=a*b+(d-e)/f",benchmark_runner()}};
}

//-----------------------------------------------------------------------------
benchmark_runners create_unary_benchmarks()
{
    return benchmark_runners{{"a+=b",benchmark_runner()},
                             {"a*=b",benchmark_runner()},
                             {"a-=b",benchmark_runner()},
                             {"a/=b",benchmark_runner()},
                             {"a+=s",benchmark_runner()},
                             {"a*=s",benchmark_runner()},
                             {"a-=s",benchmark_runner()},
                             {"a/=s",benchmark_runner()}};

}

//-----------------------------------------------------------------------------
benchmark_funcs create_unary_functions(const function_type &add_array,
                                       const function_type &sub_array,
                                       const function_type &mult_array,
                                       const function_type &div_array,
                                       const function_type &add_scalar,
                                       const function_type &sub_scalar,
                                       const function_type &mult_scalar,
                                       const function_type &div_scalar)
{
    return benchmark_funcs{{"a+=b",add_array},
                           {"a*=b",mult_array},
                           {"a-=b",sub_array},
                           {"a/=b",div_array},
                           {"a+=s",add_scalar},
                           {"a*=s",mult_scalar},
                           {"a-=s",sub_scalar},
                           {"a/=s",div_scalar}};

}

//-----------------------------------------------------------------------------
benchmark_funcs create_binary_functions(const function_type &add,
                                        const function_type &sub,
                                        const function_type &div,
                                        const function_type &mult,
                                        const function_type &all)
{
    return benchmark_funcs{{"c=a+b",add},
                           {"c=a/b",div},
                           {"c=a*b",mult},
                           {"c=a-b",sub},
                           {"c=a*b+(d-e)/f",all}};
}
//-----------------------------------------------------------------------------
void run_benchmarks(size_t nruns,benchmark_runners &runners,benchmark_funcs &funcs)
{
    for(auto &runner: runners)
        runner.second.run<bmtimer_t>(nruns,funcs[runner.first]);
}

//-----------------------------------------------------------------------------
void run_binary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o)
{
    function_type allocate_data = std::bind(f90::allocate_data,int(nx),int(ny));
    function_type deallocate_data = std::bind(f90::deallocate_data);

    benchmark_runners runners = create_binary_benchmarks(); 
    setup_benchmarks(runners,allocate_data,deallocate_data);

    benchmark_funcs funcs = create_binary_functions(
                            function_type(std::bind(f90::binary_run_add)),
                            function_type(std::bind(f90::binary_run_div)),
                            function_type(std::bind(f90::binary_run_mult)),
                            function_type(std::bind(f90::binary_run_sub)),
                            function_type(std::bind(f90::binary_run_all)));

   
    run_benchmarks(nruns,runners,funcs);
    write_result(runners,o);
}

//-----------------------------------------------------------------------------
void run_unary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o)
{

    function_type allocate_data = std::bind(f90::allocate_data,int(nx),int(ny));
    function_type deallocate_data = std::bind(f90::deallocate_data);

    benchmark_runners runners = create_unary_benchmarks(); 
    setup_benchmarks(runners,allocate_data,deallocate_data);

    benchmark_funcs funcs = create_unary_functions(
            function_type(std::bind(f90::unary_run_add_array)),
            function_type(std::bind(f90::unary_run_sub_array)),
            function_type(std::bind(f90::unary_run_mult_array)),
            function_type(std::bind(f90::unary_run_div_array)),
            function_type(std::bind(f90::unary_run_add_scalar)),
            function_type(std::bind(f90::unary_run_sub_scalar)),
            function_type(std::bind(f90::unary_run_mult_scalar)),
            function_type(std::bind(f90::unary_run_div_scalar)));

   
    run_benchmarks(nruns,runners,funcs);
    write_result(runners,o);
}
