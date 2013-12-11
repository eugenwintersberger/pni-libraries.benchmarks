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

#include <pni/core/array_arithmetic.hpp>
#include "../common/data_generator.hpp"

template<typename ATYPE> class binary_arithmetic_benchmark
{
    private:
        shape_t _shape;
        ATYPE _a;
        ATYPE _b;
        ATYPE _c;
        ATYPE _d;
        ATYPE _e;
        ATYPE _f;
    public:
        binary_arithmetic_benchmark(const shape_t &s):
            _shape(s)
        {
            allocate(); 
        }

        void allocate()
        {
            typedef typename ATYPE::value_type value_type;
            typedef array_factory<ATYPE> factory_type;

            deallocate();

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

        }

        void deallocate()
        {
            _a = ATYPE();
            _b = ATYPE();
            _c = ATYPE();
            _d = ATYPE();
            _e = ATYPE();
            _f = ATYPE();
        }

        void add() { _c = _a + _b; }

        void sub() { _c = _a - _b; }


        void mult() { _c = _a * _b; }

        void div() { _c= _a/_b; }

        void all() { _c = (_a*_b) + (_d-_e)/_f; }

};
