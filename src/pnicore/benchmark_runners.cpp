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

//-----------------------------------------------------------------------------
void run_binary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o)
{
    typedef benchmark_runner::function_t function_type;
   
    function_type allocate_data = std::bind(f90::allocate_data,int(nx),int(ny));
    function_type deallocate_data = std::bind(f90::deallocate_data);

    function_type add_func = std::bind(f90::binary_run_add);
    function_type div_func = std::bind(f90::binary_run_div);
    function_type mul_func = std::bind(f90::binary_run_mult);
    function_type sub_func = std::bind(f90::binary_run_sub);
    function_type all_func = std::bind(f90::binary_run_all);

    //define benchmark runners
    benchmark_runner add_bm,mult_bm,div_bm,sub_bm,all_bm;
    f90::allocate_data(int(nx),int(ny));
    
    //run the benchmarks
    add_bm.run<bmtimer_t>(nruns,add_func);
    sub_bm.run<bmtimer_t>(nruns,sub_func);
    div_bm.run<bmtimer_t>(nruns,div_func);
    mult_bm.run<bmtimer_t>(nruns,mul_func);
    all_bm.run<bmtimer_t>(nruns,all_func);
    f90::deallocate_data();

    //output result
    o<<"#c=a+b\tc=a-b\tc=a/b\tc=a*b\tc=a*b+(d-e)/f"<<std::endl;
    o<<std::scientific<<std::setprecision(16);
    for(auto add_iter = add_bm.begin(),sub_iter = sub_bm.begin(),
             div_iter = div_bm.begin(),mul_iter = mult_bm.begin(),
             all_iter = all_bm.begin();
        add_iter != add_bm.end();
        ++add_iter,++sub_iter,++div_iter,++mul_iter,++all_iter)
        o<<add_iter->time()<<"\t"<<sub_iter->time()<<"\t"<<
           div_iter->time()<<"\t"<<mul_iter->time()<<"\t"<<
           all_iter->time()<<std::endl;

}
