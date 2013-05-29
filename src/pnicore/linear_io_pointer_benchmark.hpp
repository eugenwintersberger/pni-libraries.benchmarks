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
#include <pni/core/service.hpp>
#include <pni/core/types.hpp>

using namespace pni::core;

/*!
\brief linear IO pointer benchmark

This benchmark tests the IO performance of plain pointer access. It is thus a
good reference for other benchmarks using higher level data structures to store
data.
*/
template<typename T> class linear_io_pointer_benchmark
{
    private:
        size_t _size; //!< number of element allocated for the benchmark
        T *_ptr;      //!< pointer to allocated memory
        T _result;    //!< temporary result 
    public:
        //=================constructor and destructor==========================
        /*!
        \brief constructor

        Constructor for the benchmark. It allocates a pointer of type T to a
        memory region for n elements.
        \param n number of elements 
        */
        linear_io_pointer_benchmark(size_t n):
            _size(n),
            _ptr(new T[n]),
            _result(0)
        {}

        //---------------------------------------------------------------------
        //! move constructor
        linear_io_pointer_benchmark(linear_io_pointer_benchmark<T> &&bm):
            _size(bm._size),
            _ptr(bm._ptr),
            _result(bm._result)
        {
            bm._size = 0;
            bm._ptr = nullptr;
            bm._result = T(0);
        }

        //---------------------------------------------------------------------
        //! copy constructor
        linear_io_pointer_benchmark(const linear_io_pointer_benchmark<T> &bm):
            _size(bm._size),
            _ptr(new T[_size]),
            _result(bm._result)
        {
            for(size_t i=0;i<_size;++i) _ptr[i] = bm._ptr[i];
        }

        //---------------------------------------------------------------------
        /*!
        \brief destructor

        Frees the memory allocated by the constructor.
        */
        ~linear_io_pointer_benchmark()
        {
            if(_ptr) delete [] _ptr;
            _ptr = nullptr;
        }

        //====================assignment operators=============================
        //! copy assignment operator
        linear_io_pointer_benchmark<T> &operator=(const
                linear_io_pointer_benchmark<T> &bm)
        {
            if(this == &bm) return *this;

            if(_ptr) delete [] _ptr;

            _size = bm._size;
            _ptr = new T[_size];
            for(size_t i=0;i<_size;++i) _ptr[i] = bm._ptr[i];
            _result = bm._result;
            return *this;
        }

        //---------------------------------------------------------------------
        //! move assignment operator
        linear_io_pointer_benchmark<T> &operator=(linear_io_pointer_benchmark<T> &&bm)
        {
            if(this == &bm) return *this;

            if(_ptr) delete [] _ptr;

            _size = bm._size; bm._size = 0;
            _ptr  = bm._ptr;  bm._ptr = nullptr;
            _result = bm._reslt; bm._result = T(0);
            return *this;
        }

        //=======================public member functions=======================
        /*!
        \brief write benchmark

        Benchmark the IO performance by writing data to all the elements of the
        allocated memory region. 
        */
        void write_data()
        {
            T index(0);
            for(size_t i=0;i<_size;i++) _ptr[i] = index++;
        }

        //---------------------------------------------------------------------
        /*!
        \brief read benchmark

        Benchmark read performance by reading data from all the elements in the
        allocated memory region. 
        */
        void read_data()
        {
            _result = T(0);
            for(size_t i=0;i<_size;i++) _result += _ptr[i];
        }

        //-----------------------------------------------------------------
        //! get benchmark name
        string name() const
        {
            return "Linear IO (Pointer) "+demangle_cpp_name(typeid(T*).name());
        }
};
