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

template<typename ATYPE> class inplace_arithmetic_benchmark
{
    private:
        ATYPE _array;
    public:
        inplace_arithmetic_benchmark(ATYPE &&a):
            _array(std::move(a))
        {}

        void add(typename ATYPE::value_type v)
        {
            _array += v;
        }

        void add(const ATYPE &a)
        {
            _array += a;
        }

        void sub(typename ATYPE::value_type v)
        {
            _array -= v;
        }

        void sub(const ATYPE &a)
        {
            _array -= a;
        }

        void mult(typename ATYPE::value_type v)
        {
            _array *= v;
        }

        void mult(const ATYPE &a)
        {
            _array *= a;
        }

        void div(typename ATYPE::value_type v)
        {
            _array /= v;
        }

        void div(const ATYPE &a)
        {
            _array /= a;
        }

};
