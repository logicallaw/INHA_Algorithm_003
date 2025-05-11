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

// Output: grandparent's left child.
TEST(RBTSibling, Test1) {
  Node *grand_parent_node =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);
  grand_parent_node->color = 'B';

  Node *parLeft_child =
      new Node(12200795, "Misaso", "Lee", 6, "01012341234", 1811516800);
  Node *parRight_child =
      new Node(12220795, "Algorithm", "Park", 6, "01012341234", 1911516800);

  parLeft_child->parent_node = grand_parent_node;
  grand_parent_node->left_child = parLeft_child;

  parRight_child->parent_node = grand_parent_node;
  grand_parent_node->right_child = parRight_child;

  Node *rightChild_right_child =
      new Node(12230795, "Algorithm", "Kim", 3, "01012341234", 1921516800);

  rightChild_right_child->parent_node = parRight_child;
  parRight_child->right_child = rightChild_right_child;

  RBT *rbt = new RBT();

  Node *found_sibling = rbt->sibling(rightChild_right_child);
  EXPECT_EQ(found_sibling, parLeft_child);
}

// Output: grandparent's right child.
TEST(RBTSibling, Test2) {
  Node *grand_parent_node =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);
  grand_parent_node->color = 'B';

  Node *parLeft_child =
      new Node(12200795, "Misaso", "Lee", 6, "01012341234", 1811516800);
  Node *parRight_child =
      new Node(12220795, "Algorithm", "Park", 6, "01012341234", 1911516800);

  parLeft_child->parent_node = grand_parent_node;
  grand_parent_node->left_child = parLeft_child;

  parRight_child->parent_node = grand_parent_node;
  grand_parent_node->right_child = parRight_child;

  Node *leftChild_right_child =
      new Node(12230795, "Algorithm", "Kim", 3, "01012341234", 1921516800);

  leftChild_right_child->parent_node = parLeft_child;
  parLeft_child->right_child = leftChild_right_child;

  RBT *rbt = new RBT();

  Node *found_sibling = rbt->sibling(leftChild_right_child);
  EXPECT_EQ(found_sibling, parRight_child);
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