//benchmark for index policies

#include <iostream>
#include <chrono>
#include <vector>
#include <array>

#include <pni/core/index_map/index_maps.hpp>
#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>

using namespace pni::core;

//define a timer type for the benchmarks
typedef chrono_timer<std::chrono::high_resolution_clock,
                    std::chrono::nanoseconds> bmtimer_t;


//index map with a std::vector so store the shape

template<typename STYPE,typename MTYPE> STYPE get_shape(const MTYPE &map)
{
    STYPE c(map.size());

    std::copy(map.begin(),map.end(),c.begin());
    return c;
}


template<typename MAP> class variant_bm
{
    private:
        size_t _nx;
        size_t _ny;
        size_t _offset;
        std::vector<size_t> _vindex;
        std::array<size_t,2> _aindex;
        MAP    _map;
    public:
        variant_bm(const MAP& map):
            _map(map), 
            _nx(0),
            _ny(0),
            _offset(0)
        {
            auto shape = get_shape<shape_t>(map);
            _nx = shape[0];
            _ny = shape[1];
            _vindex = std::vector<size_t>(2);

        }
        void variadic_run()
        {
            _offset = 0;

            for(size_t i=0;i<_nx;i++)
                for(size_t j=0;j<_ny;++j)
                    _offset += _map.template offset(i,j);
        }

        void vector_run()
        {
            _offset = 0;

            for(_vindex[0]=0;_vindex[0]<_nx;_vindex[0]++)
                for(_vindex[1]=0;_vindex[1]<_ny;_vindex[1]++)
                    _offset += _map.template offset(_vindex);
        }
        
        void array_run()
        {
            _offset = 0;

            for(_aindex[0]=0;_aindex[0]<_nx;_aindex[0]++)
                for(_aindex[1]=0;_aindex[1]<_ny;_aindex[1]++)
                    _offset += _map.template offset(_aindex);
        }
};


template<typename MAPT> void run_benchmark(size_t nruns,MAPT &&m)
{
    typedef variant_bm<MAPT> variant_bm_t; //variant benchmark type
    typedef benchmark_runner::function_t function_t;

    variant_bm_t variant_bm_i(m);

    benchmark_runner r_variadic,r_vector,r_array;
    benchmark_runner::function_t f_variadic,f_vector,f_array;
    
    f_variadic = std::bind(&variant_bm_t::variadic_run,&variant_bm_i);
    f_vector   = std::bind(&variant_bm_t::vector_run,&variant_bm_i);
    f_array    = std::bind(&variant_bm_t::array_run,&variant_bm_i);


    r_array.run<bmtimer_t>(nruns,f_array);
    r_vector.run<bmtimer_t>(nruns,f_vector);
    r_variadic.run<bmtimer_t>(nruns,f_variadic);

    auto i_variadic = r_variadic.begin();
    auto i_vector   = r_vector.begin();
    auto i_array    = r_vector.begin();
    std::cout<<std::scientific;
    while(i_variadic!=r_variadic.end())
        std::cout<<*i_variadic++<<"\t"<<*i_vector++<<"\t"<<*i_array++<<std::endl;
    
}

size_t c_reference_computation(size_t nx,size_t ny)
{
    size_t offset = 0;

    for(size_t i = 0;i<nx;++i)
        for(size_t j = 0;j<ny;++j)
            offset += i*ny+j;

    return offset;
}

void c_ref_benchmark(size_t nruns)
{
    typedef benchmark_runner::function_t function_t;

    benchmark_runner runner;
    size_t nx = 100;
    size_t ny = 100;
    function_t f = std::bind(c_reference_computation,nx,ny);

    runner.run<bmtimer_t>(nruns,f);

    std::cout<<std::scientific;
    auto iter = runner.begin();
    while(iter!=runner.end())
        std::cout<<*iter++<<std::endl;
}

int main(int argc,char **argv)
{
    //create the index maps
    auto dindex_map = map_utils<dynamic_cindex_map>::create(shape_t{100,100});
    auto sindex_map = map_utils<static_cindex_map<100,100>>::create(shape_t{100,100});
    auto findex_map = map_utils<fixed_dim_cindex_map<2>>::create(shape_t{100,100});


    configuration config; 
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<string>("map","m",
                      "select the index map type to benchmark","dynamic"));
    config.add_option(config_option<size_t>("nruns","n","number of runs",10));

    parse(config,cliargs2vector(argc,argv));

    if(config.value<bool>("help"))
    {
        std::cerr<<config<<std::endl;
        return 1;
    }
  
    //load the map type
    auto map_type = config.value<string>("map");
    auto nruns    = config.value<size_t>("nruns");
    //select the map for the benchmark
    if(map_type=="dynamic")     run_benchmark(nruns,dindex_map);
    else if(map_type=="fixed")  run_benchmark(nruns,findex_map);
    else if(map_type=="static") run_benchmark(nruns,sindex_map);
    else if(map_type=="cref")   c_ref_benchmark(nruns);
    else
        std::cerr<<"invalid map"<<std::endl;



    return 0;
}

