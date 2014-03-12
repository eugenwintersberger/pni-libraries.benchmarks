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
 *  Created on: Oct 25, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <typeinfo>
#include <pni/core/utilities.hpp>
#include <pni/core/types.hpp>

#include <common/data_generator.hpp>

using namespace pni::core;

/*!
\brief linear IO pointer benchmark

This benchmark tests the IO performance of plain pointer access. It is thus a
good reference for other benchmarks using higher level data structures to store
data.
*/
template<typename DATA> class linear_io_pointer 
{
    public:
        typedef typename DATA::value_type value_type;
        typedef typename DATA::array_type array_type;
        typedef random_generator<value_type> generator_type;
    private:
        shape_t _shape;
        DATA        _data;
        value_type *_ptr;      //!< pointer to allocated memory
        value_type  _buffer;   //!< temporary result 
        size_t      _size;     //!< total size of elements
    public:
        //=================constructor and destructor==========================
        /*!
        \brief constructor

        Constructor for the benchmark. It allocates a pointer of type T to a
        memory region for n elements.
        \param n number of elements 
        */
        template<typename CTYPE> linear_io_pointer(const CTYPE &shape):
            _shape(shape),
            _data(shape),
            _ptr(const_cast<value_type*>(data(_data.data()))),
            _buffer(generator_type()()),
            _size(size(_data.data()))
        {}

        void allocate()
        {
            _data.allocate(_shape);
            _data.initialize();

            _ptr = const_cast<value_type*>(data(_data.data()));
            _size = size(_data.data());
            _buffer = generator_type()();
        }

        void deallocate()
        {
            _data.deallocate();
        }

        //=======================public member functions=======================
        /*!
        \brief write benchmark

        Benchmark the IO performance by writing data to all the elements of the
        allocated memory region. 
        */
        void write_data()
        {
            for(size_t i=0;i<_size;i++) _ptr[i] = _buffer;
        }

        //---------------------------------------------------------------------
        /*!
        \brief read benchmark

        Benchmark read performance by reading data from all the elements in the
        allocated memory region. 
        */
        void read_data()
        {
            for(size_t i=0;i<_size;i++) _buffer = _ptr[i];
        }

};
