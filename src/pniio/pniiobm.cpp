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

using namespace pni::core;

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

  BenchmarkPointer benchmark;
  //create the benchmark instance
  try
  {
    benchmark = BenchmarkFactory::create(config.value<string>("type"),
                                         config.value<string>("backend"));
  }
  catch(key_error &error)
  {
    std::cerr<<error<<std::endl;
    return 1;
  }

  //now we have to configure the benchmark according to the CLI arguments
  //passed by the user
  benchmark->nx(config.value<size_t>("nx"));
  benchmark->ny(config.value<size_t>("ny"));
  benchmark->nframes(config.value<size_t>("nframes"));
  benchmark->filename(config.value<string>("output"));
  benchmark->split_size(config.value<size_t>("split"));


  //create the benchmark runner instance
  benchmark_runner runner = create_runner(benchmark);

  //set the benchmark function
  BenchmarkFunction f = std::bind(&FileIOBenchmark::run,benchmark.get());

  //run the benchmark
  runner.run<BenchmarkTimer>(config.value<size_t>("nruns"),f);

  //create the output stream
  if(config.has_option("logfile"))
    write_logfile(config,runner,cli_options_string(argc,argv));

  return 0;
}
