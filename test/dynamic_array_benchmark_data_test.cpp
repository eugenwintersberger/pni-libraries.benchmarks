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
#include <common/array_benchmark_data.hpp>
#include <pni/core/arrays.hpp>
#include "common.hpp"

using DynamicArrays = boost::mpl::list<
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::uint8>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::int8>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::uint16>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::int16>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::uint32>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::int32>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::uint64>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::int64>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::float32>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::float64>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::float128>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::complex32>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::complex64>>,
ArrayBenchmarkData<pni::core::dynamic_array<pni::core::complex128>>,
ArrayBenchmarkData<pni::core::dynamic_array<std::string>>
>;


BOOST_AUTO_TEST_SUITE(BenchmarkCommonTest)

BOOST_AUTO_TEST_SUITE(DynamicArrayBenchmarkData)

BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction,T,DynamicArrays)
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

BOOST_AUTO_TEST_CASE_TEMPLATE(test_assignment,T,DynamicArrays)
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



//template<typename T>
//using farray_test = array_benchmark_data_test<fixed_dim_array<T,2>>;
//
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<uint8>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<int8>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<uint16>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<int16>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<uint32>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<int32>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<uint64>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<int64>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<float32>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<float64>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<float128>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<complex32>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<complex64>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<complex128>);
//CPPUNIT_TEST_SUITE_REGISTRATION(farray_test<string>);
//
//template<typename T>
//using sarray_test = array_benchmark_data_test<static_array<T,10,100>>;
//
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<uint8>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<int8>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<uint16>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<int16>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<uint32>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<int32>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<uint64>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<int64>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<float32>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<float64>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<float128>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<complex32>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<complex64>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<complex128>);
//CPPUNIT_TEST_SUITE_REGISTRATION(sarray_test<string>);
