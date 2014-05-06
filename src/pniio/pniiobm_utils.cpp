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

#include "pniiobm_utils.hpp"

//----------------------------------------------------------------------------
configuration create_configuration()
{
    configuration config = create_default_config();
    config.add_option(config_option<string>("backend","b",
                      "HDF5 (=hdf5) or PNIIO (=pniio) backend","pniio"));
    config.add_option(config_option<size_t>("nx","x",
                      "number of point along first dimension",1024));
    config.add_option(config_option<size_t>("ny","y",
                      "number of points along second dimension",1024));
    config.add_option(config_option<string>("type","t",
                      "data type to use for writing","uint8"));
    config.add_option(config_option<size_t>("nframes","n",
                      "number of frames to write per run",10));
    config.add_option(config_option<string>("output","o",
                      "name of output file","pniiobm.h5"));
    config.add_option(config_option<size_t>("split","s",
                "split size for files",size_t(0)));

    return config;
}

//----------------------------------------------------------------------------
void write_parameters(benchmark_log &log,const configuration &config)
{
    log.add_parameter<size_t>("split_size",config.value<size_t>("split"),
                              "MByte");
    log.add_parameter<string>("output",config.value<string>("output"),"");
    log.add_parameter<size_t>("nframes",config.value<size_t>("nframes"),"1");
    log.add_parameter<string>("type_code",config.value<string>("type"),"1");
    log.add_parameter<size_t>("nx",config.value<size_t>("nx"),"1");
    log.add_parameter<size_t>("ny",config.value<size_t>("ny"),"1");
    log.add_parameter<string>("backend",config.value<string>("backend"),"");

}
