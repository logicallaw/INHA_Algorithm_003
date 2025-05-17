/*
 * This is file of the project 2025_Lecture_Algorithm
 * Licensed under the MIT License.
 * Copyright (c) 2025 Junho Kim
 * For full license text, see the LICENSE file in the root directory or at
 * https://opensource.org/license/mit
 * Author: Junho Kim
 * Latest Updated Date: 2025-05-17
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
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
  Node(const int &sid, const string &subject, const string &sname,
       const int &semester, const string &phone, const int &timestamp);

private:
  NodeKey key;
  string sname;
  int semester;
  string phone;
  int timestamp;

  Node *parent_node;
  Node *left_child;
  Node *right_child;

  char color;

  friend class RedBlackTree;
};

class RedBlackTree {
public:
  RedBlackTree();

  void inquireInsert(const int &sid, const string &subject, const string &sname,
                     const int &semester, const string &phone,
                     const int &timestamp);
  void inquireAllSubjects(const int &sid);
  void inquireStudentNumberOfSubject(const string &subject);
  void inquireEarlyStudent(const string &subject, const int &k);

private:
  static bool subjectNameLess(const SubjectNodePair &a,
                              const SubjectNodePair &b);
  static bool timestampLess(Node *&a, Node *&b);
  static constexpr bool kIsDuplicateNode = true;
  static constexpr bool kIsNewlyInserted = false;
  static constexpr const char *kUnexpectedErrorMessage =
      "Algorithm error! You must solve this problem.";
  static constexpr const char *kNoRecordsFoundMessage = "No records found";
  static constexpr int kCompareLess = -1;
  static constexpr int kCompareEqual = 0;
  static constexpr int kCompareGreater = 1;

  bool isEmpty() const;
  bool isDuplicateKey(const NodeKey &a, const NodeKey &b);
  bool isBlack(Node *sibling_node);
  bool isDoubleRed(Node *cur_node);

  Node *getSibling(Node *cur_node);
  int getNodeDepth(Node *cur_node);

  SearchResult searchParentOrSelf(Node *cur_node, const NodeKey &key);
  int comparator(const NodeKey &comp1, const NodeKey &comp2);
  void printNodeStatus(Node *node, const bool &status);

  void handleEmptyInsert(const int &sid, const string &subject, Node *new_node);
  void handleNewInsert(const int &sid, const string &subject, Node *parent,
                       char direction, Node *child);
  void handleDuplicateNode(Node *existing_node, const int &new_timestamp);

  void insertToMaps(const int &sid, const string &subject, Node *new_node);
  void insertStudentToSidMap(const int &sid, const string &subject,
                             Node *new_node);
  void insertStudentToSubjectMap(const string &subject, Node *new_node);

  void adjustRestructure(Node *cur_node);
  Node *adjustRecolor(Node *cur_node);
  void adjustRebalance(Node *cur_node);

  void rotateRight(Node *old_root);
  void rotateLeft(Node *old_root);
  void filpColor(Node *node);

  Node *tree_root;
  int tree_size;
  SidMap sid_map;
  SubjectMap subject_map;
};

Node::Node(const int &sid, const string &subject, const string &sname,
           const int &semester, const string &phone, const int &timestamp)
    : key(NodeKey(sid, subject)), sname(sname), semester(semester),
      phone(phone), timestamp(timestamp), parent_node(nullptr),
      left_child(nullptr), right_child(nullptr), color('R') {}

RedBlackTree::RedBlackTree()
    : tree_root(nullptr), tree_size(0), sid_map({}), subject_map({}) {}

constexpr bool RedBlackTree::kIsDuplicateNode;
constexpr bool RedBlackTree::kIsNewlyInserted;
constexpr const char *RedBlackTree::kUnexpectedErrorMessage;
constexpr const char *RedBlackTree::kNoRecordsFoundMessage;
constexpr int RedBlackTree::kCompareLess;
constexpr int RedBlackTree::kCompareEqual;
constexpr int RedBlackTree::kCompareGreater;

void RedBlackTree::inquireInsert(const int &sid, const string &subject,
                                 const string &sname, const int &semester,
                                 const string &phone, const int &timestamp) {

  Node *new_node = new Node(sid, subject, sname, semester, phone, timestamp);

  if (isEmpty()) {
    handleEmptyInsert(sid, subject, new_node);
    return;
  }

  SearchResult searched_result = searchParentOrSelf(tree_root, new_node->key);
  Node *parent_or_self = searched_result.first;
  char parent_direction = searched_result.second;

  if (parent_or_self == nullptr) {
    cout << kUnexpectedErrorMessage << "\n";
    return;
  }

  if (isDuplicateKey(parent_or_self->key, new_node->key)) {
    handleDuplicateNode(parent_or_self, timestamp);
    return;
  }

  handleNewInsert(sid, subject, parent_or_self, parent_direction, new_node);
}

void RedBlackTree::inquireAllSubjects(const int &sid) {
  // If existed
  if (sid_map.find(sid) != sid_map.end()) {
    vector<SubjectNodePair> &sid_vector = sid_map[sid];

    // sorted by subject name
    sort(sid_vector.begin(), sid_vector.end(), subjectNameLess);

    for (const SubjectNodePair &ele : sid_vector) {
      cout << ele.first << " " << ele.second->color << " ";
    }
    cout << "\n";

    return;
  }
  cout << kNoRecordsFoundMessage << "\n";
}

void RedBlackTree::inquireStudentNumberOfSubject(const string &subject) {
  if (subject_map.find(subject) != subject_map.end()) {
    const vector<Node *> &subject_vector = subject_map[subject];

    const int student_number_of_subject = subject_vector.size();

    int depth_sum = 0;
    for (Node *ele : subject_vector) {
      depth_sum += getNodeDepth(ele);
    }
    cout << student_number_of_subject << " " << depth_sum << "\n";
    return;
  }
  cout << kUnexpectedErrorMessage << "\n";
}

void RedBlackTree::inquireEarlyStudent(const string &subject, const int &k) {
  if (subject_map.find(subject) != subject_map.end()) {
    vector<Node *> &subject_vector = subject_map[subject];

    const int subject_vector_size = subject_vector.size();
    sort(subject_vector.begin(), subject_vector.end(), timestampLess);

    int range_max = (subject_vector_size < k) ? subject_vector_size : k;

    for (int i = 0; i < range_max; i++) {
      Node *subject_node = subject_vector[i];

      cout << subject_node->key.first << " " << subject_node->color << " ";
    }
    cout << "\n";
    return;
  }
  cout << kUnexpectedErrorMessage << "\n";
}

bool RedBlackTree::subjectNameLess(const SubjectNodePair &a,
                                   const SubjectNodePair &b) {
  return a.first < b.first;
}

bool RedBlackTree::timestampLess(Node *&a, Node *&b) {
  return a->timestamp < b->timestamp;
}

bool RedBlackTree::isEmpty() const { return (tree_size == 0); }

bool RedBlackTree::isDuplicateKey(const NodeKey &a, const NodeKey &b) {
  return a == b;
}

bool RedBlackTree::isBlack(Node *sibling_node) {
  if (sibling_node == nullptr || sibling_node->color == 'B') {
    return true;
  }
  return false;
}

bool RedBlackTree::isDoubleRed(Node *cur_node) {
  if (cur_node->color == 'B') {
    return false;
  }
  if (cur_node->parent_node == nullptr) {
    return false;
  }
  return (cur_node->parent_node->color == 'R');
}

Node *RedBlackTree::getSibling(Node *cur_node) {
  Node *par_node = cur_node->parent_node;
  if (par_node->left_child == cur_node) {
    return par_node->right_child;
  }
  return par_node->left_child;
}

int RedBlackTree::getNodeDepth(Node *cur_node) {
  int depth = 0;
  while (cur_node->parent_node != nullptr) {
    cur_node = cur_node->parent_node;
    depth++;
  }
  return depth;
}

SearchResult RedBlackTree::searchParentOrSelf(Node *cur_node,
                                              const NodeKey &key) {
  if (cur_node == nullptr) {
    return SearchResult(nullptr, 'E');
  }

  if (comparator(cur_node->key, key) == kCompareGreater) {
    if (cur_node->left_child != nullptr) {
      return searchParentOrSelf(cur_node->left_child, key);
    }
    return SearchResult(cur_node, 'L');
  }
  if (comparator(cur_node->key, key) == kCompareLess) {
    if (cur_node->right_child != nullptr) {
      return searchParentOrSelf(cur_node->right_child, key);
    }
    return SearchResult(cur_node, 'R');
  }
  // { If it's already exist, return self node. }
  return SearchResult(cur_node, 'A');
}

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

void RedBlackTree::printNodeStatus(Node *node, const bool &status) {
  int depth = getNodeDepth(node);
  cout << depth << " " << status << "\n";
}

void RedBlackTree::handleEmptyInsert(const int &sid, const string &subject,
                                     Node *new_node) {
  insertToMaps(sid, subject, new_node);

  new_node->color = 'B';
  tree_root = new_node;
  tree_size++;
  printNodeStatus(tree_root, kIsNewlyInserted);
}

void RedBlackTree::handleNewInsert(const int &sid, const string &subject,
                                   Node *parent, char direction, Node *child) {
  child->parent_node = parent;
  if (direction == 'L')
    parent->left_child = child;
  if (direction == 'R')
    parent->right_child = child;
  tree_size++;
  insertToMaps(sid, subject, child);

  Node *cur_node = child;
  adjustRebalance(cur_node);
  printNodeStatus(child, kIsNewlyInserted);
}

void RedBlackTree::handleDuplicateNode(Node *existing_node,
                                       const int &new_timestamp) {
  existing_node->timestamp = new_timestamp;
  printNodeStatus(existing_node, kIsDuplicateNode);
}

void RedBlackTree::insertToMaps(const int &sid, const string &subject,
                                Node *new_node) {
  insertStudentToSidMap(sid, subject, new_node);
  insertStudentToSubjectMap(subject, new_node);
}

void RedBlackTree::insertStudentToSidMap(const int &sid, const string &subject,
                                         Node *new_node) {
  SubjectNodePair new_node_pair(subject, new_node);

  if (sid_map.find(sid) != sid_map.end()) {
    sid_map[sid].push_back(new_node_pair);
    return;
  }
  vector<SubjectNodePair> new_node_vector;
  new_node_vector.push_back(new_node_pair);
  sid_map.insert({sid, new_node_vector});
}

void RedBlackTree::insertStudentToSubjectMap(const string &subject,
                                             Node *new_node) {
  if (subject_map.find(subject) == subject_map.end()) {
    vector<Node *> new_vector;

    new_vector.push_back(new_node);

    subject_map.insert({subject, new_vector});
    return;
  }
  vector<Node *> &subject_vector = subject_map[subject];
  if (find(subject_vector.begin(), subject_vector.end(), new_node) ==
      subject_vector.end()) {
    subject_map[subject].push_back(new_node);
  }
}

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

Node *RedBlackTree::adjustRecolor(Node *cur_node) {
  Node *par_node = cur_node->parent_node;
  Node *grand_par_node = par_node->parent_node;

  filpColor(grand_par_node);
  filpColor(par_node);
  filpColor(getSibling(par_node));

  if (grand_par_node == tree_root && grand_par_node->color == 'R') {
    grand_par_node->color = 'B';
  }
  return grand_par_node;
}

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

void RedBlackTree::rotateRight(Node *old_root) {
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
    if (comparator(new_root->parent_node->key, new_root->key) == kCompareLess) {
      new_root->parent_node->right_child = new_root;
    }
    if (comparator(new_root->parent_node->key, new_root->key) ==
        kCompareGreater) {
      new_root->parent_node->left_child = new_root;
    }
  }

  if (new_root->parent_node == nullptr) {
    tree_root = new_root;
  }
}

void RedBlackTree::rotateLeft(Node *old_root) {
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
    if (comparator(new_root->parent_node->key, new_root->key) == kCompareLess) {
      new_root->parent_node->right_child = new_root;
    }
    if (comparator(new_root->parent_node->key, new_root->key) ==
        kCompareGreater) {
      new_root->parent_node->left_child = new_root;
    }
  }

  if (new_root->parent_node == nullptr) {
    tree_root = new_root;
  }
}

void RedBlackTree::filpColor(Node *node) {
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

  int test_case;
  cin >> test_case;

  RedBlackTree *red_black_tree = new RedBlackTree();

  while (test_case--) {
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

  return 0;
}