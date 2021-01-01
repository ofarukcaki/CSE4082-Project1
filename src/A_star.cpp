#include "A_star.h"
#include "utils.h"
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

// Will return the index to be expanded next on frontier list
int h1(const std::vector<Node *> &frontier, const int goalState[]) {
    // Node which has smallest cost + estimated cost
    // Node *smallestNode;
    int index = 0;
    int smallestIndex = 0;
    int smallest = std::numeric_limits<int>::max();

    // iterate over frontier to find smalles cost
    for (const auto &x : frontier) {
        // TODO: Frontier list büyüdükçe en küçük costu bulmak için en sona kadar gitmek(yeni eklenenler için) çok uzun sürebilir
        // yeni node'lar vektörün sonuna eklendiği için vektörün arkaasından aramaya başlayabiliriz
        // yeni expand edilen node'lar arasında eğer bir önceki costtan daha düşük olan var onu expand ederiz

        // calculate h1 value
        int misplaced = 0;
        for (int i = 0; i < 16; i++) {
            if (x->state[i] != goalState[i])
                misplaced++;
        }

        if ((x->cost + misplaced) < smallest) {
            // smallest so far
            smallest = x->cost + misplaced;
            smallestIndex = index;
        }
        // printf("Misplaced: %d  Cost: %d   Total: %d\n", misplaced, x->cost, x->cost + misplaced);
        index++;
    }
    // printf("Smallest index: %d\n", smallestIndex);
    return smallestIndex;
}

std::vector<Direction> A_star_search(const int startingState[], const int goalState[]) {
    // // std::vector<Direction> A_star_search(int a, int b) {
    int expanded = 0;             // # of expanded nodes
    std::vector<Node *> frontier; // frontier list

    // expanded list, keeps previously visited states
    std::unordered_map<std::string, bool> expandedList;

    Node *startNode = new Node(startingState, NULL, Direction::None, 0, 0);

    // add root node to expanded list
    addExpanded(expandedList, startNode->state);

    // Add root to frontier list
    frontier.push_back(startNode);
    Node *current = frontier.front(); // get the root node without removing from frontier list(yet)

    while (true) {
        // index of the frontier list element to be expanded
        int index = h1(frontier, goalState);

        // select the current(to be expanded) node based returned index from h1
        current = frontier[index];

        // expand selected ndoe by adding it's children to frontier
        expand_node(expandedList, frontier, current);

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

    // until first node
    while (current->parentMove != 8) {
        // printTable(current->state);
        std::cout << current->parentMove << " ";
        current = current->parentNode;
    }

    // TODO: construct the path after finding the solution and return
    std::vector<Direction>
        path = {Direction::UP};
    return path;
}