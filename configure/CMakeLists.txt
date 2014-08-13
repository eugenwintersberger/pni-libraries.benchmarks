include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)
include(FindBoost)
include(FindPkgConfig)

if(NOT PKG_CONFIG_FOUND)
    message("Could not find pkg-config ... try without it!")
endif()
   
#setup for GNU CXX compiler
if(CMAKE_COMPILER_IS_GNUCXX)
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


#=====================need to check compiler flags=============================
#check for supported c++11 flags

#should wrap this into a macro and call it in the GNU CXX section of the
#configuration

#store the original state of CMAKE_REQUIRED_FLAGS
set(CMAKE_REQUIRED_FLAGS_ORIG "${CMAKE_REQUIRED_FLAGS}")

set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++11")
check_cxx_source_compiles("int main() { return 0; }" HAS_CXX11_FLAG)

set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++0x")
check_cxx_source_compiles("int main() { return 0; }" HAS_CXX0X_FLAG)

if(HAS_CXX11_FLAG)
    add_definitions(-std=c++11)
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++11")
else()
    if(HAS_CXX0X_FLAG)
        add_definitions(-std=c++0x)
        set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_ORIG} -std=c++0x")
    else()
        message(FATAL_ERROR,"Compiler does not support C++11 compiler flag")
    endif()
endif()

#==========================check installation configuration====================
include(configure/InstallConfig.cmake)                          

#===================================check the size of data types===============
include(configure/CheckTypeSizes.txt)

#=================try to figure out some compiler capabilities=================
include(configure/CheckCompilerCaps.txt)

#==========need to check for several libraries if they are installed=============

if(PKG_CONFIG_FOUND)
    pkg_search_module(PNICORE REQUIRED pnicore)
    pkg_search_module(CPPUNIT REQUIRED cppunit)
    pkg_search_module(PNIIO REQUIRED pniio)
endif()

