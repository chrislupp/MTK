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

project(MTK VERSION 1.0.0)


# Find Eigen
find_package(Eigen 3.0.0 REQUIRED)


# Create MTK library
#-------------------

# set source files for the library
set(SRC
    src/datatypes.cpp
    src/modetracking.cpp
    src/modaltools.cpp
    )


# set header files for the library
set(HEADERS
    include/modaltools.h
    include/modetracking.h
    include/mtk_datatypes.h
    )


# create the library
add_library(MTK ${SRC} ${HEADERS})


# Configure installation
#-----------------------

# install directories
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/MTK/include )

# install files
install(FILES ${HEADERS} DESTINATION "${INCLUDE_INSTALL_DIR}")


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