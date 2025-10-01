#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>

#define MAX 50

// double S[MAX][MAX][4][3]; // Storage for squares
double S[4][3];

void Square();


void Square() {
    // TODO: Create a unit square centered at origin
    // Store the 4 corner points after applying current transformation matrix
    // double S[4][3];
    S[0][0] = 1.0;
    S[0][1] = 1.0;
    S[0][2] = 1.0;
    S[1][0] = -1.0;
    S[1][1] = 1.0;
    S[1][2] = 1.0;
    S[2][0] = -1.0;
    S[2][1] = -1.0;
    S[2][2] = 1.0;
    S[3][0] = 1.0;
    S[3][1] = -1.0;
    S[3][2] = 1.0;
}

int main() {
    Square();
    std::cout << S[0][0];
    return 0;
}