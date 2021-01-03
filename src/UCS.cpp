#include "UCS.h"
#include "A_star.h"
#include "utils.h"
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

int select_UCS(const std::vector<Node *> &frontier, Node *current) {

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

void UCS(const int startingState[], const int goalState[]) {
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

    while (true) {
        // index of the frontier list element to be expanded

        // TODO: Replace with UCS
        // int index = h1(frontier, goalState, newNodes, current);
        int index = select_UCS(frontier, current);

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