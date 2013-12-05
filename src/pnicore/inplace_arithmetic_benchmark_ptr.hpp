/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Feb 19, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

template<typename ATYPE> class inplace_arithmetic_benchmark_ptr
{
    private:
        ATYPE _array;
        typename ATYPE::value_type *_ptr;
        size_t _size;
    public:
        inplace_arithmetic_benchmark_ptr(ATYPE &&a):
            _array(std::move(a))
        {
            _ptr = const_cast<typename ATYPE::value_type *>
                   (_array.storage().data()); 
            _size = _array.size();
        }

        void add(typename ATYPE::value_type v)
        {
            for(size_t i=0;i<_size;++i) _ptr[i] += v;
        }

        void add(const ATYPE &a)
        {
            typedef typename ATYPE::value_type* ptr_t;
            ptr_t a_ptr = const_cast<ptr_t>(a.storage().data());

            for(size_t i=0;i<_size;++i)
                _ptr[i] += a_ptr[i];
        }


        void sub(typename ATYPE::value_type v)
        {
            for(size_t i=0;i<_size;++i) _ptr[i] -= v;
        }

        void sub(const ATYPE &a)
        {
            typedef typename ATYPE::value_type* ptr_t;
            ptr_t a_ptr = const_cast<ptr_t>(a.storage().data());

            for(size_t i=0;i<_size;++i)
                _ptr[i] -= a_ptr[i];
        }


        void mult(typename ATYPE::value_type v)
        {
            for(size_t i=0;i<_size;++i) _ptr[i] *= v;
        }

        void mult(const ATYPE &a)
        {
            typedef typename ATYPE::value_type* ptr_t;
            ptr_t a_ptr = const_cast<ptr_t>(a.storage().data());

            for(size_t i=0;i<_size;++i)
                _ptr[i] *= a_ptr[i];
        }

        void div(typename ATYPE::value_type v)
        {
            for(size_t i=0;i<_size;++i) _ptr[i] /=v;
        }

        void div(const ATYPE &a)
        {
            typedef typename ATYPE::value_type* ptr_t;
            ptr_t a_ptr = const_cast<ptr_t>(a.storage().data());

            for(size_t i=0;i<_size;++i)
                _ptr[i] /= a_ptr[i];
        }

};
