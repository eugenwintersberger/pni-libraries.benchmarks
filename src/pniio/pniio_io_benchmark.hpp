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
// Created on: Jan 05, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "file_io_benchmark.hpp"

extern "C" {
#include <hdf5.h>
}

#include <pni/io/nexus.hpp>

#include "../common/data_generator.hpp"

template<typename T> class PNIIOBenchmark : public FileIOBenchmark
{
  public:
    using ArrayType = pni::core::dynamic_array<T>;
    using DataGenerator = RandomGenerator<T>;
  private:
    //! array holding the buffer for the frame data
    ArrayType _frame_buffer;
    hdf5::file::File     _file;
  public:
    //===================constructors and destructor=======================
    //! default constructor
    PNIIOBenchmark():
      FileIOBenchmark(),
      _frame_buffer()
  {}

    //======================public member functions========================
    //! create data structures
    virtual void create();
    virtual void close();

    //---------------------------------------------------------------------
    //! run the benchmark
    virtual void run() ;

};

//-----------------------------------------------------------------------------
template<typename T> void PNIIOBenchmark<T>::create()
{
  using namespace pni::core;
  //create data
  shape_t shape{nx(),ny()};
  _frame_buffer = ArrayType::create(shape);

  std::generate(_frame_buffer.begin(),_frame_buffer.end(),
                DataGenerator());

  //
  // create the file
  //
  _file = hdf5::file::create(filename(),hdf5::file::AccessFlags::TRUNCATE);
      //pni::io::nexus::create_file(filename(),hdf5::file::AccessFlags::TRUNCATE);

  //
  // create the dataset
  //
  hdf5::Dimensions s{0,nx(),ny()};
  hdf5::Dimensions cs{1,nx(),ny()};
  hdf5::node::Group root = _file.root();
  auto type = hdf5::datatype::create<T>();
  hdf5::dataspace::Simple space{s,{hdf5::dataspace::Simple::UNLIMITED,nx(),nx()}};
  hdf5::node::ChunkedDataset(root,"data",type,space,cs);

}

//-----------------------------------------------------------------------------
template<typename T> void PNIIOBenchmark<T>::close()
{
  _file.close();
}


//-----------------------------------------------------------------------------
template<typename T> void PNIIOBenchmark<T>::run()
{
  hdf5::dataspace::Hyperslab selection({0,0,0},{1,nx(),nx()});
  hdf5::node::Dataset field = _file.root()["data"];
  for(size_t n = 0; n<nframes();n++)
  {
    field.extent(0,1);
    selection.offset(0,n);
    field.write(_frame_buffer,selection);
    _file.flush(hdf5::file::Scope::GLOBAL);
  }
}
