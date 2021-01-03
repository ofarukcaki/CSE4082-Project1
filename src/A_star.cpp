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
int h1(const std::vector<Node *> &frontier, const int goalState[], int newNodes, Node *current) {
    // Node which has smallest cost + estimated cost
    // Node *smallestNode;
    int index = 0;
    int smallestIndex = 0;
    int smallest = std::numeric_limits<int>::max();
    /*
    // Extra optimization 🚀
    int frontierLength = frontier.size();
    if (frontierLength != 0) {
        // calculate parent's cost, we aim to find smaller cost than this
        int misplaced_inner_parent = 0;
        for (int j = 0; j < 16; j++) {
            if (current->state[j] != goalState[j])
                misplaced_inner_parent++;
        }
        int parentCost = current->cost + misplaced_inner_parent; // parent's cost + estimated cost

        int smallest_child_cost = parentCost;
        int smallest_child_inner_index;

        // printf("parent cost: %d\n", parentCost);

        // check last <newNodes> nodes to find smaller value than last expanded node.
        for (int i = 0; i < newNodes; i++) {
            Node *temp = frontier[frontierLength - 1 - i];
            int misplaced_inner = 0;
            for (int j = 0; j < 16; j++) {
                if (temp->state[j] != goalState[j])
                    misplaced_inner++;
            }

            int child_total_cost = temp->cost + misplaced_inner;

            // printf(">> [%d] %d  total: %d\n", frontierLength - 1 - i, temp->cost, child_total_cost);

            if (child_total_cost < smallest_child_cost) {
                // a smaller(cost) child is found
                smallest_child_cost = child_total_cost;

                // set index
                smallest_child_inner_index = frontierLength - 1 - i;
            }
        }

        if (smallest_child_cost < parentCost) {
            // printf("[NEW_ADDED]Smallest index: %d  smallest cost: %d\n", smallest_child_inner_index, smallest_child_cost);
            // smaller cost node is available among new added nodes, return it's index
            return smallest_child_inner_index;
        }
    }
*/
    // iterate over frontier to find smalles cost
    for (const auto &x : frontier) {
        // TODO: Frontier list büyüdükçe en küçük costu bulmak için en sona kadar gitmek(yeni eklenenler için) çok uzun sürebilir
        // yeni node'lar vektörün sonuna eklendiği için vektörün arkaasından aramaya başlayabiliriz
        // yeni expand edilen node'lar arasında eğer bir önceki costtan daha düşük olan var onu expand ederiz

        // TODO: node'un costu yeterince büyükse h1 hesaplamaya gerek yok, skip edilebilir
        // if (x->cost > smallest)
        //     continue;

        // calculate h1 value
        // misplaced = 0;
        // for (int i = 0; i < 16; i++) {
        //     if (x->state[i] != goalState[i])
        //         misplaced++;
        // }
        int misplaced = getMisplacedCount(x->state, goalState);

        /*
        // printf("Mispalced: %d\n", misplaced);
        if (misplaced == 0) {
            std::cout << "MISPLACED IS 0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
            // std::exit(0);
        }
*/
        // if (x->isGoal(goalState)) {
        //     std::cout << "GOALSTATE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        //     std::exit(0);
        // }

        if ((x->cost + misplaced) < smallest) {
            // smallest so far
            smallest = (x->cost + misplaced);
            smallestIndex = index;
        }
        // printf("Misplaced: %d  Cost: %d   Total: %d\n", misplaced, x->cost, x->cost + misplaced);
        index++;
    }
    if (smallest > 25) {
        printf("Smallest index: %d  Smallest val: %d \n", smallestIndex, smallest);
    }
    return smallestIndex;
}

int h2(const std::vector<Node *> &frontier, const int goalState[], int newNodes, Node *current) {
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

std::vector<Direction> A_star_search(const int startingState[], const int goalState[]) {
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
        // int index = h1(frontier, goalState, newNodes, current);
        int index = h1(frontier, goalState, newNodes, current);

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
    printf("Total  Expanded: %d\n", expanded);
    printf("Max # of nodes stored in memory: %d\n", maxNodes + 1);

    printTable(current->state);
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