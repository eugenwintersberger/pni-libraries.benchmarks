/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * benchmarks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * benchmarks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with benchmarks.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Dec 13, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once                

#include "array_benchmark_data.hpp"


template<typename ATYPE> 
class view_benchmark_data : public array_benchmark_data<ATYPE>
{
    public:
        typedef typename ATYPE::view_type array_type;
        typedef typename ATYPE::value_type value_type; 
    private:
        typedef array_benchmark_data<ATYPE> base;
        array_type _view;


        //---------------------------------------------------------------------
        void update_view()
        {
            std::vector<slice> slices;
            auto shape = base::data().template shape<shape_t>();

            for(auto d: shape) slices.push_back(slice(0,d));

            _view = base::date()(slices);
        }
    public:

        //---------------------------------------------------------------------
        template<typename CTYPE> 
        view_benchmark_data(const CTYPE &shape):
            array_benchmark_data<ATYPE>(shape)
        {
            update_view();
        }

        //---------------------------------------------------------------------
        template<typename CTYPE> void allocate(const CTYPE &shape)
        {
            base::template allocate(shape);

            update_view();
        }

        //---------------------------------------------------------------------
        void deallocate()
        {
            base::deallocate();
            update_view();
        }

        //---------------------------------------------------------------------
        array_type &data() { return _view; }
        
        //---------------------------------------------------------------------
        const array_type &data() const { return _view; }

};
