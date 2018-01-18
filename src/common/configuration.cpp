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

#include "configuration.hpp"

pni::core::configuration create_default_config()
{
  using namespace pni::core;
  configuration config;

  config.add_option(config_option<bool>("help","h",
                                        "show help text",false));
  config.add_option(config_option<bool>("logfile-overwrite","",
                                        "overwrite existing logfile",false));
  config.add_option(config_option<string>("logfile","l",
                                          "name of the logfile","benchmark.nxs"));
  config.add_option(config_option<size_t>("nruns","r",
                                          "number of benchmark_runs",size_t(1)));
  config.add_option(config_option<string>("entry","e",
                                          "Name of the entry in the logfile","benchmark"));

  return config;
}

//----------------------------------------------------------------------------
std::string cli_options_string(int argc,char **argv)
{
  std::string output;

  if(argc<2) return output;

  for(size_t i=1;i<argc;++i) output += " "+std::string(argv[i]);

  return output;
}
