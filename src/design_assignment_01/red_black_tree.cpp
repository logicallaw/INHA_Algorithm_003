/*
 * This is file of the project 2025_Lecture_Algorithm
 * Licensed under the MIT License.
 * Copyright (c) 2025 Junho Kim
 * For full license text, see the LICENSE file in the root directory or at
 * https://opensource.org/license/mit
 * Author: Junho Kim
 * Latest Updated Date: 2025-05-19
 *
 * NOTE: This file is under active maintenance as of May 18, 2025.
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>√
using namespace std;

class Node;
class RedBlackTree;

typedef pair<Node *, char> SearchResult;
typedef pair<int, string> NodeKey;
typedef pair<string, Node *> SubjectNodePair;
typedef map<int, vector<SubjectNodePair>> SidMap;
typedef map<string, vector<Node *>> SubjectMap;

enum class QueryType : char {
  kInsert = 'I',
  kListSubjects = 'L',
  kCountStudents = 'C',
  kEarliestApplicants = 'M'
};

class Node {
public:
  // Constructor: Initializes a node with student and course information.
  Node(const int &sid, const string &subject, const string &sname,
       const int &semester, const string &phone, const int &timestamp);

private:
  // Composite key: (student ID, subject name) used for tree ordering.
  NodeKey key;

  // Student name.
  string sname;

  // Semester of course registration.
  int semester;

  // Student phone number.
  string phone;

  // Timestamp of registration (used for earliest applicant logic).
  int timestamp;

  // Pointer to the parent node in the tree.
  Node *parent_node;

  // Pointer to the left child in the tree.
  Node *left_child;

  // Pointer to the right child in the tree.
  Node *right_child;

  // Node color: 'R' for red, 'B' for black (used in balancing).
  char color;

  // Grant RedBlackTree class access to private members.
  friend class RedBlackTree;
};

class RedBlackTree {
public:
  // Constructor: Initializes an empty Red-Black Tree.
  RedBlackTree();
  ~RedBlackTree();

  // Recursively deletes all nodes in the subtree rooted at 'node' using
  // post-order traversal.
  void deleteSubtree(Node *node);

  // Query Type: “I sid subject sname semester phone timestamp”
  void inquireInsert(const int &sid, const string &subject, const string &sname,
                     const int &semester, const string &phone,
                     const int &timestamp);

  // Query Type: “L sid”
  void inquireAllSubjects(const int &sid);

  // Query Type: "C subject”
  void inquireStudentNumberOfSubject(const string &subject);

  // Query Type: ”M subject K”
  void inquireEarlyStudent(const string &subject, const int &k);

private:
  // Comparator: returns true if the subject name of 'a' is lexicographically
  // less than 'b'.
  static bool subjectNameLess(const SubjectNodePair &a,
                              const SubjectNodePair &b);

  // Comparator: returns true if 'a' has an earlier timestamp than 'b'.
  static bool timestampLess(Node *&a, Node *&b);

  // Constant: Indicates that the node already exists in the tree.
  static constexpr bool kIsDuplicateNode = true;

  // Constant: Indicates that the node is newly inserted.
  static constexpr bool kIsNewlyInserted = false;

  // Message: Should never happen if logic is correct (guard message).
  static constexpr const char *kUnexpectedErrorMessage =
      "Algorithm error! You must solve this problem.";

  // Message: Displayed when no records are found for a query.
  static constexpr const char *kNoRecordsFoundMessage = "No records found";

  // Comparator constants for key ordering.
  static constexpr int kCompareLess = -1;
  static constexpr int kCompareEqual = 0;
  static constexpr int kCompareGreater = 1;

  // Checks if the tree is empty.
  bool isEmpty() const;

  // Checks whether two keys (sid, subject) are the same.
  bool isDuplicateKey(const NodeKey &a, const NodeKey &b);

  // Checks if a node is black or null (used in balancing).
  bool isBlack(Node *sibling_node);

  // Checks whether the current node and its parent are both red.
  bool isDoubleRed(Node *cur_node);

  // Returns the sibling of the current node.
  Node *getSibling(Node *cur_node);

  // Returns the depth (level) of a node from the root.
  int getNodeDepth(Node *cur_node);

  // Search for a parent or yourself.
  SearchResult searchParentOrSelf(Node *cur_node, const NodeKey &key);

  // Compares two NodeKeys (sid, subject) and returns compare constant.
  int comparator(const NodeKey &comp1, const NodeKey &comp2);

  // Prints the depth of the node and whether it was a duplicate.
  void printNodeStatus(Node *node, const bool &status);

  // Handles insertion when the tree is empty (sets new node as root).
  void handleEmptyInsert(const int &sid, const string &subject, Node *new_node);

  // Handles insertion when the node is new (not duplicate).
  void handleNewInsert(const int &sid, const string &subject, Node *parent,
                       char direction, Node *child);

  // Handles case where the node already exists (updates timestamp).
  void handleDuplicateNode(Node *existing_node, const int &new_timestamp);

  // Inserts a node into both sid_map and subject_map.
  void insertToMaps(const int &sid, const string &subject, Node *new_node);

  // Adds subject info to sid_map for a given student ID.
  void insertStudentToSidMap(const int &sid, const string &subject,
                             Node *new_node);

  // Adds student node to subject_map for the given subject.
  void insertStudentToSubjectMap(const string &subject, Node *new_node);

  // Performs restructuring when double red occurs.
  void adjustRestructure(Node *cur_node);

  // Recolors grandparent-parent-sibling nodes and returns new current node.
  Node *adjustRecolor(Node *cur_node);

  // Repeat until double red does not occur.
  void adjustRebalance(Node *cur_node);

  // Performs right rotation at the given node.
  void rotateRight(Node *old_root);

  // Performs left rotation at the given node.
  void rotateLeft(Node *old_root);

  // Flips the color of a node ('R' ↔ 'B').
  void flipColor(Node *node);

  // Root node of the Red-Black Tree.
  Node *tree_root;

  // Total number of nodes currently in the tree.
  int tree_size;

  // Mapping from student ID to a list of (subject, node*) entries.
  SidMap sid_map;

  // Mapping from subject name to a list of student nodes.
  SubjectMap subject_map;
};

Node::Node(const int &sid, const string &subject, const string &sname,
           const int &semester, const string &phone, const int &timestamp)
    : key(NodeKey(sid, subject)), sname(sname), semester(semester),
      phone(phone), timestamp(timestamp), parent_node(nullptr),
      left_child(nullptr), right_child(nullptr), color('R') {}

RedBlackTree::RedBlackTree()
    : tree_root(nullptr), tree_size(0), sid_map({}), subject_map({}) {}

RedBlackTree::~RedBlackTree() { deleteSubtree(tree_root); }

// Recursively deletes all nodes in the subtree rooted at 'node' using
// post-order traversal.
void RedBlackTree::deleteSubtree(Node *node) {
  if (!node)
    return;

  deleteSubtree(node->left_child);
  deleteSubtree(node->right_child);
  delete node;
}

constexpr bool RedBlackTree::kIsDuplicateNode;
constexpr bool RedBlackTree::kIsNewlyInserted;
constexpr const char *RedBlackTree::kUnexpectedErrorMessage;
constexpr const char *RedBlackTree::kNoRecordsFoundMessage;
constexpr int RedBlackTree::kCompareLess;
constexpr int RedBlackTree::kCompareEqual;
constexpr int RedBlackTree::kCompareGreater;

// Query Type: “I sid subject sname semester phone timestamp”
void RedBlackTree::inquireInsert(const int &sid, const string &subject,
                                 const string &sname, const int &semester,
                                 const string &phone, const int &timestamp) {

  // Create a new node.
  Node *new_node = new Node(sid, subject, sname, semester, phone, timestamp);

  // If the tree is empty,
  if (isEmpty()) {
    handleEmptyInsert(sid, subject, new_node);
    return;
  }

  // Search for a parent or yourself.
  SearchResult searched_result = searchParentOrSelf(tree_root, new_node->key);
  Node *parent_or_self = searched_result.first;
  char parent_direction = searched_result.second;

  // If the following conditions are met, the algorithm is wrong.
  if (parent_or_self == nullptr) {
    cout << kUnexpectedErrorMessage << "\n";
    return;
  }

  // If that key already exists in the tree, only timestamp is updated.
  if (isDuplicateKey(parent_or_self->key, new_node->key)) {
    handleDuplicateNode(parent_or_self, timestamp);
    return;
  }

  // Insert a new node.
  handleNewInsert(sid, subject, parent_or_self, parent_direction, new_node);
}

// Query Type: “L sid”
void RedBlackTree::inquireAllSubjects(const int &sid) {
  // Retrieve all subjects a student has applied for.
  if (sid_map.find(sid) != sid_map.end()) {
    // Save the entire application for a particular student.
    vector<SubjectNodePair> &sid_vector = sid_map[sid];

    // Sort in dictionary order.
    sort(sid_vector.begin(), sid_vector.end(), subjectNameLess);

    // Repeatedly print out the node's subject and the node's color.
    for (const SubjectNodePair &ele : sid_vector) {
      cout << ele.first << " " << ele.second->color << " ";
    }
    cout << "\n";

    return;
  }

  cout << kNoRecordsFoundMessage << "\n";
}

// Query Type: "C subject”
void RedBlackTree::inquireStudentNumberOfSubject(const string &subject) {
  // Look up the number of students who applied for a particular subject.
  if (subject_map.find(subject) != subject_map.end()) {
    // Save the number of students who applied for the given subject.
    const vector<Node *> &subject_vector = subject_map[subject];

    // Save the size of the number of students who applied for a particular
    // subject.
    const int student_number_of_subject = subject_vector.size();

    // Add depth as it traverses the node.
    int depth_sum = 0;
    for (Node *ele : subject_vector) {
      depth_sum += getNodeDepth(ele);
    }

    // Output the sum of the number of students who applied for the subject and
    // the node depth that contains the information they applied for the
    // subject.
    cout << student_number_of_subject << " " << depth_sum << "\n";
    return;
  }

  // This should not happen if the algorithm and input are correct.
  cout << kUnexpectedErrorMessage << "\n";
}

// Query Type: ”M subject K”
void RedBlackTree::inquireEarlyStudent(const string &subject, const int &k) {
  // Retrieve up to K students who applied earliest for the subject.
  if (subject_map.find(subject) != subject_map.end()) {
    // Save the K number of students who applied for a particular subject first.
    vector<Node *> &subject_vector = subject_map[subject];

    // Sort the student nodes by earliest timestamp (ascending).
    sort(subject_vector.begin(), subject_vector.end(), timestampLess);

    // Determine how many students to print (up to K).
    const int subject_vector_size = subject_vector.size();
    int range_max = (subject_vector_size < k) ? subject_vector_size : k;

    // Among the application records in which 'subject' matches, 'timestamp' is
    // the fastest, and 'K' nodes are separated by spaces and outputted.
    for (int i = 0; i < range_max; i++) {
      Node *subject_node = subject_vector[i];

      cout << subject_node->key.first << " " << subject_node->color << " ";
    }
    cout << "\n";
    return;
  }

  // This should not happen if the algorithm and input are correct.
  cout << kUnexpectedErrorMessage << "\n";
}

// Comparator: returns true if the subject name of 'a' is lexicographically less
// than 'b'.
bool RedBlackTree::subjectNameLess(const SubjectNodePair &a,
                                   const SubjectNodePair &b) {
  return a.first < b.first;
}

// Comparator: returns true if 'a' has an earlier timestamp than 'b'.
bool RedBlackTree::timestampLess(Node *&a, Node *&b) {
  return a->timestamp < b->timestamp;
}

// Checks if the tree is empty.
bool RedBlackTree::isEmpty() const { return (tree_size == 0); }

// Checks whether two keys (sid, subject) are the same.
bool RedBlackTree::isDuplicateKey(const NodeKey &a, const NodeKey &b) {
  return a == b;
}

// Checks if a node is black or null (used in balancing).
bool RedBlackTree::isBlack(Node *sibling_node) {
  if (sibling_node == nullptr || sibling_node->color == 'B') {
    return true;
  }
  return false;
}

// Checks whether the current node and its parent are both red.
bool RedBlackTree::isDoubleRed(Node *cur_node) {
  if (cur_node->color == 'B') {
    return false;
  }
  if (cur_node->parent_node == nullptr) {
    return false;
  }
  return (cur_node->parent_node->color == 'R');
}

// Returns the sibling of the current node.
Node *RedBlackTree::getSibling(Node *cur_node) {
  Node *par_node = cur_node->parent_node;
  if (par_node->left_child == cur_node) {
    return par_node->right_child;
  }
  return par_node->left_child;
}

// Returns the depth (level) of a node from the root.
int RedBlackTree::getNodeDepth(Node *cur_node) {
  int depth = 0;
  while (cur_node->parent_node != nullptr) {
    cur_node = cur_node->parent_node;
    depth++;
  }
  return depth;
}

// Search for a parent or yourself.
SearchResult RedBlackTree::searchParentOrSelf(Node *cur_node,
                                              const NodeKey &key) {
  // If the conditions below are satisfied, it is an error in entering the
  // problem.
  if (cur_node == nullptr) {
    return SearchResult(nullptr, 'E');
  }

  if (comparator(cur_node->key, key) == kCompareGreater) {
    if (cur_node->left_child != nullptr) {
      // Go to the left node.
      return searchParentOrSelf(cur_node->left_child, key);
    }
    // Founded cur_node's parent!
    return SearchResult(cur_node, 'L');
  }
  if (comparator(cur_node->key, key) == kCompareLess) {
    if (cur_node->right_child != nullptr) {
      // Go to the right node.
      return searchParentOrSelf(cur_node->right_child, key);
    }
    // Founded cur_node's parent!
    return SearchResult(cur_node, 'R');
  }
  // If it's already exist, return self node.
  return SearchResult(cur_node, 'A');
}

// Compares two NodeKeys (sid, subject) and returns compare constant.
int RedBlackTree::comparator(const NodeKey &comp1, const NodeKey &comp2) {
  if (comp1.first < comp2.first) {
    return kCompareLess;
  }
  if (comp1.first > comp2.first) {
    return kCompareGreater;
  }
  // { comp1.first == comp2.first }
  if (comp1.second < comp2.second) {
    return kCompareLess;
  }
  if (comp1.second > comp2.second) {
    return kCompareGreater;
  }
  return kCompareEqual;
}

// Prints the depth of the node and whether it was a duplicate.
void RedBlackTree::printNodeStatus(Node *node, const bool &status) {
  int depth = getNodeDepth(node);
  cout << depth << " " << status << "\n";
}

// Handles insertion when the tree is empty (sets new node as root).
void RedBlackTree::handleEmptyInsert(const int &sid, const string &subject,
                                     Node *new_node) {
  new_node->color = 'B';
  tree_root = new_node;
  tree_size++;

  insertToMaps(sid, subject, new_node);

  printNodeStatus(tree_root, kIsNewlyInserted);
}

// Handles insertion when the node is new (not duplicate).
void RedBlackTree::handleNewInsert(const int &sid, const string &subject,
                                   Node *parent, char direction, Node *child) {
  // Update the parent-child relationship.
  child->parent_node = parent;
  if (direction == 'L')
    parent->left_child = child;
  if (direction == 'R')
    parent->right_child = child;
  tree_size++;

  insertToMaps(sid, subject, child);

  // Check the balance of the nodes
  Node *cur_node = child;
  adjustRebalance(cur_node);

  printNodeStatus(child, kIsNewlyInserted);
}

// Handles case where the node already exists (updates timestamp).
void RedBlackTree::handleDuplicateNode(Node *existing_node,
                                       const int &new_timestamp) {
  existing_node->timestamp = new_timestamp;
  printNodeStatus(existing_node, kIsDuplicateNode);
}

// Inserts a node into both sid_map and subject_map.
void RedBlackTree::insertToMaps(const int &sid, const string &subject,
                                Node *new_node) {
  insertStudentToSidMap(sid, subject, new_node);
  insertStudentToSubjectMap(subject, new_node);
}

// Adds subject info to sid_map for a given student ID.
void RedBlackTree::insertStudentToSidMap(const int &sid, const string &subject,
                                         Node *new_node) {
  SubjectNodePair new_node_pair(subject, new_node);

  // If the existing sid_map does not exist,
  if (sid_map.find(sid) != sid_map.end()) {
    sid_map[sid].push_back(new_node_pair);
    return;
  }

  vector<SubjectNodePair> new_node_vector;
  new_node_vector.push_back(new_node_pair);
  sid_map.insert({sid, new_node_vector});
}

// Adds student node to subject_map for the given subject.
void RedBlackTree::insertStudentToSubjectMap(const string &subject,
                                             Node *new_node) {
  // If the existing subject_map does not exist,
  if (subject_map.find(subject) == subject_map.end()) {
    vector<Node *> new_vector;
    new_vector.push_back(new_node);
    subject_map.insert({subject, new_vector});
    return;
  }

  // Check that the node exists in subject_vector.
  vector<Node *> &subject_vector = subject_map[subject];
  if (find(subject_vector.begin(), subject_vector.end(), new_node) ==
      subject_vector.end()) {
    subject_map[subject].push_back(new_node);
  }
}

// Performs restructuring when double red occurs.
void RedBlackTree::adjustRestructure(Node *cur_node) {
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

// Recolors grandparent-parent-sibling nodes and returns new current node.
Node *RedBlackTree::adjustRecolor(Node *cur_node) {
  Node *par_node = cur_node->parent_node;
  Node *grand_par_node = par_node->parent_node;

  flipColor(grand_par_node);
  flipColor(par_node);
  flipColor(getSibling(par_node));

  if (grand_par_node == tree_root && grand_par_node->color == 'R') {
    grand_par_node->color = 'B';
  }
  return grand_par_node;
}

// Repeat until double red does not occur.
void RedBlackTree::adjustRebalance(Node *cur_node) {
  while (isDoubleRed(cur_node)) {
    if (isBlack(getSibling(cur_node->parent_node))) {
      adjustRestructure(cur_node);
      break;
    } else {
      cur_node = adjustRecolor(cur_node);
    }
  }
}

// Performs right rotation at the given node.
void RedBlackTree::rotateRight(Node *old_root) {
  // Define new_root and middle_subtree.
  Node *new_root = old_root->left_child;
  Node *middle_subtree = new_root->right_child;

  // Update the child relationship between new_root and old_root.
  new_root->right_child = old_root;
  old_root->left_child = middle_subtree;

  // If middle_subtree exists, update the parent relationship.
  if (middle_subtree) {
    middle_subtree->parent_node = old_root;
  }

  // Update the parent relationship between new_root and old_root.
  new_root->parent_node = old_root->parent_node;
  old_root->parent_node = new_root;

  // If new_root's parents exist, update the parent-child relationship
  if (new_root->parent_node) {
    if (comparator(new_root->parent_node->key, new_root->key) == kCompareLess) {
      new_root->parent_node->right_child = new_root;
    }
    if (comparator(new_root->parent_node->key, new_root->key) ==
        kCompareGreater) {
      new_root->parent_node->left_child = new_root;
    }
  }

  // If new_root is the root of the tree,
  if (new_root->parent_node == nullptr) {
    tree_root = new_root;
  }
}

// Performs left rotation at the given node.
void RedBlackTree::rotateLeft(Node *old_root) {
  // Define new_root and middle_subtree.
  Node *new_root = old_root->right_child;
  Node *middle_subtree = new_root->left_child;

  // Update the child relationship between new_root and old_root.
  new_root->left_child = old_root;
  old_root->right_child = middle_subtree;

  // If middle_subtree exists, update the parent relationship.
  if (middle_subtree) {
    middle_subtree->parent_node = old_root;
  }

  // Update the parent relationship between new_root and old_root.
  new_root->parent_node = old_root->parent_node;
  old_root->parent_node = new_root;

  // If new_root's parents exist, update the parent-child relationship
  if (new_root->parent_node) {
    if (comparator(new_root->parent_node->key, new_root->key) == kCompareLess) {
      new_root->parent_node->right_child = new_root;
    }
    if (comparator(new_root->parent_node->key, new_root->key) ==
        kCompareGreater) {
      new_root->parent_node->left_child = new_root;
    }
  }

  // If new_root is the root of the tree,
  if (new_root->parent_node == nullptr) {
    tree_root = new_root;
  }
}

// Flips the color of a node ('R' ↔ 'B').
void RedBlackTree::flipColor(Node *node) {
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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // Enter test cases.
  int test_case;
  cin >> test_case;

  // Define red_black_tree instance.
  RedBlackTree *red_black_tree = new RedBlackTree();

  while (test_case--) {
    // Enter query type.
    // There are four types of query type: 'I', 'L', 'C', and 'M'.
    char query_type;
    cin >> query_type;

    if (query_type == static_cast<char>(QueryType::kInsert)) {
      int sid, semester, timestamp;
      string subject, sname, phone;

      cin >> sid >> subject >> sname >> semester >> phone >> timestamp;

      red_black_tree->inquireInsert(sid, subject, sname, semester, phone,
                                    timestamp);

      continue;
    }

    if (query_type == static_cast<char>(QueryType::kListSubjects)) {
      int sid;

      cin >> sid;

      red_black_tree->inquireAllSubjects(sid);
      continue;
    }

    if (query_type == static_cast<char>(QueryType::kCountStudents)) {
      string subject;

      cin >> subject;

      red_black_tree->inquireStudentNumberOfSubject(subject);
      continue;
    }

    if (query_type == static_cast<char>(QueryType::kEarliestApplicants)) {
      string subject;
      int k;

      cin >> subject >> k;

      red_black_tree->inquireEarlyStudent(subject, k);
      continue;
    }
  }

  delete red_black_tree;

  return 0;
}