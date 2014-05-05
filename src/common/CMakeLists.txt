set(COMMON_SRC utils.cpp configuration.cpp)

configure_file(config.hpp.cmake config.hpp @ONLY)
include_directories(${PNICORE_INCLUDE_DIRS})
add_library(commonobjs OBJECT ${COMMON_SRC})
