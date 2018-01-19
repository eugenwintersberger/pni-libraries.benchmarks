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
#include <pni/io/nexus.hpp>
#include <h5cpp/hdf5.hpp>


class BenchmarkLog
{
  private:
    hdf5::node::Group _group;
    hdf5::node::Group _data_group;
    hdf5::node::Group _params_group;
  public:
    //! default constructor
    BenchmarkLog();

    //--------------------------------------------------------------------
    //! constructor
    BenchmarkLog(const hdf5::node::Group &g);

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
    void create_item(const std::string &name,const std::string &unit)
    {
      auto type = hdf5::datatype::create<T>();
      hdf5::dataspace::Simple dataspace{{0},{hdf5::dataspace::Simple::UNLIMITED}};

      hdf5::node::ChunkedDataset f(_data_group,name,type,dataspace,{1024});
      f.attributes.create<std::string>("units").write(unit);
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
    void append_data(const std::string &name,T value)
    {
      hdf5::node::Dataset f = _data_group[name];

      f.extent(0,1);
      hdf5::dataspace::Simple space = f.dataspace();
      hdf5::dataspace::Hyperslab selection{{space.size()-1},{1}};
      f.write(value,selection);
    }

    //--------------------------------------------------------------------
    template<typename T>
    void add_parameter(const std::string &name,T value,const std::string &unit)
    {
      auto type = hdf5::datatype::create<T>(value);
      hdf5::dataspace::Scalar space;

      hdf5::node::Dataset f(_params_group,name,type,space);
      f.write(value);
      f.attributes.create<std::string>("units").write(unit);
    }

};
