set(INDEX_MAP_BM_SRC index_map_bm.cpp)
set(ARITHMETIC_BM_SRC arithmeticbm.cpp benchmark_runners.cpp)

set(FARITHMETIC_BM_SRC arithmetic_benchmark.f90 )


link_directories(${PNICORE_LIBRARY_DIRS})
include_directories(${PNICORE_INCLUDE_DIRS})
add_executable(index_map_bm ${INDEX_MAP_BM_SRC})
target_link_libraries(index_map_bm ${PNICORE_LIBRARIES})

add_library(farithmetic OBJECT ${FARITHMETIC_BM_SRC})
add_executable(arithmeticbm ${ARITHMETIC_BM_SRC} $<TARGET_OBJECTS:farithmetic>)
target_link_libraries(arithmeticbm ${PNICORE_LIBRARIES})

install(TARGETS index_map_bm arithmeticbm DESTINATION ${CMAKE_INSTALL_BINDIR})
