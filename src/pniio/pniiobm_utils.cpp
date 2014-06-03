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

//----------------------------------------------------------------------------
benchmark_runner create_runner(const pointer_type &ptr)
{
    benchmark_runner runner;

    //create the pre- and post-run functions
    function_type pre_run = std::bind(&file_io_benchmark::create,ptr.get());
    function_type post_run = std::bind(&file_io_benchmark::close,ptr.get());

    //set the pre and post run functions
    runner.prerun(pre_run);
    runner.postrun(post_run);

    return runner;
}

//----------------------------------------------------------------------------
void write_logfile(const configuration &config,const benchmark_runner &runner,
                   const string &cli_args)
{
    //create the logfile
    logfile f(config.value<string>("logfile"),
              config.value<bool>("logfile-overwrite"));

    //create the log entry
    benchmark_log log = f.create_log(config.value<string>("entry"),
                                     "pniiobm",program_version,
                                     cli_args,
                                     "A benchmark using the pniio backend",
                                     "some stupid text");
    //write program configuration
    write_parameters(log,config);
        
    log.create_item<float64>("write",runner.begin()->unit());
    for(auto bm: runner)
        log.append_data("write",bm.time());

}
