set(INDEX_MAP_BM_SRC index_map_bm.cpp)


include_directories(${PNICORE_INCLUDE_DIRS})
add_executable(index_map_bm ${INDEX_MAP_BM_SRC})
target_link_libraries(index_map_bm ${PNICORE_LIBRARIES})
