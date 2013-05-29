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
\brief multiindex pointer benchmark

Benchmark class for testing IO performance on a raw pointer useing a
multi-dimensional access pattern. 
\tparam T data type for which to allocate memory
*/
template<typename T> class multiindex_io_pointer
{
    private:
        T *_ptr;    //!< pointer to memory
        size_t _nx; //!< number of elements along the first dimension
        size_t _ny; //!< number of elements along the second dimension
        T _result;  //!< result buffer 
    public:
        //==================construtors========================================
        /*!
        \brief constructor
        
        Creates an instance of this benchmark by allocating nx x ny elements on
        the heap. 
        \param nx number of points in the first dimension
        \param ny number of points in the second dimension
        */
        multiindex_io_pointer(size_t nx,size_t ny):
            _ptr(new T[nx*ny]),
            _nx(nx),
            _ny(ny),
            _result(0)
        { }

        //---------------------------------------------------------------------
        //! copy constructor
        multiindex_io_pointer(const multiindex_io_pointer<T> &mip):
            _ptr(new T[mip._nx*mip._ny]),
            _nx(mip._nx),
            _ny(mip._ny),
            _result(mip._result)
        {
            for(size_t i=0;i<_nx*_ny;++i) _ptr[i] = mip._ptr[i]; 
        }

        //---------------------------------------------------------------------
        //! move constructor
        multiindex_io_pointer(multiindex_io_pointer<T> &&mip):
            _ptr(mip._ptr),
            _nx(mip._nx),
            _ny(mip._ny),
            _result(mip._result)
        {
            mip._ptr = nullptr;
            mip._nx = 0;
            mip._ny = 0;
        }

        //---------------------------------------------------------------------
        //! destructor
        ~multiindex_io_pointer()
        {
            if(_ptr) delete [] _ptr;
            _ptr = nullptr;
        }

        //=====================assignment operators============================
        //! copy assignment operator
        multiindex_io_pointer<T> &operator=(const multiindex_io_pointer<T> &mip)
        {
            if(this == &mip) return *this;

            if(_ptr) delete [] _ptr;

            _nx = mip._nx;
            _ny = mip._ny;
            _ptr = new T[_nx*_ny];
            _result = mip._result;

            return *this;
        }

        //---------------------------------------------------------------------
        //! move assignment operator
        multiindex_io_pointer<T> &operator=(multiindex_io_pointer<T> &&mip)
        {
            if(this == &mip) return *this;

            _ptr = mip._ptr;
            mip._ptr = nullptr;
            _nx  = mip._nx;
            mip._nx = 0;
            _ny  = mip._ny;
            mip._ny = 0;
            _result = mip._result;

            return *this;
        }

        //================public member functions==============================
        /*!
        \brief write benchmark

        Testing raw pointer write performance using a multindex access pattern 
        to address the element position and write data to it.
        */
        void write_data()
        {
            T index(0);

            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _ptr[i*_ny+j] = index++;

        }

        //---------------------------------------------------------------------
        /*!
        \brief read benchmark

        Testing raw pointer read performance using a multiindex access pattern
        to address the element position and read data from it.
        */
        void read_data()
        {
            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _result += _ptr[i*_ny+j];
        }


        //---------------------------------------------------------------------
        //! get the benchmark name
        string name() const
        {
            return string("Multi-index IO (Pointer) ")+
                   demangle_cpp_name(typeid(T*).name());
        }
            
};
