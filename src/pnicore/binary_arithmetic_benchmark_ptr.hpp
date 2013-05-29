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

template<typename ATYPE> class binary_arithmetic_benchmark_ptr
{
    public:
        typedef typename ATYPE::value_type value_type;
    private:
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
        binary_arithmetic_benchmark_ptr(ATYPE &a):
            _a(a),_b(a),_c(a),
            _d(a),_e(a),_f(a),_size(a.size()),
            _a_ptr(const_cast<value_type*>(_a.storage().storage().ptr())),
            _b_ptr(const_cast<value_type*>(_b.storage().storage().ptr())),
            _c_ptr(const_cast<value_type*>(_c.storage().storage().ptr())),
            _d_ptr(const_cast<value_type*>(_d.storage().storage().ptr())),
            _e_ptr(const_cast<value_type*>(_e.storage().storage().ptr())),
            _f_ptr(const_cast<value_type*>(_f.storage().storage().ptr()))
        {
            //initialize the data 

            uniform_distribution<typename ATYPE::value_type> random_dist;

            auto a_iter = _a.begin();
            auto b_iter = _b.begin();
            auto c_iter = _c.begin();
            auto d_iter = _d.begin();
            auto e_iter = _e.begin();
            auto f_iter = _f.begin();

            for(;a_iter!=_a.end();)
            {
                *(a_iter++) = random_dist();
                *(b_iter++) = random_dist();
                *(c_iter++) = random_dist();
                *(d_iter++) = random_dist();
                *(e_iter++) = random_dist();
                *(f_iter++) = random_dist();
            }
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
