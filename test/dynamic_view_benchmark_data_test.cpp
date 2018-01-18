/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of PNI libraries benchmark suite.
 *
 * PNI libraries benchmark suite is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 2 of the License,
 * or (at your option) any later version.
 *
 * PNI libraries benchmark suite is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * PNI libraries benchmark suite.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Dec 13, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <iostream>
#include <common/types.hpp>
#include <common/view_benchmark_data.hpp>
#include <pni/core/arrays.hpp>
#include "common.hpp"

using DynamicViews = boost::mpl::list<
ViewBenchmarkData<pni::core::dynamic_array<pni::core::uint8>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::int8>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::uint16>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::int16>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::uint32>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::int32>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::uint64>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::int64>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::float32>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::float64>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::float128>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::complex32>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::complex64>>,
ViewBenchmarkData<pni::core::dynamic_array<pni::core::complex128>>,
ViewBenchmarkData<pni::core::dynamic_array<std::string>>
>;


BOOST_AUTO_TEST_SUITE(BenchmarkCommonTest)

BOOST_AUTO_TEST_SUITE(DynamicViewBenchmarkData)

BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction,T,DynamicViews)
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
  BOOST_CHECK_EQUAL(bm_data_2.data().size(),ArrayDefaultParameters<typename T::ArrayType::storage_type>::size());
  BOOST_CHECK_EQUAL(bm_data_2.data().rank(),ArrayDefaultParameters<typename T::ArrayType::storage_type>::rank());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_assignment,T,DynamicViews)
{
  pni::core::shape_t shape{10,100};
  T bm_data(shape);

  //copy assignment
  T bm_data_1 = bm_data;
  BOOST_CHECK_EQUAL(bm_data_1.data().rank(),bm_data.data().rank());
  BOOST_CHECK_EQUAL(bm_data_1.data().size(),bm_data.data().size());

  //move assignment
  T bm_data_2 = std::move(bm_data_1);
  BOOST_CHECK_EQUAL(bm_data_1.data().rank(),ArrayDefaultParameters<typename T::ArrayType::storage_type>::rank());
  BOOST_CHECK_EQUAL(bm_data_1.data().size(),ArrayDefaultParameters<typename T::ArrayType::storage_type>::size());

  BOOST_CHECK_EQUAL(bm_data_2.data().rank(),bm_data.data().rank());
  BOOST_CHECK_EQUAL(bm_data_2.data().size(),bm_data.data().size());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

