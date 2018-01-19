//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Dec 17, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <memory>
#include <pni/core/types.hpp>


// forward declaration of the file_io_benchmark class
class FileIOBenchmark;

class BenchmarkFactory
{
  public:
    using BenchmarkPointer = std::unique_ptr<FileIOBenchmark>;
  private:
    static BenchmarkPointer create_pniio(const std::string &type_code);

    static BenchmarkPointer create_hdf5(const std::string &type_code);
  public:
    //---------------------------------------------------------------------
    //!
    //! \brief create a benchmark
    //!
    //! Creates an instance of a benchmark class according to the type code
    //! passed by the user and the backend which should be used to write the
    //! data.
    //! Supported backends are currently
    //! \li hdf5 - using the plain HDF5 C API
    //! \li pniio - using the pniio wrapper
    //!
    //! \throws key_error if either the type code or the backend are unkown
    //! \param type string representation of the data type
    //! \param backend the backend to use
    //! \return unique pointer to the benchmark instance
    //!
    static BenchmarkPointer create(const std::string &type_code,
                                   const std::string &backend);
};

