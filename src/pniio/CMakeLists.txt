set(PNIIOBM_SRC benchmark_factory.cpp file_io_benchmark.cpp pniiobm.cpp)


link_directories(${PNIIO_LIBRARY_DIRS})
include_directories(${PNIIO_INCLUDE_DIRS})

add_executable(pniiobm ${PNIIOBM_SRC} $<TARGET_OBJECTS:commonobjs>)
target_link_libraries(pniiobm ${PNIIO_LIBRARIES})

install(TARGETS pniiobm  DESTINATION ${CMAKE_INSTALL_BINDIR})

