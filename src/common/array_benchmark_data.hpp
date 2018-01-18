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
// PNI libraries benchmark suite is distributed in the hope that it will be
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
///
#pragma once                

#include "types.hpp"
#include "data_generator.hpp"


//!
//! \brief array manger
//! 
//! This tempalte holds a particular array and provides methods to access the 
//! array as well as allocate, deallocate, and initialize it with random data. 
//!
//! \tparam ATYPE array type
//!
template<typename ATYPE> 
class ArrayBenchmarkData
{
  public:
    //! array type
    using ArrayType =  ATYPE;
    //! value type
    using ValueType = typename ArrayType::value_type;
    //! array factory type
    using FactoryType = array_factory<ArrayType>;
    //! generator type
    using GeneratorType = RandomGenerator<ValueType>;
  private:
    ArrayType _data; //!< the array wit hdata
  public:
    //---------------------------------------------------------------------
    //!
    //! \brief constructor
    //!
    //! Construct the array data from a shape.
    //!
    //! \tparam CTYPE container type with shape information
    //!
    //! \param shape reference to a CTYPE instance
    //!
    template<typename CTYPE>
    ArrayBenchmarkData(const CTYPE &shape):
    _data(ArrayType::template create(shape))
    {
      this->initialize();
    }

    //---------------------------------------------------------------------
    //!
    //! \brief allocate array data
    //!
    //! Allocate new memory for the array. The shape information is
    //! provided to the method by a STL compliant container.
    //!
    //! \tparam CTYPE container type with shape
    //! \param shape reference to the shape container
    //!
    template<typename CTYPE>
    void allocate(const CTYPE &shape)
    {
      _data = ArrayType::template create(shape);
    }

    //---------------------------------------------------------------------
    //!
    //! \brief initialize the array
    //!
    //! This method initializes the internal array with random data.
    //!
    void initialize()
    {
      std::generate(_data.begin(),_data.end(),GeneratorType());
    }

    //---------------------------------------------------------------------
    //!
    //! \brief deallocate the array
    //!
    //! Basically this function does nothing. As we do array allocation
    //! using rvalue reference to original data will be dropped when
    //! allocating memory automatically.
    //!
    void deallocate() {  }

    //---------------------------------------------------------------------
    //!
    //! \brief get reference to array
    //!
    //! Return a reference to the array stored in the class.
    //! \return array reference
    //!
    ArrayType &data() { return _data; }

    //---------------------------------------------------------------------
    //!
    //! \brief get const reference to the array
    //!
    //! Return a const reference to the array stored in the class.
    //!
    //! \return const reference to the array
    //!
    const ArrayType &data() const { return _data; }

};
