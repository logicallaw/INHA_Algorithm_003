/*
 * This is file of the project 2025_Lecture_Algorithm
 * Licensed under the MIT License.
 * Copyright (c) 2025 Junho Kim
 * For full license text, see the LICENSE file in the root directory or at
 * https://opensource.org/license/mit
 * Author: Junho Kim
 * Latest Updated Date: 2025-05-11
 */
#include "../src/non_main_red_black_tree.cpp"
#include <gtest/gtest.h>

// Case1: return node1's left child(node3's sibling).
TEST(RBTSibling, Test1) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);
  Node *node2 =
      new Node(12200795, "Algorithm", "Kim", 6, "01012341234", 1711516800);
  Node *node3 =
      new Node(12220795, "Algorithm", "Kim", 6, "01012341234", 1711516800);

  node1->color = 'B';
  node1->left_child = node2;
  node2->parent_node = node1;

  node1->right_child = node3;
  node3->parent_node = node1;

  RedBlackTree *rbt = new RedBlackTree();
  Node *result = rbt->sibling(node3);
  EXPECT_EQ(result, node2);
}

// Case2: return node1's right child(node2's sibling).
TEST(RBTSibling, Test2) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);
  Node *node2 =
      new Node(12200795, "Algorithm", "Kim", 6, "01012341234", 1711516800);
  Node *node3 =
      new Node(12220795, "Algorithm", "Kim", 6, "01012341234", 1711516800);

  node1->color = 'B';
  node1->left_child = node2;
  node2->parent_node = node1;

  node1->right_child = node3;
  node3->parent_node = node1;

  RedBlackTree *rbt = new RedBlackTree();
  Node *result = rbt->sibling(node2);
  EXPECT_EQ(result, node3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
/*
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from RBTSibling
[ RUN      ] RBTSibling.Test1
[       OK ] RBTSibling.Test1 (0 ms)
[ RUN      ] RBTSibling.Test2
[       OK ] RBTSibling.Test2 (0 ms)
[----------] 2 tests from RBTSibling (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
*/