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
//  Created on: Feb 19, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../common/data_generator.hpp"

template<typename ATYPE> 
class BinaryArithmeticBenchmarkPointer
{

  public:
    using ArrayType = ATYPE;
    using ValueType = typename ArrayType::value_type;
  private:
    pni::core::shape_t _shape;
    ArrayType _a;
    ArrayType _b;
    ArrayType _c;
    ArrayType _d;
    ArrayType _e;
    ArrayType _f;
    size_t _size;
    ValueType *_a_ptr;
    ValueType *_b_ptr;
    ValueType *_c_ptr;
    ValueType *_d_ptr;
    ValueType *_e_ptr;
    ValueType *_f_ptr;
  public:
    BinaryArithmeticBenchmarkPointer(const pni::core::shape_t &s):
      _shape(s),
      _a(),
      _b(),
      _c(),
      _d(),
      _e(),
      _f(),
      _size(0),
      _a_ptr(nullptr),
      _b_ptr(nullptr),
      _c_ptr(nullptr),
      _d_ptr(nullptr),
      _e_ptr(nullptr),
      _f_ptr(nullptr)
  {
  }

    void allocate()
    {

      deallocate(); //to be on the safe side first deallocate memory

      _a = ArrayType::create(_shape);
      _b = ArrayType::create(_shape);
      _c = ArrayType::create(_shape);
      _d = ArrayType::create(_shape);
      _e = ArrayType::create(_shape);
      _f = ArrayType::create(_shape);

      std::generate(_a.begin(),_a.end(),RandomGenerator<ValueType>());
      std::generate(_b.begin(),_b.end(),RandomGenerator<ValueType>());
      std::generate(_c.begin(),_c.end(),RandomGenerator<ValueType>());
      std::generate(_d.begin(),_d.end(),RandomGenerator<ValueType>());
      std::generate(_e.begin(),_e.end(),RandomGenerator<ValueType>());
      std::generate(_f.begin(),_f.end(),RandomGenerator<ValueType>());

      _a_ptr = const_cast<ValueType*>(_a.data());
      _b_ptr = const_cast<ValueType*>(_b.data());
      _c_ptr = const_cast<ValueType*>(_c.data());
      _d_ptr = const_cast<ValueType*>(_d.data());
      _e_ptr = const_cast<ValueType*>(_e.data());
      _f_ptr = const_cast<ValueType*>(_f.data());
      _size = _a.size();

    }

    void deallocate()
    {
      _a = ArrayType();
      _b = ArrayType();
      _c = ArrayType();
      _d = ArrayType();
      _e = ArrayType();
      _f = ArrayType();
      _size = _a.size();
    }

    void add()
    {
      for(size_t i=0;i<_size;++i)
        _c_ptr[i] = _a_ptr[i] + _b_ptr[i];
    }

    void sub()
    {
      for(size_t i=0;i<_size;++i)
        _c_ptr[i] = _a_ptr[i] - _b_ptr[i];
    }


    void mult()
    {
      for(size_t i=0;i<_size;++i)
        _c_ptr[i] = _a_ptr[i] * _b_ptr[i];
    }

    void div()
    {
      for(size_t i=0;i<_size;++i)
        _c_ptr[i] = _a_ptr[i] / _b_ptr[i];
    }

    void all()
    {
      for(size_t i=0;i<_size;++i)
        _c_ptr[i] = _a_ptr[i]*_b_ptr[i] + (_d_ptr[i]-_e_ptr[i])/_f_ptr[i];
    }

};
