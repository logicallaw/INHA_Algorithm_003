/*
 * This is file of the project 2025_Lecture_Algorithm
 * Licensed under the MIT License.
 * Copyright (c) 2025 Junho Kim
 * For full license text, see the LICENSE file in the root directory or at
 * https://opensource.org/license/mit
 * Author: Junho Kim
 * Latest Updated Date: 2025-05-11
 */
#include <iostream>
#include <string>
using namespace std;

// Define enum.

class RBT;

class Node {
public:
  Node(const int &sid, const string &subject, const string &sname,
       const int &semester, const string &phone, const int &timestamp)
      : key(pair<int, string>(sid, subject)), sname(sname), semester(semester),
        phone(phone), timestamp(timestamp), parent_node(nullptr),
        left_child(nullptr), right_child(nullptr), color('R') {}

private:
  pair<int, string> key;
  string sname;
  int semester;
  string phone;
  int timestamp;

  int depth;
  Node *parent_node;
  Node *left_child;
  Node *right_child;

  char color;

  friend class RBT;
};

class RBT {
public:
  RBT() : root(nullptr), tree_size(0) {}

  void insert(const int &sid, const string &subject, const string &sname,
              const int &semester, const string &phone, const int &timestamp) {
    Node *new_node = new Node(sid, subject, sname, semester, phone, timestamp);

    // If new_node is a root
    if (tree_size == 0) {
      new_node->color = 'B';
      root = new_node;
      tree_size++;
      return;
    }

    // 삽입할 위치의 부모를 찾자.
    pair<Node *, char> par_location = binarySearch(root, new_node->key);
    if (par_location.first == nullptr) {
      cout << "Insertion error! You must solve this problem." << endl;
      return;
    }

    // Update parent-child relation.
    new_node->parent_node = par_location.first;

    if (par_location.second == 'L') {
      par_location.first->left_child = new_node;
    }
    if (par_location.second == 'R') {
      par_location.first->right_child = new_node;
    }
    tree_size++;

    // Check ordering condition.
    while (doubleRed(new_node)) {
      if (isBlack(sibling(new_node->parent_node))) {
        new_node = restructure(new_node);
        return;
      }
      // { sibling(new_node->parent_node) is red }
      else {
        new_node = recolor(new_node);
      }
    }
  }

  pair<Node *, char> binarySearch(Node *cur_node,
                                  const pair<int, string> &key) {
    if (cur_node == nullptr) {
      return pair<Node *, char>(nullptr, 'E');
    }

    if (comparator(cur_node->key, key) < 0) {
      if (cur_node->left_child != nullptr) {
        return binarySearch(cur_node->left_child, key);
      }
      return pair<Node *, char>(cur_node, 'L');
    }
    if (comparator(cur_node->key, key) > 0) {
      if (cur_node->right_child != nullptr) {
        return binarySearch(cur_node->right_child, key);
      }
      return pair<Node *, char>(cur_node, 'R');
    }
  }

  int comparator(const pair<int, string> &comp1,
                 const pair<int, string> &comp2) {
    if (comp1.first < comp2.first) {
      return 1;
    }
    if (comp1.first > comp2.first) {
      return -1;
    }
    // { comp1.first == comp2.first }
    if (comp1.second < comp2.second) {
      return 1;
    }
    if (comp1.second > comp2.second) {
      return -1;
    }
  }

  bool doubleRed(Node *cur_node) {
    return (cur_node->parent_node->color == 'R');
  }

  bool isBlack(Node *sibling_node) { return (sibling_node->color == 'B'); }

  Node *sibling(Node *cur_node) {
    Node *curParent_node = cur_node->parent_node;
    Node *grand_parent_node = curParent_node->parent_node;

    if (grand_parent_node->left_child == curParent_node) {
      return grand_parent_node->right_child;
    }
    if (grand_parent_node->right_child == curParent_node) {
      return grand_parent_node->left_child;
    }
  }

  Node *restructure(Node *cur_node) {}
  Node *recolor(Node *cur_node) {}

private:
  Node *root;
  int tree_size;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int test_case;
  cin >> test_case;

  RBT *red_black_tree = new RBT();

  while (test_case--) {
    char query_type;
    cin >> query_type;

    if (query_type == 'I') {
      int sid, semester, timestamp;
      string subject, sname, phone;

      cin >> sid >> subject >> sname >> semester >> phone >> timestamp;

      red_black_tree->insert(sid, subject, sname, semester, phone, timestamp);

      continue;
    }

    if (query_type == 'D') {

      continue;
    }

    if (query_type == 'L') {

      continue;
    }

    if (query_type == 'C') {

      continue;
    }

    if (query_type == 'M') {

      continue;
    }
  }

  return 0;
}