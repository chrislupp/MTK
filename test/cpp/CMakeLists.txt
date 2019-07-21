

add_executable(MAC mac.cpp)
add_test(MAC ${PROJECT_BINARY_DIR}/bin/MAC)

add_executable(ModeSet modeset_manip.cpp)
add_test(ModeSet ${PROJECT_BINARY_DIR}/bin/ModeSet)