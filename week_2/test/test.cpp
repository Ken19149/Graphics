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

void doMxV(double A[3][3], double B[3], double S[3]) {
    // TODO: Multiply matrix A by vector B, store result in S
    for (int i=0;i<3;i++) {
        S[i] = A[i][0]*B[0] +  A[i][1]*B[1] + A[i][2]*B[2]; 
    }
}

void displayM(double A[3][3]) { 
  // TODO: Multiply two 3x3 matrices: C = A × B
    std::cout << std::fixed << std::setprecision(0);
    for (int i=0;i<3;i++) {
        std::cout << "[ ";
        for (int j=0;j<3;j++) {
            std::cout << (A[i][j]) << " ";
        }
        std::cout << "]" << std::endl;
    }
}


void displayV(double A[3]) {
    // TODO: Display vector in a readable
    std::cout << std::fixed << std::setprecision(0);
    for (int i=0;i<3;i++) {
        std::cout << "[ " << A[i] << " ]" << std::endl;
    }
}

int main() {
    double A[3][3] = {{1,2,3},{0,0,0},{1,1,1}};
    double B[3][3] = {{2,2,2},{3,2,1},{0,1,2}};
    double C[3][3];
    double V[3] = {7,2,6};
    double S[3];

    doMxM(A, B, C);
    displayM(C);
    displayV(V);
    doMxV(C, V, S);
    displayV(S);
    return 0;
}