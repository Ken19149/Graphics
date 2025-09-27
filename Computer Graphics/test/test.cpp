#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>

// Matrix operations - Students implement these
void Zero(int Matrix[3][3]) {
    
    Matrix[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
}


int main() {
    int Matrix[3][3];
    std::cout << Matrix[3][3] << std::endl;
    Zero(Matrix);
    std::cout << Matrix[3][3] << std::endl;
    return 0;
}