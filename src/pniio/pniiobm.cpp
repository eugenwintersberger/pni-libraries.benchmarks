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
    benchmark_runner runner = create_runner(bm_ptr);

    //set the benchmark function
    function_type f = std::bind(&file_io_benchmark::run,bm_ptr.get());

    //run the benchmark
    runner.run<bm_timer_t>(config.value<size_t>("nruns"),f);

    //create the output stream
    if(config.has_option("logfile")) 
        write_logfile(config,runner,cli_options_string(argc,argv));

    return 0;
}
