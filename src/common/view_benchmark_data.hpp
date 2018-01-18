//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of PNI libraries benchmark suite.
//
// PNI libraries benchmark suite is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 2 of the License,
// or (at your option) any later version.
//
// PNI libraries benchmark suite  is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// PNI libraries benchmark suite.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Dec 13, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once                

#include "array_benchmark_data.hpp"
#include <pni/core/arrays.hpp>
#include <vector>

template<typename ATYPE>
pni::core::array_view<ATYPE> create_view(ATYPE &a)
{
    std::vector<pni::core::slice> slices;
    auto shape = a.template shape<pni::core::shape_t>();

    for(auto d: shape) slices.push_back(pni::core::slice(0,d));

    return a(slices);
}

template<typename ATYPE> 
class ViewBenchmarkData : public ArrayBenchmarkData<ATYPE>
{
  public:
    using ArrayType = pni::core::array_view<ATYPE>;
    using ValueType = typename ATYPE::value_type;
  private:
    using Base =  ArrayBenchmarkData<ATYPE>;
    ArrayType _view;


  public:
    template<typename CTYPE>
    ViewBenchmarkData(const CTYPE &shape):
    ArrayBenchmarkData<ATYPE>(shape),
    _view(create_view(ArrayBenchmarkData<ATYPE>::data()))
    {
    }

    //---------------------------------------------------------------------
    template<typename CTYPE> void allocate(const CTYPE &shape)
    {
      Base::template allocate(shape);

      _view = create_view(Base::data());
    }

    //---------------------------------------------------------------------
    void deallocate()
    {
      Base::deallocate();
      _view = create_view(Base::data());
    }

    //---------------------------------------------------------------------
    ArrayType &data() { return _view; }

    //---------------------------------------------------------------------
    const ArrayType &data() const { return _view; }

};
