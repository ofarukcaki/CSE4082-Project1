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
                 DOWN_RIGHT };

class Node {
public:
    int state[16];             // The state of the node
    enum Direction parentMove; // The operation that generated this node from the parent
    int depth;                 // Depth of this node (parent.depth +1)
    int cost;                  // Path cost of this node from depth 0.
    Node *parentNode;          // Pointer to the node which created this node

    // Constructor
    Node(int state[], Node *parentNode, enum Direction parentMove, int depth, int cost) {
        std::copy(state, state + 16, this->state); // copy the state array
        this->parentMove = parentMove;
        this->depth = depth;
        this->cost = cost;
        this->parentNode = parentNode;
    }

    // Destructor
    ~Node() {
        //
    }
};

#endif