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
#pragma once                

#include "types.hpp"


//!
//! \brief run binary benchmark 
//! 
//! Run benchmarks. This function executes the runners stored in map with the
//! functions provided by funcs. Both are maps where the key of a runner must 
//! have a matching key in the function map providing the function object to 
//! run the benchmark for. 
//! 
//! \param nruns total number of runs
//! \param map map with runner instances
//! \param funcs map with function objects 
//!
void run_benchmarks(size_t nruns,benchmark_runners &map,benchmark_funcs &funcs);


//-----------------------------------------------------------------------------
//!
//! \brief setup binary runners
//! 
//! Setup the binary arithmetic runners with the appropriate pre- and postrun
//! functions. These function are basically responsible for memory reallocation 
//! and initializiation before each run and cleaning up memory after each run.
//! 
//! \param runners the benchmark runners
//! \param pre pre-run function
//! \param post post-run function
//!
void setup_benchmarks(benchmark_runners &runners,const function_type &pre,
                      const function_type &post);

//-----------------------------------------------------------------------------
//!
//! \brief write binary results
//!  
//! Writes the results for the binary arithmetic benchmark to an output stream. 
//! 
//! \param runners benchmark runners
//! \param o output stream
//!
void write_result(const benchmark_runners &runners, std::ostream &o);
