include(${PROJECT_SOURCE_DIR}/cmake/common/BoostLibrarySetup.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/common/BoostTestConfig.cmake)

find_package(Boost COMPONENTS unit_test_framework)

set(TEST_SRC 
             #benchmark_test.cpp 
             dynamic_array_benchmark_data_test.cpp 
             fixed_array_benchmark_data_test.cpp
             static_array_benchmark_data_test.cpp
             #view_benchmark_data_test.cpp
    )

set_boost_test_definitions(TEST_SRC "testing common benchmark code")
add_executable(benchmarktest ${TEST_SRC})
target_link_libraries(benchmarktest pniio Boost::unit_test_framework)
add_boost_logging_test("Benchmark:common" benchmarktest ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(check benchmarktest)
