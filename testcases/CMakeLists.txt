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
# Benchmark CMakeLists
#
#===============================================================================

project (MTK-Benchmarks)


#-------------------------------------------------------------------------------
# Modal Functions Benchmark
#-------------------------------------------------------------------------------
add_executable(modal_functions modal_func.cpp)


if(NOT HDF5_INTERNAL_BUILD)
    target_link_libraries(modal_functions optimized ${HDF5_LIBRARIES})
    if(EXISTS "$ENV{HDF5_DEBUG_DIR}")
        target_link_libraries(modal_functions debug ${HDF5_DEBUG_LIB})
    endif()
else()
    target_link_libraries(modal_functions optimized 
        hdf5-static
        hdf5_hl_cpp-static
        hdf5_cpp-static
        ${LIBSZ}
        ${LIBZ}
        )
endif()


#-------------------------------------------------------------------------------
# Mode Tracking Benchmark
#-------------------------------------------------------------------------------
add_executable(mode_tracking mode_tracking.cpp)


if(NOT HDF5_INTERNAL_BUILD)
    target_link_libraries(mode_tracking optimized ${HDF5_LIBRARIES})
    if(EXISTS "$ENV{HDF5_DEBUG_DIR}")
        target_link_libraries(mode_tracking debug ${HDF5_DEBUG_LIB})
    endif()
else()
    target_link_libraries(mode_tracking optimized 
        hdf5-static
        hdf5_hl_cpp-static
        hdf5_cpp-static
        ${LIBSZ}
        ${LIBZ}
        )
endif()