//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jan 5, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "pniiobm_utils.hpp"


//----------------------------------------------------------------------------
//                  MAIN PROGRAM
//----------------------------------------------------------------------------
int main(int argc,char **argv)
{
    typedef chrono_timer<std::chrono::high_resolution_clock,
                        std::chrono::milliseconds> bm_timer_t;
    typedef benchmark_factory::pointer_type pointer_type;
    typedef benchmark_runner::function_t function_type;

    //
    configuration config = create_configuration();
   
    //parse commmand line options 
    parse(config,cliargs2vector(argc,argv));
    if(config.value<bool>("help"))
    {
        std::cerr<<config<<std::endl;
        return 1;
    }

    pointer_type bm_ptr;
    //create the benchmark instance
    try
    {
        bm_ptr = benchmark_factory::create(config.value<string>("type"),
                                           config.value<string>("backend"));
    }
    catch(key_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }

    //now we have to configure the benchmark according to the CLI arguments 
    //passed by the user
    bm_ptr->nx(config.value<size_t>("nx"));
    bm_ptr->ny(config.value<size_t>("ny"));
    bm_ptr->nframes(config.value<size_t>("nframes"));
    bm_ptr->filename(config.value<string>("output"));
    bm_ptr->split_size(config.value<size_t>("split"));


    //create the benchmark runner instance
    benchmark_runner runner;

    //set the benchmark function
    function_type f = std::bind(&file_io_benchmark::run,bm_ptr.get());
    //create the pre- and post-run functions
    function_type pre_run = std::bind(&file_io_benchmark::create,bm_ptr.get());
    function_type post_run = std::bind(&file_io_benchmark::close,bm_ptr.get());

    //set the pre and post run functions
    runner.prerun(pre_run);
    runner.postrun(post_run);
    //run the benchmark
    runner.run<bm_timer_t>(config.value<size_t>("nruns"),f);

    
    //create the output stream
    if(config.has_option("logfile"))
    {
        logfile f(config.value<string>("logfile"),
                  config.value<bool>("logfile-overwrite"));
        benchmark_log log = f.create_log("pniiobm",
                                         "pniiobm",program_version,
                                         "blabla",
                                         "A benchmark using the pniio backend",
                                         "some stupid text");
        //write program configuration
        write_parameters(log,config);

        log.create_item<float64>("write","ms");
        for(auto bm: runner)
            log.append_data("write",bm.time());

        //open log file for writting
        //std::ofstream logfile(config.value<string>("logfile").c_str());
        //output_result(logfile,runner);
    }

    return 0;
}
