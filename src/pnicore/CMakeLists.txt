set(ARITHMETIC_BM_SRC arithmeticbm.cpp benchmark_runners.cpp)
set(ITERATOR_BM_SRC iteratorbm.cpp)
set(INDEXMAP_BM_SRC index_map_bm.cpp)

set(FARITHMETIC_BM_SRC arithmetic_benchmark.f90 )
set(MULTIINDEX_BM_SRC multiindexbm.cpp)


add_library(farithmetic OBJECT ${FARITHMETIC_BM_SRC})
add_executable(arithmeticbm ${ARITHMETIC_BM_SRC} $<TARGET_OBJECTS:farithmetic>
               $<TARGET_OBJECTS:commonobjs>)
target_link_libraries(arithmeticbm pniio)

#add_executable(iteratorbm ${ITERATOR_BM_SRC} $<TARGET_OBJECTS:commonobjs>)
#target_link_libraries(iteratorbm pniio)

#add_executable(multiindexbm ${MULTIINDEX_BM_SRC} $<TARGET_OBJECTS:commonobjs>)
#target_link_libraries(multiindexbm pniio)

#add_executable(indexmapbm ${INDEXMAP_BM_SRC} $<TARGET_OBJECTS:commonobjs>)
#target_link_libraries(indexmapbm pniio )

#install(TARGETS arithmeticbm  
#                iteratorbm 
#                multiindexbm
#                indexmapbm
#                DESTINATION ${CMAKE_INSTALL_BINDIR})

