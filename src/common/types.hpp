//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// benchmarks is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// benchmarks is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with benchmarks.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Dec 13, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once                

#include <chrono>
#include <map>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/benchmark.hpp>
#include <pni/core/configuration.hpp>

//!
//! \brief timer type for benchmarks 
//!
//! This is the common timer type used for all benchmarks. 
//! Nanoseconds should provide a sufficiently good time resolution for all 
//! kinds of benchmarks - even short ones.
//!
using TimerType =  pni::core::chrono_timer<std::chrono::high_resolution_clock,
                                           std::chrono::nanoseconds>;

//----------------------------------------------------------------------------
//!
//! \brief function type 
//! 
//! The common function type for benchmarks.
//!
using FunctionType =  pni::core::benchmark_runner::function_t;

//----------------------------------------------------------------------------
//! 
//! \brief benchmark runner map
//! 
//! Map holding an arbitrary number of benchmark runners which can be 
//! identified by a name (the key value of the mape). 
//! The benchmark runners execute the benchmarks and store the results. 
//! 
using BenchmarkRunners =  std::map<std::string,pni::core::benchmark_runner>;

//-----------------------------------------------------------------------------
//! 
//! \brief benchmark function map
//!
//! A map holding benchmark functions. Each function can be identified 
//! by a name (the key of the map). The intention is that for 
//! each benchmark key in benchmark_runners a key in benchmark_funcs exists.
//!
using BenchmarkFunctions =  std::map<std::string,FunctionType>;
