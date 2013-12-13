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
#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include <algorithm>

#include <common/types.hpp>
#include <common/array_benchmark_data.hpp>

/*!
\brief provide array defaults 

This class provides methods that return the default parameters of different
array types.
*/
template<typename ATYPE> struct array_default_params
{
    typedef ATYPE array_type;

    static size_t rank() { return array_type().rank(); }

    static size_t size() { return array_type().size(); }
};


/*!
\brief test of the array_benchmark_data class

 */
template<typename ATYPE>
class array_benchmark_data_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(array_benchmark_data_test<ATYPE>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST_SUITE_END();
    private:
        typedef ATYPE array_type;
        typedef typename array_type::map_type     index_map_type;
        typedef typename array_type::storage_type storage_type;
        typedef typename array_type::value_type   value_type;
        typedef array_factory<array_type> factory_type;
        typedef array_benchmark_data<array_type> data_type;
        typedef array_default_params<array_type> default_params;
        std::vector<value_type> ref_data; //buffer with reference data
        ATYPE array;
        shape_t shape;

        

    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_assignment();
};

//------------------------------------------------------------------------------
template<typename ATYPE> void array_benchmark_data_test<ATYPE>::setUp() { }

//------------------------------------------------------------------------------
template<typename ATYPE> void array_benchmark_data_test<ATYPE>::tearDown() { }

//------------------------------------------------------------------------------
template<typename ATYPE> 
void array_benchmark_data_test<ATYPE>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //default construction
    data_type bm_data;
    CPPUNIT_ASSERT(bm_data.data().rank() == default_params::rank());
    CPPUNIT_ASSERT(bm_data.data().size() == default_params::size());

    //construction from shape
    shape_t shape{10,100};
    data_type bm_data_1(shape);
    CPPUNIT_ASSERT(bm_data_1.data().rank() == 2);
    CPPUNIT_ASSERT(bm_data_1.data().size() == 10*100);
    auto shape_1 = bm_data_1.data().template shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),shape_1.begin()));

    //copy construction
    data_type bm_data_2 = bm_data_1;
    CPPUNIT_ASSERT(bm_data_2.data().rank() == bm_data_1.data().rank());
    CPPUNIT_ASSERT(bm_data_2.data().size() == bm_data_1.data().size());
    auto shape_2 = bm_data_2.data().template shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape_1.begin(),shape_1.end(),shape_2.begin()));

    //move construction
    data_type bm_data_3 = std::move(bm_data_2);
    CPPUNIT_ASSERT(bm_data_3.data().rank() == bm_data_1.data().rank());
    CPPUNIT_ASSERT(bm_data_3.data().size() == bm_data_1.data().size());
    auto shape_3 = bm_data_3.data().template shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape_1.begin(),shape_1.end(),shape_3.begin()));
    CPPUNIT_ASSERT(bm_data_2.data().size() == default_params::size());
    CPPUNIT_ASSERT(bm_data_2.data().rank() == default_params::rank());

}

//-----------------------------------------------------------------------------
template<typename ATYPE>
void array_benchmark_data_test<ATYPE>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    shape_t shape{10,100};
    data_type bm_data(shape);

    //copy assignment
    data_type bm_data_1;
    bm_data_1 = bm_data;
    CPPUNIT_ASSERT(bm_data_1.data().rank() == bm_data.data().rank());
    CPPUNIT_ASSERT(bm_data_1.data().size() == bm_data.data().size());

    //move assignment
    data_type bm_data_2;
    bm_data_2 = std::move(bm_data_1);
    CPPUNIT_ASSERT(bm_data_1.data().rank() == default_params::rank());
    CPPUNIT_ASSERT(bm_data_1.data().size() == default_params::size());

    CPPUNIT_ASSERT(bm_data_2.data().rank() == bm_data.data().rank());
    CPPUNIT_ASSERT(bm_data_2.data().size() == bm_data.data().size());

}





