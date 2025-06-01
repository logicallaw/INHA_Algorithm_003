/*
 * This is file of the project 2025_Lecture_Algorithm
 * Licensed under the MIT License.
 * Copyright (c) 2025 Junho Kim
 * For full license text, see the LICENSE file in the root directory or at
 * https://opensource.org/license/mit
 * Author: Junho Kim
 * Latest Updated Date: 2025-06-01
 *
 * Description: Builds a Minimum Spanning Tree using Prim's algorithm and
 * outputs selected bridges. (Note: The problem refers to these as 'roads'.)
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

// Map city names to their elevation values
typedef map<string, int> CityElevationMap;

// Store the list of bridges connected to each city (adjacency list)
typedef unordered_map<string, vector<Bridge *>> BridgeGraph;

// Map city names to their corresponding Node objects
typedef map<string, Node *> CityNodeMap;

// Store a collection of Bridge pointers used as a heap or list
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
  // Track the current status of the vertex: 'U' (Unseen), 'F' (Fringe), or 'T'
  // (Tree)
  char status;

  // Store the name of the city represented by this node
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

// Define a comparator struct that determines the maintenance priority of
// bridges (roads)
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
  MST() : starting_node(nullptr), total_length(0) {}

  // Select the starting city for Prim's algorithm
  void setStartingNode(const string &starting_city) {
    starting_node = city_node_map[starting_city];
    // Update the vertex status to Tree
    starting_node->status = 'T';

    // Insert the bridges adjacent to the starting vertex into the priority
    // queue
    for (Bridge *bridge : graph[starting_city]) {
      bridge_heap.push_back(bridge);
      push_heap(bridge_heap.begin(), bridge_heap.end(), BridgeComparator{});
    }
  }

  void initializeMST() {
    // Repeat until no fringe vertices remain
    while (!bridge_heap.empty()) {
      // Get the highest-priority bridge currently at the front of the priority
      // queue
      Bridge *next_bridge = bridge_heap.front();
      pop_heap(bridge_heap.begin(), bridge_heap.end(), BridgeComparator{});
      bridge_heap.pop_back();

      Node *first_node = city_node_map[next_bridge->earlier_city];
      Node *second_node = city_node_map[next_bridge->later_city];

      // Skip the bridge if both connected cities are already in the MST
      if (first_node->status == 'T' && second_node->status == 'T') {
        continue;
      }

      // Select the new vertex to add to the Tree
      Node *new_node = (first_node->status == 'T') ? second_node : first_node;
      new_node->status = 'T';

      // Print intermediate information as required by the problem specification
      cout << min(first_node->city, second_node->city) << " "
           << max(first_node->city, second_node->city) << endl;

      // For each bridge connected to the new Tree vertex, add it to the
      // priority queue if the other endpoint is not yet in the Tree
      for (Bridge *connected_bridge : graph[new_node->city]) {
        Node *other =
            (city_node_map[connected_bridge->earlier_city] == new_node)
                ? city_node_map[connected_bridge->later_city]
                : city_node_map[connected_bridge->earlier_city];
        if (other->status == 'U' || other->status == 'F') {
          bridge_heap.push_back(connected_bridge);
          push_heap(bridge_heap.begin(), bridge_heap.end(), BridgeComparator{});
        }
      }
      // Add the selected bridge to the MST and update the total maintenance
      // length
      mst_bridges.push_back(next_bridge);
      total_length += next_bridge->road_length;
    }
  }

  // Print the total length of bridges to be maintained
  void printTotalElevationSum() const { cout << total_length << "\n"; }

  // Print information of all bridges to be maintained, with each field
  // separated by spaces
  void printAllBridges() {
    // Sort the cities in lexicographic order
    sort(mst_bridges.begin(), mst_bridges.end(), bridgeCityOrder);

    for (Bridge *b : mst_bridges) {
      cout << b->timestamp << " " << b->earlier_city << " " << b->later_city
           << " " << b->road_length << endl;
    }
  }

  // Sort the cities in lexicographic order
  static bool bridgeCityOrder(Bridge *a, Bridge *b) {
    if (a->earlier_city != b->earlier_city)
      return a->earlier_city < b->earlier_city;
    return a->later_city < b->later_city;
  }

private:
  // Store the starting vertex for Prim's algorithm
  Node *starting_node;

  // Store the list of bridges included in the Minimum Spanning Tree
  BridgeHeap mst_bridges;

  // Store the total length of all bridges selected for maintenance
  int total_length;
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