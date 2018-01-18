cmake_minimum_required(VERSION 3.3.0)
project(pnibenchmarks 
        LANGUAGES C CXX Fortran
        VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 11)

include(cmake/common/EnsureBuildType.cmake)
include(cmake/common/InstallConfig.cmake)
include(cmake/common/OutputDirConfig.cmake)
include(cmake/common/WindowsUtils.cmake)

#
# add a check target to build and run the tests
#
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_BUILD_TYPE})


# =============================================================================
# determine from which source to get dependencies
# =============================================================================
set(WITH_CONAN OFF CACHE BOOL "Satisfy dependencies with conan")

if(WITH_CONAN)
    include(cmake/common/ConanSetup.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/conan.cmake)
    
    conan_cmake_run(CONANFILE conanfile.txt
                    BASIC_SETUP
                    BUILD missing)  
endif()

#======================do here some setup work=================================
include(configure/CMakeLists.txt)

include_directories("src")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/src")
#need this to get the generated header files into the build.
add_subdirectory("src/common")
#add_subdirectory("test")
#add_subdirectory("src/pnicore")
#add_subdirectory("src/pniio")

