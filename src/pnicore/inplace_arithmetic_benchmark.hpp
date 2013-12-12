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
 *  Created on: Dev 28, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/arrays.hpp>

#include "../common/data_generator.hpp"

using namespace pni::core;

template<typename ATYPE> class inplace_arithmetic_benchmark
{
    public:
        typedef typename ATYPE::value_type value_type;
        typedef array_factory<ATYPE> factory_type;
    private:
        shape_t _shape;
        ATYPE _a;
        ATYPE _b;
        value_type _s;
    public:
        inplace_arithmetic_benchmark(const shape_t &s):
            _shape(s)
        {}

        void allocate()
        {
            _a = factory_type::create(_shape);
            _b = factory_type::create(_shape);

            std::generate(_a.begin(),_a.end(),random_generator<value_type>());
            std::generate(_b.begin(),_b.end(),random_generator<value_type>());

            _s = random_generator<value_type>()();
        }

        void deallocate()
        {
            _a = ATYPE();
            _b = ATYPE();
            _s = value_type(0);
        }


        void add_scalar() { _a += _s; }

        void add_array() { _a += _b; }

        void sub_scalar() { _a -= _s; }

        void sub_array() { _a -= _b; }

        void mult_scalar() { _a *= _s; }

        void mult_array() { _a *= _b; }

        void div_scalar() { _a /= _s; }

        void div_array() { _a /= _b; }

};
