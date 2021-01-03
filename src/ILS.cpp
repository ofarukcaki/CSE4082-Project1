#include "ILS.h"
#include "A_star.h"
#include "UCS.h"
#include "utils.h"
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

int select_ILS(const std::vector<Node *> &frontier, Node *current) {

    int index = 0;
    int smallestIndex = 0;
    int smallest = std::numeric_limits<int>::max();

    for (const auto &x : frontier) {
        if ((x->cost) < smallest) {
            // smallest so far
            smallest = x->cost;
            smallestIndex = index;
        }
        index++;
    }
    return smallestIndex;
}

bool ILS(const int startingState[], const int goalState[], int limit) {
    // // std::vector<Direction> A_star_search(int a, int b) {
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

    while (frontier.size() > 0) {
        // index of the frontier list element to be expanded

        // TODO: Replace with UCS
        // int index = h1(frontier, goalState, newNodes, current);
        int index = select_ILS(frontier, current);

        // select the current(to be expanded) node based returned index from h1
        current = frontier[index];

        // expand selected node by adding it's children to frontier
        newNodes = expand_node_ils(expandedList, frontier, current, limit);

        // printFrontierListCosts(frontier);
        expanded++;
        maxNodes += newNodes; // newly expanded nodes minus last deleted node
        // printf("Expanded: %d\n", newNodes);

        if (current->isGoal(goalState)) {
            std::cout << "*** Goal State Reached ***" << std::endl;

            printf("\nCost of solution: %d\n", current->cost);
            printf("Total  Expanded: %d\n", expanded);
            printf("Max # of nodes stored in memory: %d\n", maxNodes + 1);

            // until first node
            while (current->parentMove != 8) {
                // printTable(current->state);
                std::cout << current->parentMove << " ";
                current = current->parentNode;
            }

            return true; // exit while loop
        } else {
            // not a goal state
        }

        // remove from frontier
        frontier.erase(frontier.begin() + index);
    }

    // printTable(startingState);
    return false;
    // TODO: construct the path after finding the solution and return
}

void ILS_master(const int startingState[], const int goalState[]) {
    int limit = 1;
    bool found = false; // goal state found or not

    while (found == false) {
        printf("Limit: %d\n", limit);
        found = ILS(startingState, goalState, limit);
        limit++;
    }
}