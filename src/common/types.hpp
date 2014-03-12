/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * benchmarks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * benchmarks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with benchmarks.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Dec 13, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once                


#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/benchmark.hpp>
#include <pni/core/configuration.hpp>

using namespace pni::core;

/*!
\brief timer type for benchmarks 

This is the common timer type used for all benchmarks. 
*/
typedef chrono_timer<std::chrono::high_resolution_clock,
                     std::chrono::nanoseconds> timer_type;

/*!
\brief function type 

The common function type for benchmarks.
*/
typedef benchmark_runner::function_t function_type;

//! map with an arbitrary number of benchmarks
typedef std::map<string,benchmark_runner> benchmark_runners;

//! map with benchmark functions
typedef std::map<string,function_type> benchmark_funcs;
