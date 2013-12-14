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
#include <common/data_generator.hpp>

using namespace pni::core;

/*!
\brief IO bechmark for linear containers

This benchmark class provides IO benchmarks for containers storing data in a
linear sequence. Iterators which must be provided by the container types are
used to access the data in the container.
\tparam CTYPE container type used for benchmarking
*/
template<typename DATA> class linear_io_iterator
{
    public:
        typedef typename DATA::value_type value_type;
        typedef typename DATA::array_type array_type;
        typedef random_generator<value_type> generator_type;
    private:
        shape_t _shape;
        DATA data;
        value_type buffer;
    public:
        linear_io_iterator(const shape_t &s):
            _shape(s),
            data(_shape), 
            buffer(generator_type()()) 
        {}

        //---------------------------------------------------------------------
        void allocate()
        {
            data.allocate(_shape);
            data.initialize();

            buffer = generator_type()();
        }

        //---------------------------------------------------------------------
        void deallocate()
        {
            data.deallocate();
        }

        //================public member functions==============================
        /*!
        \brief write benchmark

        This benchmark can be used to obtain the write performance of the
        iterator provided by the container. The function runs through all the
        elements of the container and writes a number there.
        */
        void write_data()
        {
            for(auto &v: data.data()) v = buffer;
        }

        //---------------------------------------------------------------------
        /*!
        \brief read benchmark

        Use this benchmark to obtain read performance of the containers
        iterator. The function iterators over each element in the container and
        adds the values to a result variable. 
        */
        void read_data()
        {
            size_t index = 0;
            for(auto v: data.data()) buffer = v;
        }

};
