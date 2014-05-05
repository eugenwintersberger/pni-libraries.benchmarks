cmake_minimum_required(VERSION 2.6)
project(pnibenchmarks C CXX Fortran)

set(CMAKE_FAMILY_VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")

if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(SOFTWARE_URL "https://code.google.com/p/pni-libraries/source/checkout?repo=benchmarks")
#need to update those guys for every new version
set(SOFTWARE_VERSION "1.0.0")
set(SOFTWARE_COMMIT "6db45b888732aa876e839358c07c804f8b6ec41a")

#======================do here some setup work=================================
include(configure/CMakeLists.txt)

include_directories("src")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/src")
#need this to get the generated header files into the build.
add_subdirectory("src/common")
add_subdirectory("test")
add_subdirectory("src/pnicore")
add_subdirectory("src/pniio")

