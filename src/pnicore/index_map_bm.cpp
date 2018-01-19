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

#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include <algorithm>
#include <array>
#include <pni/core/configuration.hpp>
#include <pni/core/arrays.hpp>

#include <common/types.hpp>
#include <common/utils.hpp>

//index map with a std::vector so store the shape

template<typename STYPE,typename MTYPE> STYPE get_shape(const MTYPE &map)
{ 
  STYPE c(map.size());

  std::copy(map.begin(),map.end(),c.begin());
  return c;
}


template<typename MAP> class VariantBenchmark
{
  private:
    using VectorIndex = std::vector<size_t>;
    using ArrayIndex  = std::array<size_t,2>;
    size_t _nx;
    size_t _ny;
    size_t _offset;
    VectorIndex _vindex;
    ArrayIndex _aindex;
    MAP    _map;
  public:
    VariantBenchmark(const MAP& map):
      _map(map),
      _nx(0),
      _ny(0),
      _offset(0)
  {
      auto shape = get_shape<pni::core::shape_t>(map);
      _nx = shape[0];
      _ny = shape[1];
      _vindex = std::vector<size_t>(2);

  }
    void variadic_offset()
    {
      _offset = 0;

      for(size_t i=0;i<_nx;i++)
        for(size_t j=0;j<_ny;++j)
          _offset += _map.template offset(std::array<size_t,2>{{i,j}});
    }

    void vector_offset()
    {
      _offset = 0;

      for(_vindex[0]=0;_vindex[0]<_nx;_vindex[0]++)
        for(_vindex[1]=0;_vindex[1]<_ny;_vindex[1]++)
          _offset += _map.template offset(_vindex);
    }

    void vector_index()
    {
      for(size_t i=0;i<_map.max_elements();++i)
        _vindex = _map.template index<VectorIndex>(i);
    }

    void array_offset()
    {
      _offset = 0;

      for(_aindex[0]=0;_aindex[0]<_nx;_aindex[0]++)
        for(_aindex[1]=0;_aindex[1]<_ny;_aindex[1]++)
          _offset += _map.template offset(_aindex);
    }

    void array_index()
    {
      for(size_t i=0;i<_map.max_elements();++i)
        _aindex = _map.template index<ArrayIndex>(i);
    }
};

BenchmarkRunners create_runners()
{
  using namespace pni::core;
  return BenchmarkRunners{
    {"offset_variadic",benchmark_runner()},
    {"offset_vector",benchmark_runner()},
    {"offset_array",benchmark_runner()},
    {"index_vector",benchmark_runner()},
    {"index_array",benchmark_runner()}};
}

template<typename BMT> BenchmarkFunctions create_funcs(BMT &bm)
{
  using Benchmark = BMT;

  return BenchmarkFunctions{
    {"offset_variadic",FunctionType(std::bind(&Benchmark::variadic_offset,&bm))},
    {"offset_vector",FunctionType(std::bind(&Benchmark::vector_offset,&bm))},
    {"offset_array",FunctionType(std::bind(&Benchmark::array_offset,&bm))},
    {"index_vector",FunctionType(std::bind(&Benchmark::vector_index,&bm))},
    {"index_array",FunctionType(std::bind(&Benchmark::array_index,&bm))}};
}


template<typename MAPT> void run_benchmark(size_t nruns,const pni::core::shape_t &shape)
{
  using IndexMap = MAPT;
  using MapUtilities = pni::core::map_utils<IndexMap>;
  using Benchmark =  VariantBenchmark<IndexMap>;

  Benchmark bm(MapUtilities::create(shape));

  BenchmarkRunners runners = create_runners();
  BenchmarkFunctions funcs = create_funcs(bm);

  run_benchmarks(nruns,runners,funcs);

  write_result(runners,std::cout);


}

int main(int argc,char **argv)
{
  using namespace pni::core;
    //create the index maps
    auto dindex_map = map_utils<dynamic_cindex_map>::create(shape_t{100,100});
    auto sindex_map = map_utils<static_cindex_map<100,100>>::create(shape_t{100,100});
    auto findex_map = map_utils<fixed_dim_cindex_map<2>>::create(shape_t{100,100});


    configuration config; 
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<string>("map","m",
                      "select the index map type to benchmark","dynamic"));
    config.add_option(config_option<size_t>("nruns","n","number of runs",10));
    config.add_option(config_option<size_t>("nx","x",
                "number of elements along first dimension",100));
    config.add_option(config_option<size_t>("ny","y",
                "number of elements along second dimension",100));

    parse(config,cliargs2vector(argc,argv));

    if(config.value<bool>("help"))
    {
        std::cerr<<config<<std::endl;
        return 1;
    }
  
    //load the map type
    auto map_type = config.value<string>("map");
    auto nruns    = config.value<size_t>("nruns");
    shape_t shape{config.value<size_t>("nx"),config.value<size_t>("ny")};

    //select the map for the benchmark
    std::cout<<"# Index map benchmark"<<std::endl;
    if(map_type=="dynamic")
    {
        std::cout<<"# Dynamic index map"<<std::endl;
        run_benchmark<dynamic_cindex_map>(nruns,shape);
    }
    else if(map_type=="fixed")  
    {
        std::cout<<"# Fixed dim. index map"<<std::endl;
        run_benchmark<fixed_dim_cindex_map<2>>(nruns,shape);
    }
    else if(map_type=="static") 
    {
        std::cout<<"# Static index map"<<std::endl;
        run_benchmark<static_cindex_map<100,100>>(nruns,shape);
    }
    else
        std::cerr<<"invalid map"<<std::endl;



    return 0;
}

