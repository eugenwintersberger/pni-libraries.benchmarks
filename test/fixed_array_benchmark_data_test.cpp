//
// (c) Copyright 2018 DESY
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Jan 18, 2018
//
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <iostream>
#include <common/types.hpp>
#include <common/array_benchmark_data.hpp>
#include <pni/core/arrays.hpp>
#include "common.hpp"

using FixedArrays = boost::mpl::list<
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::uint8,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::int8,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::uint16,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::int16,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::uint32,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::int32,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::uint64,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::int64,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::float32,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::float64,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::float128,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::complex32,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::complex64,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<pni::core::complex128,2>>,
ArrayBenchmarkData<pni::core::fixed_dim_array<std::string,2>>
>;


BOOST_AUTO_TEST_SUITE(BenchmarkCommonTest)

BOOST_AUTO_TEST_SUITE(FixedArrayBenchmarkData)

BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction,T,FixedArrays)
{

  //construction from shape
  pni::core::shape_t shape{10,100};
  T bm_data_1(shape);
  BOOST_CHECK_EQUAL(bm_data_1.data().rank(),2);
  BOOST_CHECK_EQUAL(bm_data_1.data().size(),10*100);
  auto shape_1 = bm_data_1.data().template shape<pni::core::shape_t>();
  BOOST_CHECK(std::equal(shape.begin(),shape.end(),shape_1.begin()));

  //copy construction
  T bm_data_2 = bm_data_1;
  BOOST_CHECK_EQUAL(bm_data_2.data().rank(),bm_data_1.data().rank());
  BOOST_CHECK_EQUAL(bm_data_2.data().size(),bm_data_1.data().size());
  auto shape_2 = bm_data_2.data().template shape<pni::core::shape_t>();
  BOOST_CHECK(std::equal(shape_1.begin(),shape_1.end(),shape_2.begin()));

  //move construction
  T bm_data_3 = std::move(bm_data_2);
  BOOST_CHECK_EQUAL(bm_data_3.data().rank(),bm_data_1.data().rank());
  BOOST_CHECK_EQUAL(bm_data_3.data().size(),bm_data_1.data().size());
  auto shape_3 = bm_data_3.data().template shape<pni::core::shape_t>();
  BOOST_CHECK(std::equal(shape_1.begin(),shape_1.end(),shape_3.begin()));
  BOOST_CHECK_EQUAL(bm_data_2.data().size(),ArrayDefaultParameters<typename T::ArrayType>::size());
  BOOST_CHECK_EQUAL(bm_data_2.data().rank(),ArrayDefaultParameters<typename T::ArrayType>::rank());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_assignment,T,FixedArrays)
{
  pni::core::shape_t shape{10,100};
  T bm_data(shape);

  //copy assignment
  T bm_data_1 = bm_data;
  BOOST_CHECK_EQUAL(bm_data_1.data().rank(),bm_data.data().rank());
  BOOST_CHECK_EQUAL(bm_data_1.data().size(),bm_data.data().size());

  //move assignment
  T bm_data_2 = std::move(bm_data_1);
  BOOST_CHECK_EQUAL(bm_data_1.data().rank(),ArrayDefaultParameters<typename T::ArrayType>::rank());
  BOOST_CHECK_EQUAL(bm_data_1.data().size(),ArrayDefaultParameters<typename T::ArrayType>::size());

  BOOST_CHECK_EQUAL(bm_data_2.data().rank(),bm_data.data().rank());
  BOOST_CHECK_EQUAL(bm_data_2.data().size(),bm_data.data().size());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

