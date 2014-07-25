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

logfile::logfile():_file(),_root()
{

}

//----------------------------------------------------------------------------
logfile::logfile(const string &name,bool overwrite)
{
    //try to create a new file
    try
    {
        _file = nxfile::create_file(name,overwrite,0);
    }
    catch(...)
    {
        //if the creation of the new file fails try to open an existing file
        _file = nxfile::open_file(name,false);
    }

    _root = _file.root();

}

//----------------------------------------------------------------------------
benchmark_log logfile::create_log(const string &name,
                                  const string &program_name,
                                  const string &program_version,
                                  const string &program_config,
                                  const string &title,
                                  const string &description)
{
    nxgroup g = _root.create_group(name,"NXentry");
    g.create_group("data","NXdata");
    g.create_group("parameters","NXparameters");
    g.create_field<string>("experiment_description").write(description);
    g.create_field<string>("title").write(title);

    nxfield f = g.create_field<string>("program_name");
    f.write(program_name);
    f.attributes.create<string>("version").write(program_version);
    f.attributes.create<string>("configuration").write(program_config);

    return benchmark_log(g);
}
