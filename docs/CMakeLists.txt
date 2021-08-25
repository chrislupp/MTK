
add_custom_target(Documentation ALL jupyter-book build .
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})