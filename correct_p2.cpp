/*
 * This is file of the project 2025_Lecture_Algorithm
 * Licensed under the MIT License.
 * Copyright (c) 2025 Junho Kim
 * For full license text, see the LICENSE file in the root directory or at
 * https://opensource.org/license/mit
 * Author: Junho Kim
 * Latest Updated Date: 2025-06-01
 *
 * NOTE: This file is under active maintenance as of May 18, 2025.
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Node;
class Bridge;
class MST;

typedef map<string, int> CityElevationMap;
typedef unordered_map<string, vector<Bridge *>> BridgeGraph;
typedef map<string, Node *> CityNodeMap;
typedef vector<Bridge *> BridgeHeap;

CityElevationMap city_elevation_map;
BridgeGraph graph;
CityNodeMap city_node_map;
BridgeHeap bridge_heap;

// Message: Should never happen if logic is correct (guard message).
static constexpr const char *kUnexpectedErrorMessage =
    "Algorithm error! You must solve this problem.";

// Define a class that manages the city name and the status of the vertex
class Node {
public:
  Node(const string &city) : city(city), status('U') {}

private:
  char status;
  string city;
  friend class MST;
};

// Define a class that manages a bridge connecting two cities
class Bridge {
public:
  Bridge(const string &first_city, const string &second_city,
         const int &road_length, const string &timestamp)
      : road_length(road_length), timestamp(timestamp) {

    // Initialize the lexicographically earlier and later city names
    initializeCities(first_city, second_city);
    // Calculate the elevation difference between the two cities
    initializeHeightDifference();
  }

  // Initialize the lexicographically earlier and later city names
  void initializeCities(const string &first_city, const string &second_city) {
    return (first_city <= second_city) ? storeCities(first_city, second_city)
                                       : storeCities(second_city, first_city);
  }

  // Calculate the elevation difference between the two cities
  void initializeHeightDifference() {
    if (city_elevation_map.find(earlier_city) == city_elevation_map.end() ||
        city_elevation_map.find(later_city) == city_elevation_map.end()) {
      cout << kUnexpectedErrorMessage << "\n";
      return;
    }

    // Get elevation of the earlier city in lexicographic order
    int earlier_city_height = city_elevation_map[earlier_city];
    // Get elevation of the later city in lexicographic order
    int later_city_height = city_elevation_map[later_city];

    // Calculate the difference in elevation between the two cities
    this->road_length_diff = abs(earlier_city_height - later_city_height);
  }

  // Store the earlier and later city names based on lexicographic order
  void storeCities(const string &earlier_city, const string &later_city) {
    this->earlier_city = earlier_city;
    this->later_city = later_city;
  }

private:
  // Store the lexicographically earlier city name
  string earlier_city;

  // Store the lexicographically later city name
  string later_city;

  // Store the construction timestamp of the bridge (format: YYYY-MM)
  string timestamp;

  // Store the length of the bridge (in meters)
  int road_length;

  // Store the absolute elevation difference between the two connected cities
  int road_length_diff;

  friend struct BridgeComparator;
  friend class MST;
};

struct BridgeComparator {
  bool operator()(Bridge *a, Bridge *b) const {
    if (a->timestamp != b->timestamp)
      return a->timestamp > b->timestamp;
    if (a->road_length != b->road_length)
      return a->road_length > b->road_length;
    if (a->road_length_diff != b->road_length_diff)
      return a->road_length_diff > b->road_length_diff;
    if (a->earlier_city != b->earlier_city)
      return a->earlier_city > b->earlier_city;
    if (a->later_city != b->later_city)
      return a->later_city > b->later_city;

    cout << kUnexpectedErrorMessage << "\n";
    return false;
  }
};

class MST {
public:
  MST() {}

  void setStartingNode(const string &starting_city) {
    starting_node = city_node_map[starting_city];
    starting_node->status = 'T';

    // 우선순위큐에 삽입. 삽입된 Bridge는 F임.
    for (Bridge *bridge : graph[starting_city]) {
      bridge_heap.push_back(bridge);
      push_heap(bridge_heap.begin(), bridge_heap.end(), BridgeComparator{});
    }
  }

  void initializeMST() {
    while (!bridge_heap.empty()) {
      // Tree Vertex 가져옴
      Bridge *b = bridge_heap.front();
      pop_heap(bridge_heap.begin(), bridge_heap.end(), BridgeComparator{});
      bridge_heap.pop_back();

      Node *u = city_node_map[b->earlier_city];
      Node *v = city_node_map[b->later_city];

      if (u->status == 'T' && v->status == 'T')
        continue;

      Node *new_node = (u->status == 'T') ? v : u;
      new_node->status = 'T';

      cout << min(u->city, v->city) << " " << max(u->city, v->city) << endl;

      for (Bridge *nb : graph[new_node->city]) {
        Node *other = (city_node_map[nb->earlier_city] == new_node)
                          ? city_node_map[nb->later_city]
                          : city_node_map[nb->earlier_city];
        if (other->status == 'U' || other->status == 'F') {
          bridge_heap.push_back(nb);
          push_heap(bridge_heap.begin(), bridge_heap.end(), BridgeComparator{});
        }
      }
      mst_bridges.push_back(b);
      total_length += b->road_length;
    }
  }

  void printTotalElevationSum() const { cout << total_length << "\n"; }

  void printAllBridges() {
    sort(mst_bridges.begin(), mst_bridges.end(), [](Bridge *a, Bridge *b) {
      if (a->earlier_city != b->earlier_city)
        return a->earlier_city < b->earlier_city;
      return a->later_city < b->later_city;
    });

    for (Bridge *b : mst_bridges) {
      cout << b->timestamp << " " << b->earlier_city << " " << b->later_city
           << " " << b->road_length << endl;
    }
  }

private:
  Node *starting_node;
  vector<Bridge *> mst_bridges;
  int total_length = 0;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // Input the total number of queries
  int query_count;
  cin >> query_count;

  // Input the list of cities with their information
  while (query_count--) {
    string city;
    int elevation;

    cin >> city >> elevation;

    // Insert each city's elevation into the elevation map
    city_elevation_map.insert({city, elevation});
  }

  // Input the total number of road entries
  cin >> query_count;

  // Input space-separated road data between cities
  while (query_count--) {
    string first_city, second_city, timestamp;
    int road_length;

    cin >> first_city >> second_city >> road_length >> timestamp;

    // Create node entries for the two cities if they haven't been added yet
    if (city_node_map.find(first_city) == city_node_map.end()) {
      Node *first_city_node = new Node(first_city);
      city_node_map.insert({first_city, first_city_node});
    }
    if (city_node_map.find(second_city) == city_node_map.end()) {
      Node *second_city_node = new Node(second_city);
      city_node_map.insert({second_city, second_city_node});
    }

    // Create a bridge connecting the two cities
    Bridge *new_bridge =
        new Bridge(first_city, second_city, road_length, timestamp);

    // Add the bridge to the adjacency list for both cities (undirected)
    graph[first_city].push_back(new_bridge);
    graph[second_city].push_back(new_bridge);
  }

  // Input the starting city for Prim's algorithm
  string query_starting_city;
  cin >> query_starting_city;

  MST *mst = new MST();

  // Set the starting city for Prim's algorithm
  mst->setStartingNode(query_starting_city);

  // Initialize MST
  mst->initializeMST();

  // Print the total length of the roads to be maintained
  mst->printTotalElevationSum();
  // Print information of all roads to be maintained, separating each field with
  // spaces
  mst->printAllBridges();

  return 0;
}