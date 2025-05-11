cmake_minimum_required(VERSION 3.13)
project(INHA_Algorithm_003)

set(CMAKE_CXX_STANDARD 14)

# Find GTest
find_package(GTest REQUIRED)

# Red-Black Tree
add_executable(INHA_Algorithm_003 src/red_black_tree.cpp)

# Test codes (Based on Non-main Red-Black Tree version.)
add_executable(RBTComparatorTest test/comparator_test.cpp)
target_link_libraries(RBTComparatorTest ${GTEST_LIBRARIES} pthread)

add_executable(RBTSiblingTest test/sibling_test.cpp)
target_link_libraries(RBTSiblingTest ${GTEST_LIBRARIES} pthread)

add_executable(RBTIsBlackTest test/is_black_test.cpp)
target_link_libraries(RBTIsBlackTest ${GTEST_LIBRARIES} pthread)

add_executable(RBTDoubleRedTest test/double_red_test.cpp)
target_link_libraries(RBTDoubleRedTest ${GTEST_LIBRARIES} pthread)