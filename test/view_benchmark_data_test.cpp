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
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "view_benchmark_data_test.hpp"


template<typename T> 
using dview_test = view_benchmark_data_test<dynamic_array<T>>;

CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<int64>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<complex128>);
CPPUNIT_TEST_SUITE_REGISTRATION(dview_test<string>);

template<typename T>
using fview_test = view_benchmark_data_test<fixed_dim_array<T,2>>;

CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<int64>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<complex128>);
CPPUNIT_TEST_SUITE_REGISTRATION(fview_test<string>);

template<typename T>
using sview_test = view_benchmark_data_test<static_array<T,10,100>>;

CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<int64>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<complex128>);
CPPUNIT_TEST_SUITE_REGISTRATION(sview_test<string>);
