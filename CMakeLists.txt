#===============================================================================
#
#     Modal Tool Kit (MTK)
#
#     Copyright 2017 Christopher A. Lupp
#
#     Licensed under the Apache License, Version 2.0 (the "License");
#     you may not use this file except in compliance with the License.
#     You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#     Unless required by applicable law or agreed to in writing, software
#     distributed under the License is distributed on an "AS IS" BASIS,
#     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#     See the License for the specific language governing permissions and
#     limitations under the License.
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

# Set MTK Version
#-------------------------------------------------------------------------------
project(MTK
        VERSION 2.3.0
        )

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH
    "Single Directory for all Executables."
)


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