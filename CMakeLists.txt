cmake_minimum_required (VERSION 3.9)

project(MTK
    VERSION 4.0.0
    )


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


# flag for building the regression tests
set(BUILD_TESTS FALSE CACHE BOOL "Build regression tests")
set(BUILD_DOCS FALSE CACHE BOOL "Build documentation")


# Add Eigen
find_package(Eigen3 REQUIRED 3.4)
include_directories(${EIGEN3_INCLUDE_DIR})

message("Eigen include directory: " ${EIGEN3_INCLUDE_DIR})


include_directories(include)



if(BUILD_DOCS)
    add_subdirectory(docs)
endif()



if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include(GoogleTest)
    add_subdirectory(test)
endif()