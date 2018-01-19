set(PNIIOBM_SRC benchmark_factory.cpp 
                file_io_benchmark.cpp 
                pniiobm.cpp 
                pniiobm_utils.cpp)

add_executable(pniiobm ${PNIIOBM_SRC} $<TARGET_OBJECTS:commonobjs>)
target_link_libraries(pniiobm pniio)

install(TARGETS pniiobm  DESTINATION ${CMAKE_INSTALL_BINDIR})

