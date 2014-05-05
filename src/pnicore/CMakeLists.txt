set(ARITHMETIC_BM_SRC arithmeticbm.cpp benchmark_runners.cpp)
set(ITERATOR_BM_SRC iteratorbm.cpp)
set(INDEXMAP_BM_SRC index_map_bm.cpp)

set(FARITHMETIC_BM_SRC arithmetic_benchmark.f90 )
set(MULTIINDEX_BM_SRC multiindexbm.cpp)


link_directories(${PNICORE_LIBRARY_DIRS} ${PNIIO_LIBRARY_DIRS})
include_directories(${PNICORE_INCLUDE_DIRS})

add_library(farithmetic OBJECT ${FARITHMETIC_BM_SRC})
add_executable(arithmeticbm ${ARITHMETIC_BM_SRC} $<TARGET_OBJECTS:farithmetic>
               $<TARGET_OBJECTS:commonobjs>)
target_link_libraries(arithmeticbm ${PNICORE_LIBRARIES} ${PNIIO_LIBRARIES})

add_executable(iteratorbm ${ITERATOR_BM_SRC} $<TARGET_OBJECTS:commonobjs>)
target_link_libraries(iteratorbm ${PNICORE_LIBRARIES}
                       ${PNIIO_LIBRARIES})

add_executable(multiindexbm ${MULTIINDEX_BM_SRC} $<TARGET_OBJECTS:commonobjs>)
target_link_libraries(multiindexbm ${PNICORE_LIBRARIES} 
                      ${PNIIO_LIBRARIES})

add_executable(indexmapbm ${INDEXMAP_BM_SRC} $<TARGET_OBJECTS:commonobjs>)
target_link_libraries(indexmapbm ${PNICORE_LIBRARIES} ${PNIIO_LIBRARIES} profiler)

install(TARGETS arithmeticbm  
                iteratorbm 
                multiindexbm
                indexmapbm
                DESTINATION ${CMAKE_INSTALL_BINDIR})

