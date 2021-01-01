#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <vector>

enum Direction { UP,
                 DOWN,
                 LEFT,
                 RIGHT,
                 UP_LEFT,
                 UP_RIGHT,
                 DOWN_LEFT,
                 DOWN_RIGHT,
                 None // for the root node
};

class Node {
public:
    int state[16];             // The state of the node
    enum Direction parentMove; // The operation that generated this node from the parent
    int depth;                 // Depth of this node (parent.depth +1)
    int cost;                  // Path cost of this node from depth 0.
    Node *parentNode;          // Pointer to the node which created this node

    // Constructor
    Node(const int state[], Node *parentNode, enum Direction parentMove, int depth, int cost) {
        std::copy(state, state + 16, this->state); // copy the state array
        this->parentMove = parentMove;
        this->depth = depth;
        this->cost = cost;
        this->parentNode = parentNode;
    }

    // Destructor
    ~Node() {
        //
        // printf("Destructor called\n");
        // printf("Class object going to be destructed: [%d, %d, %d...]\n", this->state[0], this->state[1], this->state[2]);
    }

    // whether it's a goal state or not
    bool isGoal(const int goalState[]) {
        // compare state array with the goal state
        return std::equal(this->state, this->state + 16, goalState);
    }
};

#endif