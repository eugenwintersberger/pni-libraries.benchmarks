/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: May 22, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <random>

#include <pni/core/type_info.hpp>
#include <pni/core/types.hpp>

using namespace pni::core;


template<typename CT,bool is_int,bool is_complex> class UniformDistribution;

//create integer data uniformly distributed
template<typename CT> class UniformDistribution<CT,true,false> 
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            CT container(n);

#ifndef NOCPPRAND
            std::mt19937_64 engine;
            std::uniform_int_distribution<> 
                dist(type_info<value_type>::min(),type_info<value_type>::max());
#endif

#ifdef NOFOREACH
            for(auto iter=container.begin();iter!=container.end();iter++)
            {
                value_type &v = *iter;
#else
            for(value_type &v: container)
            {
#endif
#ifdef NOCPPRAND
                v = value_type(1);
#else
                v = dist(engine);
#endif
            }

            return container;
        }
};

//create floating point uniform distribution
template<typename CT> class UniformDistribution<CT,false,false>
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            CT container(n);
#ifndef NOCPPRAND       
            std::mt19937_64 engine;
            std::uniform_real_distribution<> 
                dist(type_info<float32>::min(),type_info<float32>::max());
#endif

#ifdef NOFOREACH
            for(auto iter=container.begin();iter!=container.end();iter++)
            {
                value_type &v = *iter;
#else
            for(value_type &v: container)
            {
#endif
#ifdef NOCPPRAND
                v = value_type(1);
#else
                v = dist(engine);
#endif
            }

            return container;
        }
};

//create complex uniform distribution
template<typename CT> class UniformDistribution<CT,false,true>
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            typedef typename value_type::value_type base_type;
            CT container(n);

#ifndef NOCPPRAND       
            std::mt19937_64 engine;
            std::uniform_real_distribution<>
                dist(type_info<float32>::min(),
                     type_info<float32>::max());
#endif

#ifdef NOFOREACH
            for(auto iter = container.begin();iter!=container.end();iter++)
            {
                value_type &v = *iter;
#else
            for(value_type &v: container)
            {
#endif
#ifdef NOCPPRAND
                v = value_type(1,1);
#else
                v = value_type(dist(engine),dist(engine));
#endif
            }

            return container;
        }
};

class RandomDistribution
{
    public:
        template<typename CT> static CT uniform(size_t n)
        {
            return UniformDistribution<CT,
                                       type_info<typename CT::value_type>::is_integer,
                                       type_info<typename CT::value_type>::is_complex>
                                           ::create_data(n);
        }
};
