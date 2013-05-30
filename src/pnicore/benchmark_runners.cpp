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


//-----------------------------------------------------------------------------
void plot_inplace_result(const arithmetic_runners &s,
                         const arithmetic_runners &a,
                         std::ostream &o)
{
    o<<"A +=scalar\tA-=scalar\tA/=scalar\tA*=scalar\t"<<
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
