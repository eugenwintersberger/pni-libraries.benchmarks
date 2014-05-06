//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 06, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <functional>
#include <chrono>
#include <fstream>
#include <pni/core/types.hpp>
#include <pni/core/benchmark.hpp>
#include "benchmark_factory.hpp"
#include "file_io_benchmark.hpp"
#include <common/config.hpp>
#include <common/configuration.hpp>
#include <common/logfile.hpp>

using namespace pni::core;

//!
//! \brief create program configuration
//!
configuration create_configuration();

//----------------------------------------------------------------------------
//!
//! \brief write program parameters
//!
//! Writes all the program configuration parameters passed by the user to the 
//! benchmark log.
//! 
//! \param log benchmark log instance 
//! \param config configuration instance
//!
void write_parameters(benchmark_log &log,const configuration &config);
