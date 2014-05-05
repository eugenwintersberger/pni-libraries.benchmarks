//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniutils.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Feb 19, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/arrays.hpp>

#include "../common/data_generator.hpp"

using namespace pni::core;

template<typename ATYPE> 
class inplace_arithmetic_benchmark_ptr
{
    public:
        typedef ATYPE array_type;
        typedef typename array_type::value_type value_type;
        typedef array_factory<array_type> factory_type;
    private:
        shape_t _shape;
        
        array_type _a;
        array_type _b;
        value_type _s;
        value_type *_a_ptr;
        value_type *_b_ptr;
        size_t _size;
    public:
        inplace_arithmetic_benchmark_ptr(const shape_t &s):
            _shape(s)
        {
        }

        void allocate()
        {
            _a = factory_type::create(_shape);
            _b = factory_type::create(_shape);

            std::generate(_a.begin(),_a.end(),random_generator<value_type>());
            std::generate(_b.begin(),_b.end(),random_generator<value_type>());

            _s = random_generator<value_type>()();

            _a_ptr = const_cast<value_type*>(_a.data());
            _b_ptr = const_cast<value_type*>(_b.data());

            _size = _a.size();
        }

        void deallocate()
        {
            _a = ATYPE();
            _b = ATYPE();
            _s = value_type(0);

            _a_ptr = nullptr;
            _b_ptr = nullptr;
        }


        void add_scalar() { for(size_t i=0;i<_size;++i) _a_ptr[i] += _s; }

        void add_array() { for(size_t i=0;i<_size;++i) _a_ptr[i] += _b_ptr[i]; }

        void sub_scalar() { for(size_t i=0;i<_size;++i) _a_ptr[i] -= _s; }

        void sub_array() { for(size_t i=0;i<_size;++i) _a_ptr[i] -= _b_ptr[i]; }

        void mult_scalar() { for(size_t i=0;i<_size;++i) _a_ptr[i] *= _s; }

        void mult_array() { for(size_t i=0;i<_size;++i) _a_ptr[i] *= _b_ptr[i]; }

        void div_scalar() { for(size_t i=0;i<_size;++i) _a_ptr[i] /=_s; }

        void div_array() { for(size_t i=0;i<_size;++i) _a_ptr[i] /= _b_ptr[i];
        }

};
