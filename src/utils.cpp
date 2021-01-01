#include "main.h"
#include <algorithm> // std::find
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>

int getBlankIndex(int arr[]) {
    return std::distance(arr, std::find(arr, arr + 16, 0));
}

int Manhattan(int x1, int y1, int x2, int y2) {
    return std::abs(x2 - x1) + abs(y2 - y1);
}

void printTable(const int arr[]) {
    printf("-----------------------------\n");
    printf("|  %2d  |  %2d  |  %2d  |  %2d  |\n", arr[0], arr[4], arr[8], arr[12]);
    printf("-----------------------------\n");
    printf("|  %2d  |  %2d  |  %2d  |  %2d  |\n", arr[1], arr[5], arr[9], arr[13]);
    printf("-----------------------------\n");
    printf("|  %2d  |  %2d  |  %2d  |  %2d  |\n", arr[2], arr[6], arr[10], arr[14]);
    printf("-----------------------------\n");
    printf("|  %2d  |  %2d  |  %2d  |  %2d  |\n", arr[3], arr[7], arr[11], arr[15]);
    printf("-----------------------------\n");
}

void printFrontierListTables(const std::vector<Node *> frontier) {
    std::cout << "Frontier list: [ \n";
    for (const auto node : frontier) {
        printTable(node->state);
    }
    std::cout << "]\n";
}

void printFrontierList(const std::vector<Node *> frontier) {
    std::cout << "Frontier list: [ \n";
    for (const auto node : frontier) {
        std::cout << "\t[ ";
        for (const auto x : node->state) {
            std::cout << x << ", ";
        }
        std::cout << "\b\b ],\n";
    }
    std::cout << "]\n";
}

std::string convertStateString(const int state[]) {
    char codes[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    // prepare the string equivalent of the array
    // converts all values to hex characters
    std::string str = "0000000000000000";
    for (int i = 0; i < 16; i++) {
        str[i] = codes[state[i]];
    }
    // std::cout << "_" << str << "_\n";
    return str;
}

bool isExpanded(std::unordered_map<std::string, bool> &map, int state[]) {
    std::string str = "0000000000000000";

    const auto it = map.find(convertStateString(state));
    // const auto it = map.find(str);

    if (it == map.end()) {
        return false; // not found
    }
    // std::cout << "=" << it->first << "=\n";
    return true; // found: already expanded before
}

void addExpanded(std::unordered_map<std::string, bool> &map, int state[]) {
    // convert state array to equivalent string and add to expanded list
    map.insert(std::pair<std::string, bool>(convertStateString(state), true));
}

void addIfNotExpanded(std::unordered_map<std::string, bool> &map, std::vector<Node *> &frontier, Node *node) {

    if (isExpanded(map, node->state)) {
        // already expanded
        delete node;
    } else {
        // add new node to frontier list
        frontier.push_back(node);
        // add to expanded list
        addExpanded(map, node->state);
    }
}

void expand_node(std::unordered_map<std::string, bool> &map, std::vector<Node *> &frontier, Node *node) {
    int index = getBlankIndex(node->state);

    /* up */
    if (!(index == 0 || index == 4 || index == 8 || index == 12)) {
        // clone the node and swap blank tile
        Node *newNode = new Node(node->state, node, Direction::UP, node->depth + 1, node->cost + 1);

        // slide blank tile
        newNode->state[index] = newNode->state[index - 1];
        newNode->state[index - 1] = 0;

        addIfNotExpanded(map, frontier, newNode);
    }

    /* down */
    if (!(index == 3 || index == 7 || index == 11 || index == 15)) {
        // clone the node and swap blank tile
        Node *newNode = new Node(node->state, node, Direction::DOWN, node->depth + 1, node->cost + 1);

        // slide blank tile
        newNode->state[index] = newNode->state[index + 1];
        newNode->state[index + 1] = 0;

        // add new node to frontier list
        addIfNotExpanded(map, frontier, newNode);
    }

    /* left */
    if (!(index == 0 || index == 1 || index == 2 || index == 3)) {
        // clone the node and swap blank tile
        Node *newNode = new Node(node->state, node, Direction::LEFT, node->depth + 1, node->cost + 1);

        // slide blank tile
        newNode->state[index] = newNode->state[index - 4];
        newNode->state[index - 4] = 0;

        // add new node to frontier list
        addIfNotExpanded(map, frontier, newNode);
    }

    /* right */
    if (!(index == 12 || index == 13 || index == 14 || index == 15)) {
        // clone the node and swap blank tile
        Node *newNode = new Node(node->state, node, Direction::RIGHT, node->depth + 1, node->cost + 1);

        // slide blank tile
        newNode->state[index] = newNode->state[index + 4];
        newNode->state[index + 4] = 0;

        // add new node to frontier list
        addIfNotExpanded(map, frontier, newNode);
    }

    /* top left */
    if (!(index == 0 || index == 1 || index == 2 || index == 3 || index == 4 || index == 8 || index == 12)) {
        // clone the node and swap blank tile
        Node *newNode = new Node(node->state, node, Direction::UP_LEFT, node->depth + 1, node->cost + 3);

        // slide blank tile
        newNode->state[index] = newNode->state[index - 5];
        newNode->state[index - 5] = 0;

        // add new node to frontier list
        addIfNotExpanded(map, frontier, newNode);
    }

    /* top right */
    if (!(index == 0 || index == 4 || index == 8 || index == 12 || index == 13 || index == 14 || index == 15)) {
        // clone the node and swap blank tile
        Node *newNode = new Node(node->state, node, Direction::UP_RIGHT, node->depth + 1, node->cost + 3);

        // slide blank tile
        newNode->state[index] = newNode->state[index + 3];
        newNode->state[index + 3] = 0;

        // add new node to frontier list
        addIfNotExpanded(map, frontier, newNode);
    }

    /* bottom left */
    if (!(index == 0 || index == 1 || index == 2 || index == 3 || index == 7 || index == 11 || index == 15)) {
        // clone the node and swap blank tile
        Node *newNode = new Node(node->state, node, Direction::DOWN_LEFT, node->depth + 1, node->cost + 3);

        // slide blank tile
        newNode->state[index] = newNode->state[index - 3];
        newNode->state[index - 3] = 0;

        // add new node to frontier list
        addIfNotExpanded(map, frontier, newNode);
    }

    /* bottom right */
    if (!(index == 4 || index == 7 || index == 11 || index == 12 || index == 13 || index == 14 || index == 15)) {
        // clone the node and swap blank tile
        Node *newNode = new Node(node->state, node, Direction::DOWN_RIGHT, node->depth + 1, node->cost + 3);

        // slide blank tile
        newNode->state[index] = newNode->state[index + 5];
        newNode->state[index + 5] = 0;

        // add new node to frontier list
        addIfNotExpanded(map, frontier, newNode);
    }
}

void printExpandedList(std::unordered_map<std::string, bool> &expandedList) {
    std::cout << "===== Expanded List =====\n";
    for (auto &it : expandedList) {
        // Do stuff
        std::cout << it.first << std::endl;
    }
    std::cout << "=========================\n";
}

void debugNode(const Node &node) {
    printf("============== NODE INFO ==============\n");
    printTable(node.state);
    printf("Parent move: %d\n", node.parentMove);
    printf("Depth: %d\n", node.depth);
    printf("Cost: %d\n", node.cost);
    printf("================= END =================\n");
}