#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>

void doMxM(double A[3][3], double B[3][3], double C[3][3]) {
    // TODO: Multiply two 3x3 matrices: C = A × B
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            C[i][j] = A[i][0]*B[0][j] + A[i][1]*B[1][j] + A[i][2]*B[2][j];
            // std::cout << std::to_string(C[i][j]) << std::endl;
        }
    }
}


void displayM(double A[3][3]) { 
  // TODO: Multiply two 3x3 matrices: C = A × B
    std::cout << std::fixed;

    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            std::cout << std::to_string(A[i][j]) << std::endl;
        }
    }
}

int main() {
    double A[3][3] = {{1,2,3},{0,0,0},{1,1,1}};
    double B[3][3] = {{2,2,2},{3,2,1},{0,1,2}};
    double C[3][3];

    doMxM(A, B, C);
    displayM(C);
    return 0;
}