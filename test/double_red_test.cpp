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
 * Latest Updated Date: 2025-05-17
 */
#include "../src/non_main_red_black_tree.cpp"
#include <gtest/gtest.h>

// Case1: if cur_node->color is 'B',
TEST(RBTDoubleRed, Test1) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);

  node1->color = 'B';

  RedBlackTree *rbt = new RedBlackTree();

  bool isDoubleRed = rbt->isDoubleRed(node1);
  EXPECT_EQ(isDoubleRed, false);
}

// Case2: if cur_node->parent_node is nullptr,
TEST(RBTDoubleRed, Test2) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);

  RedBlackTree *rbt = new RedBlackTree();

  bool isDoubleRed = rbt->isDoubleRed(node1);
  EXPECT_EQ(isDoubleRed, false);
}

// Case3: if cur_node->parent->color is 'R',
TEST(RBTDoubleRed, Test3) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);
  Node *node2 =
      new Node(12220795, "Algorithm", "Lee", 6, "01012341234", 1811516800);

  node1->left_child = node2;
  node2->parent_node = node1;

  RedBlackTree *rbt = new RedBlackTree();

  bool isDoubleRed = rbt->isDoubleRed(node2);
  EXPECT_EQ(isDoubleRed, true);
}

// Case4: if cur_node->parent->color is not 'R',
TEST(RBTDoubleRed, Test4) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);
  Node *node2 =
      new Node(12220795, "Algorithm", "Lee", 6, "01012341234", 1811516800);

  node1->color = 'B';
  node1->left_child = node2;
  node2->parent_node = node1;

  RedBlackTree *rbt = new RedBlackTree();

  bool isDoubleRed = rbt->isDoubleRed(node2);
  EXPECT_EQ(isDoubleRed, false);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
/*
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from RBTDoubleRed
[ RUN      ] RBTDoubleRed.Test1
[       OK ] RBTDoubleRed.Test1 (0 ms)
[ RUN      ] RBTDoubleRed.Test2
[       OK ] RBTDoubleRed.Test2 (0 ms)
[ RUN      ] RBTDoubleRed.Test3
[       OK ] RBTDoubleRed.Test3 (0 ms)
[ RUN      ] RBTDoubleRed.Test4
[       OK ] RBTDoubleRed.Test4 (0 ms)
[----------] 4 tests from RBTDoubleRed (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
*/