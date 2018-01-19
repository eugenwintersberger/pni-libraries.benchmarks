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

#include <vector>
#include "file_io_benchmark.hpp"
#include "../common/data_generator.hpp"

extern "C" {
    #include <hdf5.h>
}

template<typename T> struct type2hdftype;

#define TC2HDFTYPEMAP(stype,hdftype)\
    template<> struct type2hdftype<stype>\
    {\
        static hid_t type()\
        {\
            return hdftype;\
        }\
    }

TC2HDFTYPEMAP(pni::core::uint8,H5T_NATIVE_UCHAR);
TC2HDFTYPEMAP(pni::core::int8,H5T_NATIVE_SCHAR);
TC2HDFTYPEMAP(pni::core::uint16,H5T_NATIVE_USHORT);
TC2HDFTYPEMAP(pni::core::int16,H5T_NATIVE_SHORT);
TC2HDFTYPEMAP(pni::core::uint32,H5T_NATIVE_UINT);
TC2HDFTYPEMAP(pni::core::int32,H5T_NATIVE_INT);
TC2HDFTYPEMAP(pni::core::uint64,H5T_NATIVE_ULONG);
TC2HDFTYPEMAP(pni::core::int64,H5T_NATIVE_LONG);

template<typename T> class HDF5IOBenchmark : public FileIOBenchmark
{
  private:
    hid_t _file;
    hid_t _file_space;
    hid_t _memory_space;
    hid_t _dataset;
    hid_t _datatype;
    T *_frame_data;
    using DataGenerator = RandomGenerator<T>;

  public:
    //=====================constructor and destructors=====================
    //! default constructor
    HDF5IOBenchmark():FileIOBenchmark()
  {}

    //=======================public member functions=======================
    //! create file and dataspace
    virtual void create();

    //! close file and datasets
    virtual void close();

    //! run the benchmark
    virtual void run();
};

//-----------------------------------------------------------------------------
template<typename T> void HDF5IOBenchmark<T>::create()
{
  _frame_data = new T[nx()*ny()];
  std::generate(&_frame_data[0],&_frame_data[nx()*ny()],
                DataGenerator());

  //create data file
  _file = H5Fcreate(filename().c_str(),H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);

  //create dtype
  _datatype = H5Tcopy(type2hdftype<T>::type());

  //create data-space on disk
  hsize_t fdims[] = {0,nx(),ny()};
  hsize_t fmaxdims[] = {H5S_UNLIMITED,nx(),ny()};

  _file_space = H5Screate_simple(3,fdims,fmaxdims);

  //create data-space in memory
  hsize_t mdims[] = {nx(),ny()};
  _memory_space = H5Screate_simple(2,mdims,mdims);

  //create the property list for the dataset
  hid_t plist = H5Pcreate(H5P_DATASET_CREATE);
  H5Pset_layout(plist,H5D_CHUNKED);
  fdims[0] = 1;
  H5Pset_chunk(plist,3,fdims);
  fdims[0] = 0;
  //create the dataset
  _dataset = H5Dcreate2(_file,"data",_datatype,_file_space,
                        H5P_DEFAULT,plist,H5P_DEFAULT);

  H5Pclose(plist);
}

//-----------------------------------------------------------------------------
template<typename T> void HDF5IOBenchmark<T>::close()
{
  H5Tclose(_datatype);
  H5Sclose(_file_space);
  H5Sclose(_memory_space);
  H5Dclose(_dataset);
  H5Fclose(_file);

  if(_frame_data) delete [] _frame_data;
}

//-----------------------------------------------------------------------------
template<typename T> void HDF5IOBenchmark<T>::run()
{
  std::vector<hsize_t> fdims{3};
  std::vector<hsize_t> offset{3};
  std::vector<hsize_t> count{3};


  for(size_t n=0;n<nframes();n++)
  {
    fdims = {n+1,nx(),ny()};
    offset = {n,0,0};
    count = {1,nx(),ny()};
    H5Dset_extent(_dataset,fdims.data());
    _file_space = H5Dget_space(_dataset);

    H5Sselect_hyperslab(_file_space,H5S_SELECT_SET,offset.data(),NULL,
                        count.data(),NULL);
    H5Dwrite(_dataset,_datatype,_memory_space,_file_space,
             H5P_DEFAULT,_frame_data);

    H5Fflush(_file,H5F_SCOPE_LOCAL);
  }
}
