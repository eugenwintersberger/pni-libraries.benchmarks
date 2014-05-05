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
#include <pni/core/types.hpp>
#include <boost/lexical_cast.hpp>

#ifdef NOCPPRAND
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/mersenne_twister.hpp>
#else
#include <random>
#endif

using namespace pni::core;

//=============we need different distributions for integer and float============
template<typename T,bool is_int> struct distribution_map;

//------------distribution for integral types-----------------------------------
template<typename T> struct distribution_map<T,true>
{
#ifdef NOCPPRAND
    typedef boost::uniform_int<T> distribution_type;
#else
    typedef std::uniform_int_distribution<T> distribution_type;
#endif
};

//------------------distribution for floating point types-----------------------
template<typename T> struct distribution_map<T,false>
{
#ifdef NOCPPRAND
    typedef boost::uniform_real<T> distribution_type;
#else
    typedef std::uniform_real_distribution<T> distribution_type;
#endif
};

//=================the default generator=======================================
template<typename T> class random_generator
{
    private:
#ifdef NOCPPRAND
        boost::mt19937 _engine;
#else
        std::mt19937_64 _engine;
#endif
        typename distribution_map<T,type_info<T>::is_integer>::distribution_type _distribution;

    public:
        random_generator(T a,T b):
            _engine(std::random_device()()),
            _distribution(a,b)
        {}

        random_generator():
            _engine(std::random_device()()),
            _distribution(0.2*type_info<T>::min(),0.2*type_info<T>::max())
        { 
        }

        T operator()()
        {
            return _distribution(_engine);
        }
};

//-----------------------------------------------------------------------------
template<typename T> class random_generator<std::complex<T>>
{
    private:
        random_generator<T> _real_generator;
        random_generator<T> _imag_generator;
    public:
        random_generator(T a,T b):
            _real_generator(a,b),
            _imag_generator(a,b)
        {}

        random_generator():
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
template<> class random_generator<string>
{
    private:
        random_generator<unsigned long> _generator;
    public:
        random_generator(unsigned long a,unsigned long b):
            _generator(a,b)
        {}

        random_generator(){}

        string operator()()
        {
            return boost::lexical_cast<string>(_generator());
        }
};

    
