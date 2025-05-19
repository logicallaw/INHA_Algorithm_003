// WARNING: This file is deprecated and no longer maintained as of May 17, 2025.
// Do not modify unless absolutely necessary.
// Future support or updates are not guaranteed.
/*
 * This is file of the project 2025_Lecture_Algorithm
 * Licensed under the MIT License.
 * Copyright (c) 2025 Junho Kim
 * For full license text, see the LICENSE file in the root directory or at
 * https://opensource.org/license/mit
 * Author: Junho Kim
 * Latest Updated Date: 2025-05-19
 */
#include "../../src/design_assignment_01/non_main_red_black_tree.cpp"
#include <gtest/gtest.h>

TEST(RBTComparator, Test1) {
  pair<int, string> comp1(12200795, "Algorithm");
  pair<int, string> comp2(12210795, "Misaso");

  RedBlackTree *rbt = new RedBlackTree();
  int result = rbt->comparator(comp1, comp2);
  EXPECT_EQ(result, 1);
}

TEST(RBTComparator, Test2) {
  pair<int, string> comp1(12220795, "Algorithm");
  pair<int, string> comp2(12210795, "Misaso");

  RedBlackTree *rbt = new RedBlackTree();
  int result = rbt->comparator(comp1, comp2);
  EXPECT_EQ(result, -1);
}

TEST(RBTComparator, Test3) {
  pair<int, string> comp1(12210795, "Algorithm");
  pair<int, string> comp2(12210795, "Misaso");

  RedBlackTree *rbt = new RedBlackTree();
  int result = rbt->comparator(comp1, comp2);
  EXPECT_EQ(result, 1);
}

TEST(RBTComparator, Test4) {
  pair<int, string> comp1(12210795, "Misaso");
  pair<int, string> comp2(12210795, "Algorith");

  RedBlackTree *rbt = new RedBlackTree();
  int result = rbt->comparator(comp1, comp2);
  EXPECT_EQ(result, -1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
/*
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from RBTComparator
[ RUN      ] RBTComparator.Test1
[       OK ] RBTComparator.Test1 (0 ms)
[ RUN      ] RBTComparator.Test2
[       OK ] RBTComparator.Test2 (0 ms)
[ RUN      ] RBTComparator.Test3
[       OK ] RBTComparator.Test3 (0 ms)
[ RUN      ] RBTComparator.Test4
[       OK ] RBTComparator.Test4 (0 ms)
[----------] 4 tests from RBTComparator (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
*/