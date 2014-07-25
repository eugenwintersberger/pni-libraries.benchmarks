//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of PNI libraries benchmark suite.
//
// PNI libraries benchmark suite is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 2 of the License,
// or (at your option) any later version.
//
// PNI libraries benchmark suite is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// PNI libraries benchmark suite.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: May 05, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once                

#include <map>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

class benchmark_log
{
    private:
        nxgroup _group;
        nxgroup _data_group;
        nxgroup _params_group;
    public:
        //! default constructor
        benchmark_log();

        //--------------------------------------------------------------------
        //! constructor
        benchmark_log(const nxgroup &g);
    
        //--------------------------------------------------------------------
        //!
        //! \brief create a new data item
        //! 
        //! This method creates a new data item in the log. 
        //! 
        //! \param name the logical name of the item
        //! \param unit the physical unit of the item
        //! \return instance of nxfield representing the data item
        //! 
        template<typename T>
        void create_item(const string &name,const string &unit)
        {
            nxfield f = _data_group.create_field<T>(name);
            f.attributes.create<string>("units").write(unit);
        }

        //--------------------------------------------------------------------
        //! 
        //! \brief append data to item
        //! 
        //! Append a new value to a data item
        //! 
        //! \param name the name of the data item
        //! 
        template<typename T> 
        void append_data(const string &name,T value)
        {
            nxfield f = _data_group[name];
            
            f.grow(0,1);
            f(f.size()-1).write(value);
        }

        //--------------------------------------------------------------------
        template<typename T> 
        void add_parameter(const string &name,T value,const string &unit)
        {
            nxfield f = _params_group.create_field<T>(name);
            f.write(value);
            f.attributes.create<string>("units").write(unit);
        }

};
