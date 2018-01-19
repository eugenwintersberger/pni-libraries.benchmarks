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

#include "benchmark_runners.hpp"
#include "fortran_arithmeticbm.hpp"


BenchmarkRunners create_binary_benchmarks()
{
    return BenchmarkRunners{{"c=a+b",pni::core::benchmark_runner()},
                             {"c=a-b",pni::core::benchmark_runner()},
                             {"c=a/b",pni::core::benchmark_runner()},
                             {"c=a*b",pni::core::benchmark_runner()},
                             {"c=a*b+(d-e)/f",pni::core::benchmark_runner()}};
}

//-----------------------------------------------------------------------------
BenchmarkRunners create_unary_benchmarks()
{
    return BenchmarkRunners{{"a+=b",pni::core::benchmark_runner()},
                             {"a*=b",pni::core::benchmark_runner()},
                             {"a-=b",pni::core::benchmark_runner()},
                             {"a/=b",pni::core::benchmark_runner()},
                             {"a+=s",pni::core::benchmark_runner()},
                             {"a*=s",pni::core::benchmark_runner()},
                             {"a-=s",pni::core::benchmark_runner()},
                             {"a/=s",pni::core::benchmark_runner()}};

}

//-----------------------------------------------------------------------------
BenchmarkFunctions create_unary_functions(const FunctionType &add_array,
                                         const FunctionType &sub_array,
                                       const FunctionType &mult_array,
                                       const FunctionType &div_array,
                                       const FunctionType &add_scalar,
                                       const FunctionType &sub_scalar,
                                       const FunctionType &mult_scalar,
                                       const FunctionType &div_scalar)
{
    return BenchmarkFunctions{{"a+=b",add_array},
                              {"a*=b",mult_array},
                              {"a-=b",sub_array},
                              {"a/=b",div_array},
                              {"a+=s",add_scalar},
                              {"a*=s",mult_scalar},
                              {"a-=s",sub_scalar},
                              {"a/=s",div_scalar}};

}

//-----------------------------------------------------------------------------
BenchmarkFunctions create_binary_functions(const FunctionType &add,
                                        const FunctionType &sub,
                                        const FunctionType &div,
                                        const FunctionType &mult,
                                        const FunctionType &all)
{
    return BenchmarkFunctions{{"c=a+b",add},
                              {"c=a/b",div},
                              {"c=a*b",mult},
                              {"c=a-b",sub},
                              {"c=a*b+(d-e)/f",all}};
}


//-----------------------------------------------------------------------------
void run_binary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o)
{
    FunctionType allocate_data = std::bind(f90::allocate_data,int(nx),int(ny));
    FunctionType deallocate_data = std::bind(f90::deallocate_data);

    BenchmarkRunners runners = create_binary_benchmarks();
    setup_benchmarks(runners,allocate_data,deallocate_data);

    BenchmarkFunctions funcs = create_binary_functions(
                            FunctionType(std::bind(f90::binary_run_add)),
                            FunctionType(std::bind(f90::binary_run_sub)),
                            FunctionType(std::bind(f90::binary_run_div)),
                            FunctionType(std::bind(f90::binary_run_mult)),
                            FunctionType(std::bind(f90::binary_run_all)));

   
    run_benchmarks(nruns,runners,funcs);
    write_result(runners,o);
}

//-----------------------------------------------------------------------------
void run_unary_fortran_benchmark(size_t nruns,size_t nx,size_t ny,std::ostream
        &o)
{

    FunctionType allocate_data = std::bind(f90::allocate_data,int(nx),int(ny));
    FunctionType deallocate_data = std::bind(f90::deallocate_data);

    BenchmarkRunners runners = create_unary_benchmarks();
    setup_benchmarks(runners,allocate_data,deallocate_data);

    BenchmarkFunctions funcs = create_unary_functions(
            FunctionType(std::bind(f90::unary_run_add_array)),
            FunctionType(std::bind(f90::unary_run_sub_array)),
            FunctionType(std::bind(f90::unary_run_mult_array)),
            FunctionType(std::bind(f90::unary_run_div_array)),
            FunctionType(std::bind(f90::unary_run_add_scalar)),
            FunctionType(std::bind(f90::unary_run_sub_scalar)),
            FunctionType(std::bind(f90::unary_run_mult_scalar)),
            FunctionType(std::bind(f90::unary_run_div_scalar)));

   
    run_benchmarks(nruns,runners,funcs);
    write_result(runners,o);
}
