cmake_minimum_required(VERSION 2.6)
project(pnibenchmarks)

set(CMAKE_FAMILY_VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")

if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

#======================do here some setup work=================================
include(configure/CMakeLists.txt)

include_directories("src/common")
#need this to get the generated header files into the build.
add_subdirectory("src/common")
add_subdirectory("src/pnicore")
#add_subdirectory("src/pniio")

