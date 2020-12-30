#include "main.h"
#include <cmath>
#include <iostream>

int Manhattan(int x1, int y1, int x2, int y2) {
    return std::abs(x2 - x1) + abs(y2 - y1);
}
