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

// Case1: if cur_node is nullptr,
TEST(RBTBinarySearchTest, Test1) {
  Node *cur_node = nullptr;
  pair<int, string> key(12210795, "Algorithm");

  RedBlackTree *rbt = new RedBlackTree();

  pair<Node *, char> par_node = rbt->searchParentOrSelf(cur_node, key);
  pair<Node *, char> expected_value(nullptr, 'E');
  EXPECT_EQ(par_node, expected_value);
}

// Case2: if new_node is node5's right child.
TEST(RBTBinarySearchTest, Test2) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 5, "01012345678", 1711516800);
  Node *node2 =
      new Node(12200795, "Algorithm", "Lee", 4, "01023456789", 1811516800);
  Node *node3 =
      new Node(12220795, "Algorithm", "Choi", 5, "01045678901", 2011516800);
  Node *node4 =
      new Node(12190795, "Algorithm", "Park", 4, "01034567890", 1911516800);
  Node *node5 =
      new Node(12230795, "Algorithm", "Jung", 6, "01056789012", 2111516800);

  node1->color = 'B';
  node1->left_child = node2;
  node2->parent_node = node1;
  node2->color = 'R';
  node1->right_child = node3;
  node3->parent_node = node1;

  node2->left_child = node4;
  node4->parent_node = node2;
  node4->color = 'B';

  node3->right_child = node5;
  node5->parent_node = node3;
  node5->color = 'B';

  Node *root = node1;
  Node *new_node =
      new Node(12231795, "Algorithm", "Kim", 5, "01045678901", 2011516800);

  RedBlackTree *rbt = new RedBlackTree();
  pair<Node *, char> result = rbt->searchParentOrSelf(root, new_node->key);
  EXPECT_EQ(result.first, node5);
  EXPECT_EQ(result.second, 'R');
}

// Case3: if  new_node is node5's left child.
TEST(RBTBinarySearchTest, Test3) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 5, "01012345678", 1711516800);
  Node *node2 =
      new Node(12200795, "Algorithm", "Lee", 4, "01023456789", 1811516800);
  Node *node3 =
      new Node(12220795, "Algorithm", "Choi", 5, "01045678901", 2011516800);
  Node *node4 =
      new Node(12190795, "Algorithm", "Park", 4, "01034567890", 1911516800);
  Node *node5 =
      new Node(12230795, "Algorithm", "Jung", 6, "01056789012", 2111516800);

  node1->color = 'B';
  node1->left_child = node2;
  node2->parent_node = node1;
  node2->color = 'R';
  node1->right_child = node3;
  node3->parent_node = node1;

  node2->left_child = node4;
  node4->parent_node = node2;
  node4->color = 'B';

  node3->right_child = node5;
  node5->parent_node = node3;
  node5->color = 'B';

  Node *root = node1;
  Node *new_node =
      new Node(12221795, "Algorithm", "Kim", 5, "01045678901", 2011516800);

  RedBlackTree *rbt = new RedBlackTree();
  pair<Node *, char> result = rbt->searchParentOrSelf(root, new_node->key);
  EXPECT_EQ(result.first, node5);
  EXPECT_EQ(result.second, 'L');
}

// Case4: if new_node is node3's left child.
TEST(RBTBinarySearchTest, Test4) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 5, "01012345678", 1711516800);
  Node *node2 =
      new Node(12200795, "Algorithm", "Lee", 4, "01023456789", 1811516800);
  Node *node3 =
      new Node(12220795, "Algorithm", "Choi", 5, "01045678901", 2011516800);
  Node *node4 =
      new Node(12190795, "Algorithm", "Park", 4, "01034567890", 1911516800);
  Node *node5 =
      new Node(12230795, "Algorithm", "Jung", 6, "01056789012", 2111516800);

  node1->color = 'B';
  node1->left_child = node2;
  node2->parent_node = node1;
  node2->color = 'R';
  node1->right_child = node3;
  node3->parent_node = node1;

  node2->left_child = node4;
  node4->parent_node = node2;
  node4->color = 'B';

  node3->right_child = node5;
  node5->parent_node = node3;
  node5->color = 'B';

  Node *root = node1;
  Node *new_node =
      new Node(12211795, "Algorithm", "Kim", 5, "01045678901", 2011516800);

  RedBlackTree *rbt = new RedBlackTree();
  pair<Node *, char> result = rbt->searchParentOrSelf(root, new_node->key);
  EXPECT_EQ(result.first, node3);
  EXPECT_EQ(result.second, 'L');
}

// Case5: if new_node is node2's right child.
TEST(RBTBinarySearchTest, Test5) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 5, "01012345678", 1711516800);
  Node *node2 =
      new Node(12200795, "Algorithm", "Lee", 4, "01023456789", 1811516800);
  Node *node3 =
      new Node(12220795, "Algorithm", "Choi", 5, "01045678901", 2011516800);
  Node *node4 =
      new Node(12190795, "Algorithm", "Park", 4, "01034567890", 1911516800);
  Node *node5 =
      new Node(12230795, "Algorithm", "Jung", 6, "01056789012", 2111516800);

  node1->color = 'B';
  node1->left_child = node2;
  node2->parent_node = node1;
  node2->color = 'R';
  node1->right_child = node3;
  node3->parent_node = node1;

  node2->left_child = node4;
  node4->parent_node = node2;
  node4->color = 'B';

  node3->right_child = node5;
  node5->parent_node = node3;
  node5->color = 'B';

  Node *root = node1;
  Node *new_node =
      new Node(12201795, "Algorithm", "Kim", 5, "01045678901", 2011516800);

  RedBlackTree *rbt = new RedBlackTree();
  pair<Node *, char> result = rbt->searchParentOrSelf(root, new_node->key);
  EXPECT_EQ(result.first, node2);
  EXPECT_EQ(result.second, 'R');
}

// Case6: if new_node is node4's left child.
TEST(RBTBinarySearchTest, Test6) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 5, "01012345678", 1711516800);
  Node *node2 =
      new Node(12200795, "Algorithm", "Lee", 4, "01023456789", 1811516800);
  Node *node3 =
      new Node(12220795, "Algorithm", "Choi", 5, "01045678901", 2011516800);
  Node *node4 =
      new Node(12190795, "Algorithm", "Park", 4, "01034567890", 1911516800);
  Node *node5 =
      new Node(12230795, "Algorithm", "Jung", 6, "01056789012", 2111516800);

  node1->color = 'B';
  node1->left_child = node2;
  node2->parent_node = node1;
  node2->color = 'R';
  node1->right_child = node3;
  node3->parent_node = node1;

  node2->left_child = node4;
  node4->parent_node = node2;
  node4->color = 'B';

  node3->right_child = node5;
  node5->parent_node = node3;
  node5->color = 'B';

  Node *root = node1;
  Node *new_node =
      new Node(12190695, "Algorithm", "Kim", 5, "01045678901", 2011516800);

  RedBlackTree *rbt = new RedBlackTree();
  pair<Node *, char> result = rbt->searchParentOrSelf(root, new_node->key);
  EXPECT_EQ(result.first, node4);
  EXPECT_EQ(result.second, 'L');
}

// Case7: if new_node is node4's right child.
TEST(RBTBinarySearchTest, Test7) {
  Node *node1 =
      new Node(12210795, "Algorithm", "Kim", 5, "01012345678", 1711516800);
  Node *node2 =
      new Node(12200795, "Algorithm", "Lee", 4, "01023456789", 1811516800);
  Node *node3 =
      new Node(12220795, "Algorithm", "Choi", 5, "01045678901", 2011516800);
  Node *node4 =
      new Node(12190795, "Algorithm", "Park", 4, "01034567890", 1911516800);
  Node *node5 =
      new Node(12230795, "Algorithm", "Jung", 6, "01056789012", 2111516800);

  node1->color = 'B';
  node1->left_child = node2;
  node2->parent_node = node1;
  node2->color = 'R';
  node1->right_child = node3;
  node3->parent_node = node1;

  node2->left_child = node4;
  node4->parent_node = node2;
  node4->color = 'B';

  node3->right_child = node5;
  node5->parent_node = node3;
  node5->color = 'B';

  Node *root = node1;
  Node *new_node =
      new Node(12191695, "Algorithm", "Kim", 5, "01045678901", 2011516800);

  RedBlackTree *rbt = new RedBlackTree();
  pair<Node *, char> result = rbt->searchParentOrSelf(root, new_node->key);
  EXPECT_EQ(result.first, node4);
  EXPECT_EQ(result.second, 'R');
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
/*
[==========] Running 7 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 7 tests from RBTBinarySearchTest
[ RUN      ] RBTBinarySearchTest.Test1
[       OK ] RBTBinarySearchTest.Test1 (0 ms)
[ RUN      ] RBTBinarySearchTest.Test2
[       OK ] RBTBinarySearchTest.Test2 (0 ms)
[ RUN      ] RBTBinarySearchTest.Test3
[       OK ] RBTBinarySearchTest.Test3 (0 ms)
[ RUN      ] RBTBinarySearchTest.Test4
[       OK ] RBTBinarySearchTest.Test4 (0 ms)
[ RUN      ] RBTBinarySearchTest.Test5
[       OK ] RBTBinarySearchTest.Test5 (0 ms)
[ RUN      ] RBTBinarySearchTest.Test6
[       OK ] RBTBinarySearchTest.Test6 (0 ms)
[ RUN      ] RBTBinarySearchTest.Test7
[       OK ] RBTBinarySearchTest.Test7 (0 ms)
[----------] 7 tests from RBTBinarySearchTest (0 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 7 tests.
*/