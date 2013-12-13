/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of PNI libraries benchmark suite.
 *
 * PNI libraries benchmark suite is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 2 of the License,
 * or (at your option) any later version.
 *
 * PNI libraries benchmark suite is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * PNI libraries benchmark suite.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Dec 13, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once


/*!
\brief provide array defaults 

This class provides methods that return the default parameters of different
array types.
*/
template<typename ATYPE> struct array_default_params
{
    typedef ATYPE array_type;

    static size_t rank() { return array_type().rank(); }

    static size_t size() { return array_type().size(); }
};

