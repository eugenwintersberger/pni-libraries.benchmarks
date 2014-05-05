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

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>

using namespace pni::core;

//!
//! \brief create the default configuration
//! 
//! This function creates the default configuration and thus command line 
//! options all benchmark programs share. 
//! This includes the following options
//! \li -l(--logfile) name of the logfile where to dump data
//! \li --logfile-overwrite instructs the program to overwrite an existing
//! logfile
//! \li -r(--nruns) number of benchmark runs 
//! \li -h(--help) show help on standard error
//! 
//! \return configuration object
//!
configuration create_default_config();
