#include "main.h"
#include "A_star.h"
#include "ILS.h"
#include "UCS.h"
#include "utils.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

using namespace std;

// argv[2] is the algorithm: ucs | ils | h1 | h2 | h3
// argv[1] is the filename to read
// Example: ./15Puzzle h2 input.txt  -> Solve the puzzle on the input.txt by using h2 A* heuristic
int main(int argc, char **argv) {
    vector<vector<string>> data;
    ifstream infile(argv[1]);
    string line;
    string str;

    //  Read the file
    getline(infile, line);
    istringstream ss(line);

    int input[16];

    // read input from file
    for (int j = 0; j < 16; j++) {
        getline(ss, str, ',');
        stringstream ii(str);
        int x;
        ii >> x;
        input[j] = x;
    }

    printf("Input: ");
    for (int i = 0; i < 16; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");
    printTable(input);

    int goal_state[16] = {1, 12, 11, 10, 2, 13, 0, 9, 3, 14, 15, 8, 4, 5, 6, 7};
    /*
    int case_1[16] = {0, 12, 11, 10, 1, 13, 14, 9, 3, 2, 15, 8, 4, 5, 6, 7};
    int case_2[16] = {1, 2, 11, 0, 3, 13, 12, 10, 5, 14, 9, 8, 4, 15, 6, 7};
    int case_3[16] = {1, 12, 9, 10, 13, 11, 8, 6, 3, 2, 15, 14, 4, 5, 7, 0};
    */

    auto start = chrono::high_resolution_clock::now(); // start timer

    // Run the algorithm of choice according the command line arg. provided
    if (argv[2] == "ucs"sv) {
        UCS(input, goal_state);
    } else if (argv[2] == "ils"sv) {
        ILS_master(input, goal_state);
    } else if (argv[2] == "h1"sv) {
        A_star_search(input, goal_state, 1);
    } else if (argv[2] == "h2"sv) {
        A_star_search(input, goal_state, 2);
    } else if (argv[2] == "h3"sv) {
        A_star_search(input, goal_state, 3);
    }

    // print time took
    auto stop = chrono::high_resolution_clock::now(); // stop timer
    std::cout << "Time passed: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << "ms" << std::endl;

    return 0;
};