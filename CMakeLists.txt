#===============================================================================
#
#     __  ___          __      __   ______            __   __ __ _ __
#    /  |/  /___  ____/ /___ _/ /  /_  __/___  ____  / /  / //_/(_) /_
#   / /|_/ / __ \/ __  / __ `/ /    / / / __ \/ __ \/ /  / ,<  / / __/
#  / /  / / /_/ / /_/ / /_/ / /    / / / /_/ / /_/ / /  / /| |/ / /
# /_/  /_/\____/\__,_/\__,_/_/    /_/  \____/\____/_/  /_/ |_/_/\__/
#
# Modal Tool Kit
#
# Author: Christopher A. Lupp
#
# University of Michigan
# Active Aeroelasticity and Structures Research Lab
#
#===============================================================================


# Prevent In-Source Build
#-------------------------------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
   message(SEND_ERROR "In-source builds are not allowed. Create a build
   directory and try again.")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})


# CMake Configurations (including system specific)
#-------------------------------------------------------------------------------
if(WIN32)
    cmake_minimum_required (VERSION 3.9)
else()
    cmake_minimum_required (VERSION 3.3)
endif()

set_property(
             GLOBAL PROPERTY
             USE_FOLDERS ON
             )

# Set UM/NAST Version
#-------------------------------------------------------------------------------
project(MTK
        VERSION 2.0.0
        )

set(REVISION "Revision ${MTK_VERSION_PATCH}")


# ---------- Setup output Directories -------------------------
set(
    CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/lib
    CACHE PATH
    "Single Directory for all Libraries"
   )

# --------- Setup the Executable output Directory -------------
set(
     CMAKE_RUNTIME_OUTPUT_DIRECTORY
     ${PROJECT_BINARY_DIR}/bin
     CACHE PATH
     "Single Directory for all Executables."
   )




# if macos, search for installed libraries before looking for frameworks
if(APPLE)
    set(CMAKE_FIND_FRAMEWORK LAST CACHE STRING "order of macos frameworks")
endif(APPLE)


# C++ Compiler Flags
#-------------------------------------------------------------------------------
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support.
        Please use a different C++ compiler.")
endif()

if(UNIX)
    SET ( CMAKE_C_FLAGS   "-fPIC" CACHE STRING "compile flags" FORCE)
    SET ( CMAKE_CXX_FLAGS   "-fPIC" CACHE STRING "compile flags" FORCE)
endif(UNIX)


IF(WIN32)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /bigobj")
ENDIF()


# CMake module path
#-------------------------------------------------------------------------------
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


# Add Eigen
#-------------------------------------------------------------------------------

# find package (mandatory)
find_package(Eigen3 3.3.4 REQUIRED)

# include Eigen3
include_directories(${EIGEN3_INCLUDE_DIR})


# Create MTK library
#-------------------

# add MTK headers
include_directories(include)


# set header files for the library
set(HEADERS
    include/modaltools.h
    include/modetracking.h
    include/mtk_datatypes.h
    )


# Python Interface
#-----------------
add_subdirectory(python)


# Set up testing
#---------------
set(
    BUILD_TEST
    FALSE
    CACHE BOOL "Build regression tests"
    )

if(BUILD_TEST)
    enable_testing()
    add_subdirectory("test")
endif(BUILD_TEST)



# Configure installation
#-----------------------

# install directories
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/MTK/include )

# install files
install(FILES ${HEADERS} DESTINATION "${INCLUDE_INSTALL_DIR}")



# Cmake Package Configuration
#----------------------------
include(CMakePackageConfigHelpers)

configure_package_config_file(cmake/MTKConfig.cmake.in
  MTKConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/MTK/cmake
  PATH_VARS INCLUDE_INSTALL_DIR)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/MTKConfigVersion.cmake
  VERSION ${MTK_VERSION_MAJOR}.${MTK_VERSION_MINOR}.${MTK_VERSION_PATCH}
  COMPATIBILITY SameMajorVersion )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MTKConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/MTKConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/MTK/cmake )

export(PACKAGE MTK)