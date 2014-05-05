//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of PNI libraries benchmark suite.
//
// PNI libraries benchmark suite is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 2 of the License,
// or (at your option) any later version.
//
// PNI libraries benchmark suite  is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// PNI libraries benchmark suite.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Dec 13, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iostream>
#include <iomanip>
#include "utils.hpp"

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
void run_benchmarks(size_t nruns,benchmark_runners &runners,benchmark_funcs &funcs)
{
    for(auto &runner: runners)
        runner.second.run<timer_type>(nruns,funcs[runner.first]);
}
