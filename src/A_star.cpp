#include "A_star.h"
#include "utils.h"
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

int prevCost = std::numeric_limits<int>::max();

int getMisplacedCount(const int state[], const int goalState[]) {
    int mis = 0;
    for (int i = 0; i < 16; i++) {
        if (state[i] != goalState[i]) {
            mis = mis + 1;
        }
    }
    return mis;
}

// Will return the index to be expanded next on frontier list
int h1(const std::vector<Node *> &frontier, const int goalState[], int newNodes, const Node *current) {
    // Node which has smallest cost + estimated cost
    // Node *smallestNode;
    int index = 0;
    int smallestIndex = 0;
    int smallest = std::numeric_limits<int>::max();

    // iterate over frontier to find smalles cost
    for (const auto &x : frontier) {

        // node'un costu yeterince büyükse h1 hesaplamaya gerek yok, skip edilebilir
        if (x->cost > smallest) {

        } else {
            int misplaced = getMisplacedCount(x->state, goalState);

            if ((x->cost + misplaced) < smallest) {
                // smallest so far
                smallest = (x->cost + misplaced);
                smallestIndex = index;
            }
        }

        // printf("Misplaced: %d  Cost: %d   Total: %d\n", misplaced, x->cost, x->cost + misplaced);
        index++;
    }
    return smallestIndex;
}

int h2(const std::vector<Node *> &frontier, const int goalState[], int newNodes, const Node *current) {
    // Node which has smallest cost + estimated cost
    // Node *smallestNode;
    int index = 0;
    int smallestIndex = 0;
    int smallest = std::numeric_limits<int>::max();

    // iterate over frontier to find smalles cost
    for (const auto &x : frontier) {
        if (x->cost > smallest)
            continue;

        // get h2 value
        int manhattan_dist = totalManhattan(x->state);

        if ((x->cost + manhattan_dist) < smallest) {
            // smallest so far
            smallest = x->cost + manhattan_dist;
            smallestIndex = index;
        }
        // printf("Misplaced: %d  Cost: %d   Total: %d\n", misplaced, x->cost, x->cost + misplaced);
        index++;
    }
    // printf("Smallest index: %d  Smallest val: %d\n", smallestIndex, smallest);

    return smallestIndex;
}

int h3(const std::vector<Node *> &frontier, const int goalState[], int newNodes, const Node *current) {
    // Node which has smallest cost + estimated cost
    // Node *smallestNode;
    int index = 0;
    int smallestIndex = 0;
    int smallest = std::numeric_limits<int>::max();

    // iterate over frontier to find smalles cost
    for (const auto &x : frontier) {
        if (x->cost > smallest)
            continue;

        // get h2 value
        int manhattan_dist = totalH3_dist(x->state);

        if ((x->cost + manhattan_dist) < smallest) {
            // smallest so far
            smallest = x->cost + manhattan_dist;
            smallestIndex = index;
        }
        // printf("Misplaced: %d  Cost: %d   Total: %d\n", misplaced, x->cost, x->cost + misplaced);
        index++;
    }
    // printf("Smallest index: %d  Smallest val: %d\n", smallestIndex, smallest);

    return smallestIndex;
}

void A_star_search(const int startingState[], const int goalState[], int heuristic) {
    int expanded = 0;             // # of expanded nodes
    int maxNodes = 0;             // # of nodes stored in memory
    std::vector<Node *> frontier; // frontier list

    // expanded list, keeps previously visited states
    std::unordered_map<std::string, bool> expandedList;

    Node *startNode = new Node(startingState, NULL, Direction::None, 0, 0);

    // add root node to expanded list
    addExpanded(expandedList, startNode->state);

    int newNodes = 0;

    // Add root to frontier list
    frontier.push_back(startNode);
    Node *current = frontier.front(); // get the root node without removing from frontier list(yet)

    while (true) {
        // index of the frontier list element to be expanded
        int index;
        if (heuristic == 1) {
            index = h1(frontier, goalState, newNodes, current);
        } else if (heuristic == 2) {
            index = h2(frontier, goalState, newNodes, current);
        } else if (heuristic == 3) {
            index = h3(frontier, goalState, newNodes, current);
        }

        // int index = h2(frontier, goalState, newNodes, current);

        // select the current(to be expanded) node based returned index from h1
        current = frontier[index];

        // expand selected node by adding it's children to frontier
        newNodes = expand_node(expandedList, frontier, current);

        expanded++;
        maxNodes += newNodes; // newly expanded nodes minus last deleted node
        // printf("Expanded: %d\n", newNodes);

        if (current->isGoal(goalState)) {
            std::cout << "*** Goal State Reached ***" << std::endl;
            break; // exit while loop
        } else {
            // not a goal state
        }

        // delete frontier[index]; // deallocate space

        // remove from frontier
        frontier.erase(frontier.begin() + index);
        // printFrontierListTables(frontier);
    }

    // printTable(startingState);

    printf("\nCost of solution: %d\n", current->cost);
    printf("Total  Expanded: %d\n", expanded + 1); // +1 for the parent
    printf("Max # of nodes stored in memory: %d\n", maxNodes + 1);

    std::vector<int> path;

    printTable(current->state);

    // until first node
    while (current->parentMove != 8) {
        // printTable(current->state);
        // std::cout << current->parentMove << " ";
        path.push_back(current->parentMove);
        current = current->parentNode;
    }

    printPath(path);
}