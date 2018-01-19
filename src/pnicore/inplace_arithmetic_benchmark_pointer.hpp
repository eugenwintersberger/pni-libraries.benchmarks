//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniutils.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Feb 19, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>

#include "../common/data_generator.hpp"

template<typename ATYPE> 
class InplaceArithmeticBenchmarkPointer
{
  public:
    using ArrayType = ATYPE;
    using ValueType = typename ArrayType::value_type;

  private:
    pni::core::shape_t _shape;

    ArrayType _a;
    ArrayType _b;
    ValueType _s;
    ValueType *_a_ptr;
    ValueType *_b_ptr;
    size_t _size;
  public:
    InplaceArithmeticBenchmarkPointer(const pni::core::shape_t &s):
      _shape(s),
      _a(),
      _b(),
      _s(),
      _a_ptr(nullptr),
      _b_ptr(nullptr),
      _size(0)
  {
  }

    void allocate()
    {
      _a = ArrayType::create(_shape);
      _b = ArrayType::create(_shape);

      std::generate(_a.begin(),_a.end(),RandomGenerator<ValueType>());
      std::generate(_b.begin(),_b.end(),RandomGenerator<ValueType>());

      _s = RandomGenerator<ValueType>()();

      _a_ptr = const_cast<ValueType*>(_a.data());
      _b_ptr = const_cast<ValueType*>(_b.data());

      _size = _a.size();
    }

    void deallocate()
    {
      _a = ArrayType();
      _b = ArrayType();
      _s = ValueType(0);

      _a_ptr = nullptr;
      _b_ptr = nullptr;
    }


    void add_scalar() { for(size_t i=0;i<_size;++i) _a_ptr[i] += _s; }

    void add_array() { for(size_t i=0;i<_size;++i) _a_ptr[i] += _b_ptr[i]; }

    void sub_scalar() { for(size_t i=0;i<_size;++i) _a_ptr[i] -= _s; }

    void sub_array() { for(size_t i=0;i<_size;++i) _a_ptr[i] -= _b_ptr[i]; }

    void mult_scalar() { for(size_t i=0;i<_size;++i) _a_ptr[i] *= _s; }

    void mult_array() { for(size_t i=0;i<_size;++i) _a_ptr[i] *= _b_ptr[i]; }

    void div_scalar() { for(size_t i=0;i<_size;++i) _a_ptr[i] /=_s; }

    void div_array() { for(size_t i=0;i<_size;++i) _a_ptr[i] /= _b_ptr[i];
    }

};
