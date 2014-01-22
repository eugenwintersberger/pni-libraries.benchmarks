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
#include <pni/core/array_view.hpp>
#include <pni/core/service.hpp>

#include <common/data_generator.hpp>

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
    public:
        typedef ATYPE array_type;
        typedef array_view<array_type> view_type;
        typedef typename array_type::value_type value_type;
        typedef array_factory<array_type> factory_type;
        typedef random_generator<value_type> generator_type;
        typedef std::vector<size_t> vindex_type;
        typedef std::array<size_t,2> aindex_type;
    private:
        shape_t _shape;    //!< array shape
        size_t _nx;        //!< number of elements along the first dimension
        size_t _ny;        //!< number of elements along the second dimension
        array_type _array; //!< instance of the array
        view_type  _view;  //!< view on the entire array
        value_type *_ptr;  //!< pointer to the data
        value_type  _buffer; 
        vindex_type _vindex;
        aindex_type _aindex;
    public:
        //==================construtors========================================
        //! constructor
        multiindex_io_array(const shape_t &shape):
            _shape(shape),
            _nx(shape[0]),
            _ny(shape[1]),
            _array(factory_type::create(shape)),
            _view(_array(slice(0,_nx),slice(0,_ny))),
            _ptr(const_cast<value_type*>(_array.storage().data())),
            _buffer(generator_type()()),
            _vindex(2),
            _aindex()
        { }

        //---------------------------------------------------------------------
        void allocate()
        {
            _array = factory_type::create(_shape);
            std::generate(_array.begin(),_array.end(),random_generator<value_type>());

            _view = _array(slice(0,_nx),slice(0,_ny));
            _ptr = const_cast<value_type*>(_array.storage().data());

            _buffer = generator_type()();
        }

        void deallocate() {}

        //================public member functions==============================
        /*!
        \brief write benchmark

        Measures IO performance by writting data to each of the elements of the
        2D array. 
        */
        void variadic_write_array()
        {
            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _array(i,j) = _buffer;
        }
       
        //---------------------------------------------------------------------
        void pointer_write_array()
        {
            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _ptr[i*_ny+j] = _buffer;
        }

        //---------------------------------------------------------------------
        void vector_write_array()
        {
            for(_vindex[0]=0;_vindex[0]<_nx;++_vindex[0])
                for(_vindex[1]=0;_vindex[1]<_ny;++_vindex[1])
                    _array(_vindex) = _buffer;
        }
        
        //---------------------------------------------------------------------
        void array_write_array()
        {
            for(_aindex[0]=0;_aindex[0]<_nx;++_aindex[0])
                for(_aindex[1]=0;_aindex[1]<_ny;++_aindex[1])
                    _array(_aindex) = _buffer;
        }
        
        //---------------------------------------------------------------------
        void variadic_write_view()
        {
            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _view(i,j) = _buffer;
        }

        //---------------------------------------------------------------------
        void vector_write_view()
        {
            for(_vindex[0]=0;_vindex[0]<_nx;++_vindex[0])
                for(_vindex[1]=0;_vindex[1]<_ny;++_vindex[1])
                    _view(_vindex) = _buffer;
        }
        
        //---------------------------------------------------------------------
        void array_write_view()
        {
            for(_aindex[0]=0;_aindex[0]<_nx;++_aindex[0])
                for(_aindex[1]=0;_aindex[1]<_ny;++_aindex[1])
                    _view(_aindex) = _buffer;
        }

        //---------------------------------------------------------------------
        /*!
        \brief read benchmark

        Measures IO performance by reading data from each of the elements of the
        2D array.
        */
        void variadic_read_array()
        {
            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _buffer = _array(i,j);
        }
       
        //---------------------------------------------------------------------
        void pointer_read_array()
        {
            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _buffer = _ptr[i*_ny+j];
        }

        //---------------------------------------------------------------------
        void vector_read_array()
        {
            for(_vindex[0]=0;_vindex[0]<_nx;++_vindex[0])
                for(_vindex[1]=0;_vindex[1]<_ny;++_vindex[1])
                    _buffer = _array(_vindex);
        }
        
        //---------------------------------------------------------------------
        void array_read_array()
        {
            for(_aindex[0]=0;_aindex[0]<_nx;++_aindex[0])
                for(_aindex[1]=0;_aindex[1]<_ny;++_aindex[1])
                    _buffer = _array(_aindex);
        }
        
        //---------------------------------------------------------------------
        void variadic_read_view()
        {
            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _buffer = _view(i,j);
        }

        //---------------------------------------------------------------------
        void vector_read_view()
        {
            for(_vindex[0]=0;_vindex[0]<_nx;++_vindex[0])
                for(_vindex[1]=0;_vindex[1]<_ny;++_vindex[1])
                    _buffer = _view(_vindex);
        }
        
        //---------------------------------------------------------------------
        void array_read_view()
        {
            for(_aindex[0]=0;_aindex[0]<_nx;++_aindex[0])
                for(_aindex[1]=0;_aindex[1]<_ny;++_aindex[1])
                    _buffer = _view(_aindex);
        }

};

