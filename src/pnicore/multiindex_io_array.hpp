/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Nov 30, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once                

#include <typeinfo>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/service.hpp>

using namespace pni::core;

/*!
\brief multiindex array benchmark

Benchmark for testing IO performance using the () operator of array types along
with multindices. This benchmark uses the variadic version of the () operator
provided by the array type used. This means that elements are indexed with 
\code
ATYPE array(...);

array(i,j) = 5.;

\endcode
The benchmark assumes a 2D array for the test.
\tparam ATYPE array type to run the test for
*/
template<typename ATYPE> class multiindex_io_array
{
    private:
        ATYPE _array;   //!< instance of the array
        shape_t _shape; //!< array shape
        //! result member variable
        typename ATYPE::value_type _result;
    public:
        //==================construtors========================================
        //! constructor
        multiindex_io_array(ATYPE &&array):
            _array(std::move(array)),
            _shape(_array.template shape<shape_t>())
        { }

        //================public member functions==============================
        /*!
        \brief write benchmark

        Measures IO performance by writting data to each of the elements of the
        2D array. 
        */
        void write_data()
        {
            typedef typename ATYPE::value_type value_t;
            value_t index(0);

            for(size_t i=0;i<_shape[0];++i)
                for(size_t j=0;j<_shape[1];++j)
                    _array(i,j) = index++;

        }

        //---------------------------------------------------------------------
        /*!
        \brief read benchmark

        Measures IO performance by reading data from each of the elements of the
        2D array.
        */
        void read_data()
        {
            _result = typename ATYPE::value_type(0);

            for(size_t i=0;i<_shape[0];++i)
                for(size_t j=0;j<_shape[1];++j)
                    _result += _array(i,j);
        }


        //---------------------------------------------------------------------
        //! get benchmark name
        string name() const
        {
            return string("Multiindex IO (variadic) ")+demangle_cpp_name(typeid(ATYPE).name());
        }
};

