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

#include "types.hpp"
#include "data_generator.hpp"


template<typename ATYPE> class array_benchmark_data
{
    public:
        typedef ATYPE array_type;
        typedef typename array_type::value_type value_type;
        typedef array_factory<array_type> factory_type;
        typedef random_generator<value_type> generator_type;
    private:
        array_type _data;
    public:
        array_benchmark_data():_data() {}

        //---------------------------------------------------------------------
        template<typename CTYPE> 
        array_benchmark_data(const CTYPE &shape):
            _data(factory_type::template create(shape))
        {
            this->initialize();
        }

        //---------------------------------------------------------------------
        template<typename CTYPE> void allocate(const CTYPE &shape) 
        {
            _data = factory_type::template create(shape);
        }

        //---------------------------------------------------------------------
        void initialize()
        {
            std::generate(_data.begin(),_data.end(),generator_type());
        }

        //---------------------------------------------------------------------
        void deallocate() { _data = array_type(); }

        //---------------------------------------------------------------------
        array_type &data() { return _data; }
        
        //---------------------------------------------------------------------
        const array_type &data() const { return _data; }
    
};
