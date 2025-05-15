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
  RBT() : tree_root(nullptr), tree_size(0) {}

  void insert(const int &sid, const string &subject, const string &sname,
              const int &semester, const string &phone, const int &timestamp) {
    Node *new_node = new Node(sid, subject, sname, semester, phone, timestamp);

    // If new_node is a root
    if (tree_size == 0) {
      new_node->color = 'B';
      tree_root = new_node;
      tree_size++;
      return;
    }

    // 삽입할 위치의 부모를 찾자.
    pair<Node *, char> par_location = binarySearch(tree_root, new_node->key);
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
        break;
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
    if (cur_node->color == 'B') {
      return false;
    }
    if (cur_node->parent_node == nullptr) {
      return false;
    }
    return (cur_node->parent_node->color == 'R');
  }

  bool isBlack(Node *sibling_node) {
    if (sibling_node == nullptr || sibling_node->color == 'B') {
      return true;
    }
    return false;
  }

  Node *sibling(Node *cur_node) {
    Node *par_node = cur_node->parent_node;
    if (par_node->left_child == cur_node) {
      return par_node->right_child;
    }
    if (par_node->right_child == cur_node) {
      return par_node->left_child;
    }
  }

  Node *restructure(Node *cur_node) {
    Node *par_node = cur_node->parent_node;
    Node *grand_par_node = par_node->parent_node;

    if (grand_par_node->right_child == par_node) {
      // RL
      if (par_node->left_child == cur_node) {
        cur_node->color = 'B';
        par_node->color = 'R';
        grand_par_node->color = 'R';
        rotateRight(par_node);
        rotateLeft(grand_par_node);
      }
      // RR
      else {
        par_node->color = 'B';
        cur_node->color = 'R';
        grand_par_node->color = 'R';
        rotateLeft(grand_par_node);
      }
    } else {
      // LL
      if (par_node->left_child == cur_node) {
        par_node->color = 'B';
        cur_node->color = 'R';
        grand_par_node->color = 'R';
        rotateRight(grand_par_node);
      }
      // LR
      else {
        cur_node->color = 'B';
        par_node->color = 'R';
        grand_par_node->color = 'R';
        rotateLeft(par_node);
        rotateRight(grand_par_node);
      }
    }
  }

  void *rotateRight(Node *old_root) {
    Node *new_root = old_root->left_child;
    Node *middle_subtree = new_root->right_child;

    new_root->right_child = old_root;
    old_root->left_child = middle_subtree;

    if (middle_subtree) {
      middle_subtree->parent_node = old_root;
    }
    new_root->parent_node = old_root->parent_node;
    old_root->parent_node = new_root;

    if (new_root->parent_node) {
      if (comparator(new_root->parent_node->key, new_root->key) > 0) {
        new_root->parent_node->right_child = new_root;
      }
      if (comparator(new_root->parent_node->key, new_root->key) < 0) {
        new_root->parent_node->left_child = new_root;
      }
    }

    if (new_root->parent_node == nullptr) {
      tree_root = new_root;
    }
  }

  void *rotateLeft(Node *old_root) {
    Node *new_root = old_root->right_child;
    Node *middle_subtree = new_root->left_child;

    new_root->left_child = old_root;
    old_root->right_child = middle_subtree;

    if (middle_subtree) {
      middle_subtree->parent_node = old_root;
    }
    new_root->parent_node = old_root->parent_node;
    old_root->parent_node = new_root;

    if (new_root->parent_node) {
      if (comparator(new_root->parent_node->key, new_root->key) > 0) {
        new_root->parent_node->right_child = new_root;
      }
      if (comparator(new_root->parent_node->key, new_root->key) < 0) {
        new_root->parent_node->left_child = new_root;
      }
    }

    if (new_root->parent_node == nullptr) {
      tree_root = new_root;
    }
  }

  Node *recolor(Node *cur_node) {
    Node *par_node = cur_node->parent_node;
    Node *grand_par_node = par_node->parent_node;

    exchangeColor(grand_par_node);
    exchangeColor(par_node);
    exchangeColor(sibling(par_node));

    if (grand_par_node == tree_root && grand_par_node->color == 'R') {
      grand_par_node->color = 'B';
    }
  }

  void exchangeColor(Node *node) {
    char cur_color = node->color;
    switch (cur_color) {
    case 'R':
      node->color = 'B';
      break;
    case 'B':
      node->color = 'R';
      break;
    }
  }

private:
  Node *tree_root;
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