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

#include "logfile.hpp"
#include <pni/io/nexus.hpp>

LogFile::LogFile():_file(),_root()
{

}

//----------------------------------------------------------------------------
LogFile::LogFile(const std::string &name,bool overwrite)
{
  //try to create a new file
  try
  {
    if(overwrite)
      _file = hdf5::file::create(name,hdf5::file::AccessFlags::TRUNCATE);
    else
      _file = hdf5::file::create(name);
  }
  catch(...)
  {
    //if the creation of the new file fails try to open an existing file
    _file = hdf5::file::open(name,hdf5::file::AccessFlags::READWRITE);
  }

  _root = _file.root();

}

//----------------------------------------------------------------------------
BenchmarkLog LogFile::create_log(const std::string &name,
                                 const std::string &program_name,
                                 const std::string &program_version,
                                 const std::string &program_config,
                                 const std::string &title,
                                 const std::string &description)
{
  using namespace hdf5::node;
  using namespace pni::io;
  Group g = nexus::BaseClassFactory::create(_root,name,"NXentry");
  nexus::BaseClassFactory::create(g,"data","NXdata");
  nexus::BaseClassFactory::create(g,"parameters","NXparameters");

  auto string_type = hdf5::datatype::create<std::string>();
  hdf5::dataspace::Scalar space;
  Dataset(g,"experiment_description",string_type,space).write(description);
  Dataset(g,"title",string_type,space).write(title);

  Dataset f(g,"program_name",string_type,space);
  f.write(program_name);
  f.attributes.create<std::string>("version").write(program_version);
  f.attributes.create<std::string>("configuration").write(program_config);

  return BenchmarkLog(g);
}
