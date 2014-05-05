//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pni-benchmarks.
//
// pni-benchmarks is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pni-benchmarks is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pni-benchmarks.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: May 30, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

namespace f90
{
extern "C"
{
    extern void deallocate_data();
    extern void allocate_data(int,int);

    extern void binary_run_add();
    extern void binary_run_sub();
    extern void binary_run_div();
    extern void binary_run_mult();
    extern void binary_run_all();

    extern void unary_run_add_array();
    extern void unary_run_add_scalar();
    extern void unary_run_sub_array();
    extern void unary_run_sub_scalar();
    extern void unary_run_div_array();
    extern void unary_run_div_scalar();
    extern void unary_run_mult_array();
    extern void unary_run_mult_scalar();
}
    

}
