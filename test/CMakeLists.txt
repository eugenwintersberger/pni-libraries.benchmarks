set(TEST_SRC benchmark_test.cpp 
             array_benchmark_data_test.cpp 
             view_benchmark_data_test.cpp
    )

link_directories(${PNICORE_LIBRARY_DIRS} ${CPPUNIT_LIBRARY_DIRS})
include_directories(${CPPUNIT_INCLUDE_DIRS} ${PNICORE_INCLUDE_DIRS})

add_executable(benchmarktest ${TEST_SRC})
target_link_libraries(benchmarktest ${PNICORE_LIBRARIES} ${CPPUNIT_LIBRARIES})
