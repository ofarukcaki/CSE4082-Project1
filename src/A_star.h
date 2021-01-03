#ifndef A_STAR_H
#define A_STAR_H
#include "main.h"

// returns the path to solution from starting state to goal state
void A_star_search(const int startingState[], const int goalState[], int heuristic);
// std::vector<Direction> A_star_search(int a, int b);

#endif