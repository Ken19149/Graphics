// hw2_starter.cpp : Basic framework for 2D transformations and viewing
// 
#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#define DegreesToRadius 0.017460317460317460317460317460317
#define MAX 50

using namespace std;
int height, width;

// Matrices for transformations
double TM[3][3], RM[3][3], SM[3][3], OM[3][3], CM[3][3], V[3];
double S[MAX][MAX][4][3]; // Storage for squares
double T[MAX][MAX][3][3]; // Storage for triangles
double WVM[MAX][MAX][3][3], W[MAX][MAX][3][3]; // Window-to-viewport matrix
int Sn=0, Tn=0, Wn=0, Cn=0;

// Window and viewport coordinates
double WL, WR, WB, WT, VL, VR, VB, VT;

// Function declarations - Students need to implement these
void drawDot(int x, int y, double r, double g, double b);
void drawLine(int x1, int y1, int x2, int y2);
void Zero(double Matrix[3][3]);
void Identity(double Matrix[3][3]);
void doMxM(double A[3][3], double B[3][3], double C[3][3]);
void doMxV(double A[3][3], double B[3], double S[3]);
void displayM(double A[3][3]);
void displayV(double A[3]);
void Square();
void Triangle();
void drawSquare();
void drawTriangle();
void drawViewport(double VL, double VR, double VB, double VT);
void translate(double dx, double dy);
void rotate(double degree);
void scale(double sx, double sy);

// Basic drawing function - Students implement this
void drawDot(int x, int y, double r, double g, double b) {
    // TODO: Implement dot drawing using OpenGL
    // Hint: Use glBegin(GL_POINTS), glColor3f(), glVertex2i(), glEnd()
    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2i(x, height - y);
    glEnd();
}

// Line drawing function - Students implement this using Bresenham's algorithm
void drawLine(int x1, int y1, int x2, int y2) {
    // TODO: Implement Bresenham's line drawing algorithm
    // Handle all four octants: dx>0 dy>0, dx>0 dy<0, etc.
    // Use drawDot() to plot individual points
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int n = abs(dx) >= abs(dy) ? dx : dy;

    for (int i=0; i<=n; i++) {
        drawDot(x1, y1, 1.0, 1.0, 1.0);
        if ((x1 == x2) && (y1 == y2)) return;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

// Matrix operations - Students implement these
void Zero(double Matrix[3][3]) {
    // TODO: Set all elements of the matrix to 0
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            Matrix[i][j] = 0;
        }
    }
}

void Identity(double Matrix[3][3]) {
    // TODO: Set matrix to identity matrix (1 on diagonal, 0 elsewhere)
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (i == j) {
                Matrix[i][j] = 1;
            }
            else {
                Matrix[i][j] = 0;
            }
        }
    }
}


void doMxM(double A[3][3], double B[3][3], double S[3][3]) {
    // TODO: Multiply two 3x3 matrices: C = A × B
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            S[i][j] = A[i][0]*B[0][j] + A[i][1]*B[1][j] + A[i][2]*B[2][j];
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
    // TODO: Display matrix in a readable format
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
    // TODO: Display vector in a readable format
    std::cout << std::fixed << std::setprecision(0);
    for (int i=0;i<3;i++) {
        std::cout << "[ " << A[i] << " ]" << std::endl;
    }
}

// Shape creation functions
void Square() {
    // TODO: Create a unit square centered at origin
    // Store the 4 corner points after applying current transformation matrix
    double S[4][3];
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

void Triangle() {
    // TODO: Create a triangle with points (0,1), (-1,-1), (1,-1)
    // Store the 3 points after applying current transformation matrix
    double T[3][3];
    T[0][0] = 0.0;
    T[0][1] = 1.0;
    T[0][2] = 1.0;
    T[1][0] = -1.0;
    T[1][1] = -1.0;
    T[1][2] = 1.0;
    T[2][0] = 1.0;
    T[2][1] = -1.0;
    T[2][2] = 1.0;
}

// Drawing functions
void drawSquare() {
    // TODO: Draw all stored squares
    // For each square, draw 4 lines connecting the points
    // Apply viewport transformation before drawing
    double S[4][3];
    for (int i=0;i<4;i++) {
        drawLine(S[i][0], S[i][1], S[i+1][0], S[i+1][1]);
    }
    drawLine(S[3][0], S[3][1], S[0][0], S[0][1]);
}

void drawTriangle() {
    // TODO: Draw all stored triangles
    // For each triangle, draw 3 lines connecting the points
    // Apply viewport transformation before drawing
    double T[3][3];
    for (int i=0;i<3;i++) {
        drawLine(T[i][0], T[i][1], T[i+1][0], T[i+1][1]);
    }
    drawLine(T[2][0], T[2][1], T[0][0], T[0][1]);
}

void drawViewport(double VL, double VR, double VB, double VT) {
    // TODO: Draw the viewport boundary as a rectangle
    // Use drawLine() to draw the four sides
    drawLine(VR, VT, VR, VB);
    drawLine(VR, VB, VL, VB);
    drawLine(VL, VB, VL, VT);
    drawLine(VL, VT, VR, VT);
}

// Transformation functions - Students implement these
void translate(double dx, double dy) {
    // TODO: Create translation matrix and update current transformation
    // TM = translation matrix, CM = cumulative transformation
    double TM[3][3] = {{1,0,dx},{0,1,dy},{0,0,1}};
    doMxM(TM, CM, CM);
}

void rotate(double degree) {
    // TODO: Create rotation matrix and update current transformation
    // Convert degrees to radians first
    double RM[3][3] = {{cos(degree), -sin(degree), 0},{sin(degree), cos(degree), 0},{0,0,1}};
    doMxM(RM, CM, CM);
}

void scale(double sx, double sy) {
    // TODO: Create scaling matrix and update current transformation
    double SM[3][3] = {{1,sx,0},{0,sy,0},{0,0,1}};
    doMxM(SM, CM, CM);
}

// File reading function - Provided to students
void readFile() {
    string command;
    string filename = "hw2.in"; // Students can change this for testing
    ifstream fin(filename);

    if(fin.is_open()) {
        while(fin >> command) {
            if(command.find("#") != command.npos) {
                getline(fin, command); // Skip comments
                continue;
            }
            else if(command == "square") {
                Square();
                Sn++;
            }
            else if(command == "triangle") {
                Triangle();
                Tn++;
            }
            else if(command == "translate") {
                double Tx, Ty;
                fin >> Tx >> Ty;
                translate(Tx, Ty);
            }
            else if(command == "scale") {
                double Sx, Sy;
                fin >> Sx >> Sy;
                scale(Sx, Sy);
            }
            else if(command == "rotate") {
                double R;
                fin >> R;
                rotate(R);
            }
            else if(command == "view") {
                fin >> WL >> WR >> WB >> WT >> VL >> VR >> VB >> VT;
                drawViewport(VL, VR, VB, VT);
                
                // Calculate window-to-viewport transformation
                double Vx = (VR - VL)/(WR - WL);
                double Vy = (VT - VB)/(WT - WB);
                
                Identity(WVM[Cn][Wn]);
                Identity(W[Cn][Wn]);
                WVM[Cn][Wn][0][0] = Vx;
                WVM[Cn][Wn][1][1] = Vy;
                WVM[Cn][Wn][0][2] = VL;
                WVM[Cn][Wn][1][2] = VB;
                
                W[Cn][Wn][0][2] = -WL;
                W[Cn][Wn][1][2] = -WB;
                doMxM(WVM[Cn][Wn], W[Cn][Wn], CM);
                
                drawSquare();
                drawTriangle();
                Wn++;
            }
            else if(command == "reset") {
                Identity(TM);
                Identity(RM);
                Identity(SM);
                Identity(OM);
                Identity(CM);
                Sn = 0; Tn = 0; Wn = 0;
                Cn++;
            }
            else if(command == "end") {
                break;
            }
        }
        fin.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

// Display function
void displayFunc(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    readFile();
    
    glFlush();
}

// Main function
int main(int ac, char** av) {
    int winSizeX = 800, winSizeY = 600;
    
    if(ac == 3) {
        winSizeX = atoi(av[1]);
        winSizeY = atoi(av[2]);
    }

    width = winSizeX;
    height = winSizeY;

    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winSizeX, winSizeY);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations - Student Implementation");
    
    glutDisplayFunc(displayFunc);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, winSizeX, 0, winSizeY);

    glutMainLoop();
    return 0;
}