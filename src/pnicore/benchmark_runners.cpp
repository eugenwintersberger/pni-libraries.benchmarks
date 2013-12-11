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

//-----------------------------------------------------------------------------
void plot_inplace_result(const arithmetic_runners &s,
                         const arithmetic_runners &a,
                         std::ostream &o)
{
    o<<"#A +=scalar\tA-=scalar\tA/=scalar\tA*=scalar\t"<<
       "A +=array \tA-=array \tA/=array \tA*=array"<<std::endl;

    for(auto as_iter = s.add.begin(),ss_iter = s.sub.begin(),
             ds_iter = s.div.begin(),ms_iter = s.mult.begin(),
             aa_iter = a.add.begin(),sa_iter = a.sub.begin(),
             da_iter = a.div.begin(),ma_iter = a.mult.begin();
        as_iter != s.add.end();
        ++as_iter,++ss_iter,++ds_iter,++ms_iter,
        ++aa_iter,++sa_iter,++da_iter,++ma_iter)
        o<<std::scientific<<
            as_iter->time()<<"\t"<<ss_iter->time()<<"\t"<<
            ds_iter->time()<<"\t"<<ms_iter->time()<<"\t"<<
            aa_iter->time()<<"\t"<<sa_iter->time()<<"\t"<<
            da_iter->time()<<"\t"<<ma_iter->time()<<std::endl;
    
}

//-----------------------------------------------------------------------------
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

void run_unary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o)
{


}
