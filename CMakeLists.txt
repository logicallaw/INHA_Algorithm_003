cmake_minimum_required(VERSION 3.13)
project(INHA_Algorithm_003)

set(CMAKE_CXX_STANDARD 14)

# Find GTest
find_package(GTest REQUIRED)

# Red-Black Tree
add_executable(INHA_Algorithm_003 src/design_assignment_01/red_black_tree.cpp)

# Test codes (Based on Non-main Red-Black Tree version.)
add_executable(RBTComparatorTest test/design_assignment_01/comparator_test.cpp)
target_link_libraries(RBTComparatorTest ${GTEST_LIBRARIES} pthread)

add_executable(RBTSiblingTest test/design_assignment_01/sibling_test.cpp)
target_link_libraries(RBTSiblingTest ${GTEST_LIBRARIES} pthread)

add_executable(RBTIsBlackTest test/design_assignment_01/is_black_test.cpp)
target_link_libraries(RBTIsBlackTest ${GTEST_LIBRARIES} pthread)

add_executable(RBTDoubleRedTest test/design_assignment_01/double_red_test.cpp)
target_link_libraries(RBTDoubleRedTest ${GTEST_LIBRARIES} pthread)

add_executable(RBTBinarySearchTest test/design_assignment_01/binary_search_test.cpp)
target_link_libraries(RBTBinarySearchTest ${GTEST_LIBRARIES} pthread)


# KMP Algorithm
add_executable(KMP_Algorithm others/kmp_algorithm.cpp)


# Boyer-Moore Algorithm
add_executable(BoyerMooreAlgorithm others/boyer_moore_algorithm.cpp)
