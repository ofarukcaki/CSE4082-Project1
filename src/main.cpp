#include "main.h"
#include "utils.h"

using namespace std;

int main() {

    int initial_state[16] = {1, 12, 11, 10, 2, 13, 8, 9, 3, 14, 15, 0, 4, 5, 6, 7};

    // How to create a new node:
    // Node parent(initial_state, NULL, Direction::LEFT, 0, 1);
    // Node child(initial_state, &parent, Direction::DOWN_LEFT, 1, 5);
    // cout << "Child: " << child.cost << " " << child.depth << endl;
    // cout << child.parentNode->depth << endl;

    return 0;
}