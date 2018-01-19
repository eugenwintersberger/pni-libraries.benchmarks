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

#include <pni/core/error.hpp>
#include "benchmark_factory.hpp"
#include "pniio_io_benchmark.hpp"
#include "hdf5_io_benchmark.hpp"

//-----------------------------------------------------------------------------
BenchmarkFactory::BenchmarkPointer
BenchmarkFactory::create_pniio(const std::string &type_code)
{
  using namespace pni::core;
  BenchmarkPointer ptr;

  if(type_code == "uint8")
    ptr = BenchmarkPointer(new PNIIOBenchmark<uint8>());
  else if(type_code == "int8")
    ptr = BenchmarkPointer(new PNIIOBenchmark<int8>());
  else if(type_code == "uint16")
    ptr = BenchmarkPointer(new PNIIOBenchmark<uint16>());
  else if(type_code == "int16")
    ptr = BenchmarkPointer(new PNIIOBenchmark<int16>());
  else if(type_code == "uint32")
    ptr = BenchmarkPointer(new PNIIOBenchmark<uint32>());
  else if(type_code == "int32")
    ptr = BenchmarkPointer(new PNIIOBenchmark<int32>());
  else
    throw key_error(EXCEPTION_RECORD,"Unkown type code!");

  return ptr;
}

//-----------------------------------------------------------------------------
BenchmarkFactory::BenchmarkPointer
BenchmarkFactory::create_hdf5(const std::string &type_code)
{
  using namespace pni::core;
  BenchmarkPointer ptr;

  if(type_code == "uint8")
    ptr = BenchmarkPointer(new HDF5IOBenchmark<uint8>());
  else if(type_code == "int8")
    ptr = BenchmarkPointer(new HDF5IOBenchmark<int8>());
  else if(type_code == "uint16")
    ptr = BenchmarkPointer(new HDF5IOBenchmark<uint16>());
  else if(type_code == "int16")
    ptr = BenchmarkPointer(new HDF5IOBenchmark<int16>());
  else if(type_code == "uint32")
    ptr = BenchmarkPointer(new HDF5IOBenchmark<uint32>());
  else if(type_code == "int32")
    ptr = BenchmarkPointer(new HDF5IOBenchmark<int32>());
  else
    throw key_error(EXCEPTION_RECORD,"Unknown type code!");

  return ptr;
}


//-----------------------------------------------------------------------------
BenchmarkFactory::BenchmarkPointer
BenchmarkFactory::create(const std::string &type_code, const std::string &backend)
{
  using namespace pni::core;
  BenchmarkPointer ptr;

  if(backend == "pniio")
    ptr = create_pniio(type_code);
  else if(backend == "hdf5")
    ptr = create_hdf5(type_code);
  else
    throw key_error(EXCEPTION_RECORD,"Unkown backend!");

  return ptr;
}
