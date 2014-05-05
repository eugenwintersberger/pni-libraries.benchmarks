set(COMMON_SRC utils.cpp)

include_directories(${PNICORE_INCLUDE_DIRS})
add_library(commonobjs OBJECT ${COMMON_SRC})
