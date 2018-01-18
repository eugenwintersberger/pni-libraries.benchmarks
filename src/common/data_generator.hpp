//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pni benchmarks.
//
// PNI benchmarks is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// PNI benchmarks is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PNI benchmarks.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Dec 5, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <sstream>
#include <random>
#include <pni/core/types.hpp>
#include <boost/lexical_cast.hpp>


//=============we need different distributions for integer and float============
template<typename T,bool is_int> struct DistributionMap;

//------------distribution for integral types-----------------------------------
template<typename T> struct DistributionMap<T,true>
{
    using DistributionType = std::uniform_int_distribution<T>;
};

//------------------distribution for floating point types-----------------------
template<typename T> struct DistributionMap<T,false>
{
    using DistributionType = std::uniform_real_distribution<T>;
};

//=================the default generator=======================================
template<typename T> class RandomGenerator
{
    private:
        std::mt19937_64 _engine;
        typename DistributionMap<T,pni::core::type_info<T>::is_integer>::DistributionType _distribution;

    public:
        RandomGenerator(T a,T b):
            _engine(std::random_device()()),
            _distribution(a,b)
        {}

        RandomGenerator():
            _engine(std::random_device()()),
            _distribution(0.2*pni::core::type_info<T>::min(),
                          0.2*pni::core::type_info<T>::max())
        { 
        }

        T operator()()
        {
            return _distribution(_engine);
        }
};

//-----------------------------------------------------------------------------
template<typename T> class RandomGenerator<std::complex<T>>
{
    private:
        RandomGenerator<T> _real_generator;
        RandomGenerator<T> _imag_generator;
    public:
        RandomGenerator(T a,T b):
            _real_generator(a,b),
            _imag_generator(a,b)
        {}

        RandomGenerator():
            _real_generator(),
            _imag_generator()
        {}
        
        std::complex<T> operator()()
        {
            return std::complex<T>(_real_generator(),
                                   _imag_generator());
        }
};

//-----------------------------------------------------------------------------
template<> class RandomGenerator<std::string>
{
    private:
        RandomGenerator<unsigned long> _generator;
    public:
        RandomGenerator(unsigned long a,unsigned long b):
            _generator(a,b)
        {}

        RandomGenerator(){}

        string operator()()
        {
            return boost::lexical_cast<string>(_generator());
        }
};

    
