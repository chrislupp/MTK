
add_executable(TestEigenPair test_eigen_pair.cpp)
target_link_libraries(TestEigenPair GTest::gtest_main)

add_executable(TestModeSet test_mode_set.cpp)
target_link_libraries(TestModeSet GTest::gtest_main)

add_executable(TestMAC test_mac.cpp)
target_link_libraries(TestMAC GTest::gtest_main)

add_executable(TestModeTracking test_mode_tracking.cpp)
target_link_libraries(TestModeTracking GTest::gtest_main)
