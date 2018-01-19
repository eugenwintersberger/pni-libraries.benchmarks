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
//  Created on: Dev 28, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <algorithm>

#include "../common/data_generator.hpp"

template<typename ATYPE> class InplaceArithmeticBenchmark
{
  public:
    using ArrayType = ATYPE;
    using ValueType =  typename ArrayType::value_type;
  private:
    pni::core::shape_t _shape;
    ArrayType _a;
    ArrayType _b;
    ValueType _s;
  public:
    InplaceArithmeticBenchmark(const pni::core::shape_t &s):
      _shape(s)
  {}

    void allocate()
    {
      _a = ArrayType::create(_shape);
      _b = ArrayType::create(_shape);

      std::generate(_a.begin(),_a.end(),RandomGenerator<ValueType>());
      std::generate(_b.begin(),_b.end(),RandomGenerator<ValueType>());

      _s = RandomGenerator<ValueType>()();
    }

    void deallocate()
    {
      _a = ArrayType();
      _b = ArrayType();
      _s = ValueType(0);
    }


    void add_scalar() { _a += _s; }

    void add_array() { _a += _b; }

    void sub_scalar() { _a -= _s; }

    void sub_array() { _a -= _b; }

    void mult_scalar() { _a *= _s; }

    void mult_array() { _a *= _b; }

    void div_scalar() { _a /= _s; }

    void div_array() { _a /= _b; }
};
