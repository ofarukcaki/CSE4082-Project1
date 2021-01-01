#include "main.h"
#include "A_star.h"
#include "utils.h"
#include <time.h>

using namespace std;

int main() {

    int initial_state[16] = {1, 12, 11, 10, 2, 13, 8, 9, 3, 14, 15, 0, 4, 5, 6, 7};
    int goal_state[16] = {1, 12, 11, 10, 2, 13, 0, 9, 3, 14, 15, 8, 4, 5, 6, 7};
    int close_to_goal[16] = {1, 12, 11, 10, 2, 13, 9, 0, 3, 14, 15, 8, 4, 5, 6, 7};

    int test_state[16] = {0, 12, 11, 10, 2, 1, 13, 9, 3, 14, 15, 8, 4, 5, 6, 7};
    int case_1[16] = {0, 12, 11, 10, 1, 13, 14, 9, 3, 2, 15, 8, 4, 5, 6, 7};
    int case_2[16] = {1, 2, 11, 0, 3, 13, 12, 10, 5, 14, 9, 8, 4, 15, 6, 7};
    int case_3[16] = {1, 12, 9, 10, 13, 11, 8, 6, 3, 2, 15, 14, 4, 5, 7, 0};

    // int c = totalManhattan(case_2);
    // printf("Total Manhattan dist: %d\n", c);
    // printTable(case_2);
    // printTable(goal_state);
    // std::exit(0);

    time_t start = time(0); // start time

    std::vector<Direction> path = A_star_search(case_3, goal_state);

    // print time took
    double seconds_since_start = difftime(time(0), start);
    std::cout << "Time passed: " << seconds_since_start << std::endl;

    return 0;
};