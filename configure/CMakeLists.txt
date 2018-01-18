include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)
include(FindBoost)
include(FindPkgConfig)

if(NOT PKG_CONFIG_FOUND)
    message("Could not find pkg-config ... try without it!")
endif()
   
#setup for GNU CXX compiler
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    message("found GNU compiler ...")
    add_definitions(-g)
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_definitions(-O3)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_definitions(-O0 -fno-inline -DDEBUG)
    endif()
endif()

find_package(pniio REQUIRED)


