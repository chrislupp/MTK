#===============================================================================
#
#     __  ___          __      __   ______            __   __ __ _ __
#    /  |/  /___  ____/ /___ _/ /  /_  __/___  ____  / /  / //_/(_) /_
#   / /|_/ / __ \/ __  / __ `/ /    / / / __ \/ __ \/ /  / ,<  / / __/
#  / /  / / /_/ / /_/ / /_/ / /    / / / /_/ / /_/ / /  / /| |/ / /
# /_/  /_/\____/\__,_/\__,_/_/    /_/  \____/\____/_/  /_/ |_/_/\__/
#
#
# University of Michigan
# Active Aeroelasticity and Structures Research Lab
#
# Author: Christopher A. Lupp
#
# Main CmakeLists
#
#===============================================================================

project (MTK)


#-------------------------------------------------------------------------------
# Prevent In-Source Build
#-------------------------------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
   message(SEND_ERROR "In-source builds are not allowed. Create a build directory
   and try again.")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})


#-------------------------------------------------------------------------------
# CMake Configurations
#-------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# add cmake find scripts
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


#-------------------------------------------------------------------------------
# Add Eigen
#-------------------------------------------------------------------------------

# find package as mark as REQUIRED
find_package(Eigen3 REQUIRED)

# include Eigen3
include_directories(${EIGEN3_INCLUDE_DIR})

message(${EIGEN3_INCLUDE_DIR})


#-------------------------------------------------------------------------------
# Add HDF5
#-------------------------------------------------------------------------------

# find HDF5 package (must be installed seperately)
set(HDF5_USE_STATIC_LIBRARIES TRUE)
find_package(HDF5 COMPONENTS CXX)

if(NOT HDF5_FOUND)
    set(HDF5_INTERNAL_BUILD TRUE)
endif()

# include HDF5 headers (only from release install)
include_directories(${HDF5_INCLUDE_DIRS})

if(NOT HDF5_INTERNAL_BUILD)
    if(EXISTS "$ENV{HDF5_DEBUG_DIR}")
        set(HDF5_DEBUG_LIB
            "$ENV{HDF5_DEBUG_DIR}/lib/libhdf5_hl_cpp_D.lib;$ENV{HDF5_DEBUG_DIR}/lib/libhdf5_cpp_D.lib;$ENV{HDF5_DEBUG_DIR}/lib/libhdf5_D.lib;")
        if(EXISTS $ENV{HDF5_DEBUG_DIR}/lib/libszip_D.lib)
            set(HDF5_DEBUG_LIB ${HDF5_DEBUG_LIB} "$ENV{HDF5_DEBUG_DIR}/lib/libszip_D.lib")
        endif()

        if(EXISTS $ENV{HDF5_DEBUG_DIR}/lib/libzlib_D.lib)
            set(HDF5_DEBUG_LIB ${HDF5_DEBUG_LIB} "$ENV{HDF5_DEBUG_DIR}/lib/libzlib_D.lib")
        endif()
        
        message("Found HDF5 debug libraries.")
        message("HDF5 debug library location: " $ENV{HDF5_DEBUG_DIR})
    else()
        message("No HDF5 debug libraries found. Debug build will fail!")
    endif()
endif()

# cache the HDF5 debug path variable
set(HDF5_DEBUG_DIR $ENV{HDF5_DEBUG_DIR} CACHE STRING "HDF5 Debug root")


#-------------------------------------------------------------------------------
# Add MTK headers
#-------------------------------------------------------------------------------
include_directories("./include")


#-------------------------------------------------------------------------------
# Add subdirectories
#-------------------------------------------------------------------------------
add_subdirectory("testcases")


#===============================================================================
# Generate Documentation
#===============================================================================
# cache the BUILD_DOC variable. must be enabled by user to build documentation
set(BUILD_DOC FALSE CACHE BOOL "Build documentation")

if(BUILD_DOC)
    # find sphinx
    find_package(Sphinx REQUIRED)

    # Sphinx cache with pickled ReST documents
    set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")

    # HTML output directory
    set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/doc")

    add_custom_target(mtk_documentation ALL
    ${SPHINX_EXECUTABLE}
        -q -b html
        -d "${SPHINX_CACHE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/doc"
        "${SPHINX_HTML_DIR}"
    COMMENT "Building HTML documentation using Sphinx.")
endif()