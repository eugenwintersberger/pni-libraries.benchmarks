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

#include "inplace_arithmetic_benchmark.hpp"
#include "inplace_arithmetic_benchmark_ptr.hpp"
#include "binary_arithmetic_benchmark.hpp"
#include "binary_arithmetic_benchmark_ptr.hpp"

/*!
\brief select inplace benchmark type

This trait selects the inplace benchmark type depending on whether the pointer or
the array type should be used. This template must be specialized for pointer and
non-pointer benchmarks.
\tparam ATYPE array type
\tparam use_ptr_flag if true use pointer benchmark
*/
template<typename ATYPE,bool use_ptr_flag> struct inplace_benchmark_type;

/*!
\brief select pointer inplace benchmark

Selects the pointer pointer inplace benchmark type in case that the use_ptr_flag
is true.
\tparam ATYPE array type
*/
template<typename ATYPE> struct inplace_benchmark_type<ATYPE,true>
{
    //! inplace pointer benchmark type
    typedef inplace_arithmetic_benchmark_ptr<ATYPE> benchmark_type;
};

/*!
\brief select array inplace benchmark

Selects the array inplace benchmark type in the case that use_ptr_flag is false.
\tparam ATYPE array type
*/
template<typename ATYPE> struct inplace_benchmark_type<ATYPE,false>
{
    //! inplace array benchmark type
    typedef inplace_arithmetic_benchmark<ATYPE> benchmark_type;
};

//-----------------------------------------------------------------------------
/*!
\brief select the binary benchmark type

Select the binary benchmark type depending on the status of the use_ptr_flag
provided as the second template parameters. If the flag is true the pointer
benchmark type will be used. In case of false the array benchmark is used.
This class has to be specialized for each value of use_ptr_flag
\tparam ATYPE array type
\tparam use_ptr_flag boolean flag deciding which type to use
*/
template<typename ATYPE,bool use_ptr_flag> struct binary_benchmark_type;

/*!
\brief select binary pointer benchmark

Select the pointer type for binary benchmarks.
\tparam ATYPE array type
*/
template<typename ATYPE> struct binary_benchmark_type<ATYPE,true>
{
    //! binary pointer benchmark type
    typedef binary_arithmetic_benchmark_ptr<ATYPE> benchmark_type;
};

/*!
\brief select binary array benchmark

Select the binary array benchmark type.
\tparam ATYPE array type
*/
template<typename ATYPE> struct binary_benchmark_type<ATYPE,false>
{
    //! binary array benchmark type
    typedef binary_arithmetic_benchmark<ATYPE> benchmark_type;
};

