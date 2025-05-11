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

// If sibling_node's color is red,
TEST(RBTIsBlack, Test1) {
  Node *silbling_node =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);

  RBT *rbt = new RBT();

  bool isBlack = rbt->isBlack(silbling_node);

  EXPECT_EQ(isBlack, false);
}

// If sibling_node's color is black,
TEST(RBTIsBlack, Test2) {
  Node *silbling_node =
      new Node(12210795, "Algorithm", "Kim", 6, "01012341234", 1711516800);
  silbling_node->color = 'B';

  RBT *rbt = new RBT();

  bool isBlack = rbt->isBlack(silbling_node);

  EXPECT_EQ(isBlack, true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
/*
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from RBTIsBlack
[ RUN      ] RBTIsBlack.Test1
[       OK ] RBTIsBlack.Test1 (0 ms)
[ RUN      ] RBTIsBlack.Test2
[       OK ] RBTIsBlack.Test2 (0 ms)
[----------] 2 tests from RBTIsBlack (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
*/