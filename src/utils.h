#ifndef UTILS_H
#define UTILS_H
#include "main.h"
#include <string>
#include <unordered_map>

// returns the index of the blank square in the state array
int getBlankIndex(int arr[]);

int totalManhattan(const int arr[]);

int totalH3_dist(const int arr[]);

// Expand node by adding available moves from that state to
// given frontier list
// return the count of new nodes added to frontier list
int expand_node(std::unordered_map<std::string, bool> &map, std::vector<Node *> &frontier, Node *node);

// expand function for ILS
int expand_node_ils(std::unordered_map<std::string, bool> &map, std::vector<Node *> &frontier, Node *node, int limit);

// function to return Manhattan distance between two points
int Manhattan(int x1, int y1, int x2, int y2);

void printTable(const int arr[]);

// print the table statuses of all nodes in the frontier list
void printFrontierListTables(const std::vector<Node *> frontier);

// same as the func. above, but prints array instead
void printFrontierList(const std::vector<Node *> frontier);

void printFrontierListCosts(const std::vector<Node *> frontier);

// converts state array to string equivalent
std::string convertStateString(const int state[]);

// bool isExpanded(const std::unordered_map<std::string, bool> &map, int state[]);

// Adds the given state into visited list to not to visit it again
void addExpanded(std::unordered_map<std::string, bool> &map, int state[]);

// debugging purposes, prints the visited list
void printExpandedList(std::unordered_map<std::string, bool> &expandedList);

// print all informations of a node
// to be used for debugging purposed
void debugNode(const Node &node);

void printPath(std::vector<int> path);

#endif