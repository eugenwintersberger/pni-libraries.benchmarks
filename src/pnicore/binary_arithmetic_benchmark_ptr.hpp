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
 *  Created on: Feb 19, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "../common/data_generator.hpp"

template<typename ATYPE> class binary_arithmetic_benchmark_ptr
{
    public:
        typedef typename ATYPE::value_type value_type;
    private:
        shape_t _shape;
        ATYPE _a;
        ATYPE _b;
        ATYPE _c;
        ATYPE _d;
        ATYPE _e;
        ATYPE _f;
        size_t _size;
        value_type *_a_ptr;
        value_type *_b_ptr;
        value_type *_c_ptr;
        value_type *_d_ptr;
        value_type *_e_ptr;
        value_type *_f_ptr;
    public:
        binary_arithmetic_benchmark_ptr(const shape_t &s):
            _shape(s)
        {
            allocate();
        }
        
        void allocate()
        {
            typedef array_factory<ATYPE> factory_type;

            deallocate(); //to be on the safe side first deallocate memory

            _a = factory_type::create(_shape);
            _b = factory_type::create(_shape);
            _c = factory_type::create(_shape);
            _d = factory_type::create(_shape);
            _e = factory_type::create(_shape);
            _f = factory_type::create(_shape);

            std::generate(_a.begin(),_a.end(),random_generator<value_type>());
            std::generate(_b.begin(),_b.end(),random_generator<value_type>());
            std::generate(_c.begin(),_c.end(),random_generator<value_type>());
            std::generate(_d.begin(),_d.end(),random_generator<value_type>());
            std::generate(_e.begin(),_e.end(),random_generator<value_type>());
            std::generate(_f.begin(),_f.end(),random_generator<value_type>());
            
            _a_ptr = const_cast<value_type*>(_a.storage().data());
            _b_ptr = const_cast<value_type*>(_b.storage().data());
            _c_ptr = const_cast<value_type*>(_c.storage().data());
            _d_ptr = const_cast<value_type*>(_d.storage().data());
            _e_ptr = const_cast<value_type*>(_e.storage().data());
            _f_ptr = const_cast<value_type*>(_f.storage().data());
            _size = _a.size();

        }

        void deallocate()
        {
            _a = ATYPE();
            _b = ATYPE();
            _c = ATYPE();
            _d = ATYPE();
            _e = ATYPE();
            _f = ATYPE();
            _size = _a.size();
        }

        void add()
        {
            for(size_t i=0;i<_size;++i)
                _c_ptr[i] = _a_ptr[i] + _b_ptr[i];
        }

        void sub()
        {
            for(size_t i=0;i<_size;++i)
                _c_ptr[i] = _a_ptr[i] - _b_ptr[i];
        }


        void mult()
        {
            for(size_t i=0;i<_size;++i)
                _c_ptr[i] = _a_ptr[i] * _b_ptr[i];
        }

        void div()
        {
            for(size_t i=0;i<_size;++i)
                _c_ptr[i] = _a_ptr[i] / _b_ptr[i];
        }
        
        void all()
        {
            for(size_t i=0;i<_size;++i)
                _c_ptr[i] = _a_ptr[i]*_b_ptr[i] + (_d_ptr[i]-_e_ptr[i])/_f_ptr[i];
        }

};
