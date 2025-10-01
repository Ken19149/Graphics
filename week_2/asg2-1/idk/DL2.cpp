// simplified_line_clipping_fixed.cpp
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif
using namespace std;
int width, height;
// Viewport coordinates
double VL, VR, VB, VT;
// Cohen-Sutherland region codes
const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;
void drawDot(double x, double y, double r, double g, double b)
{
    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2d(x, y);
    glEnd();
}

void drawLine(double x1, double y1, double x2, double y2)
{
    // Simple DDA line algorithm for better understanding
    double dx = x2 - x1;
    double dy = y2 - y1;
    double steps = max(abs(dx), abs(dy));

    if (steps == 0)
    {
        drawDot(x1, y1, 1.0, 1.0, 1.0);
        return;
    }

    double xIncrement = dx / steps;
    double yIncrement = dy / steps;

    double x = x1;
    double y = y1;

    for (int i = 0; i <= steps; i++)
    {
        drawDot(round(x), round(y), 1.0, 1.0, 1.0);
        x += xIncrement;
        y += yIncrement;
    }
}
// Determine region code for a point
int getRegionCode(double x, double y)
{
    int code = INSIDE;

    if (x < VL)
        code |= LEFT;
    else if (x > VR)
        code |= RIGHT;

    if (y < VB)
        code |= BOTTOM;
    else if (y > VT)
        code |= TOP;

    return code;
}

// Cohen-Sutherland line clipping algorithm
void clipAndDrawLine(double x0, double y0, double x1, double y1)
{
    cout << "Original line: (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ")" << endl;

    int code0 = getRegionCode(x0, y0);
    int code1 = getRegionCode(x1, y1);
    bool accept = false;

    int iteration = 0;
    while (true)
    {
        iteration++;
        if (iteration > 10)
            break; // Safety check

        if (!(code0 | code1))
        {
            // Both endpoints inside viewport - accept line
            accept = true;
            break;
        }
        else if (code0 & code1)
        {
            // Both endpoints outside same region - reject line
            break;
        }
        else
        {
            // Line needs clipping
            double x, y;
            int outcode = code0 ? code0 : code1;

            // Find intersection point
            if (outcode & TOP)
            {
                x = x0 + (x1 - x0) * (VT - y0) / (y1 - y0);
                y = VT;
            }
            else if (outcode & BOTTOM)
            {
                x = x0 + (x1 - x0) * (VB - y0) / (y1 - y0);
                y = VB;
            }
            else if (outcode & RIGHT)
            {
                y = y0 + (y1 - y0) * (VR - x0) / (x1 - x0);
                x = VR;
            }
            else
            { // LEFT
                y = y0 + (y1 - y0) * (VL - x0) / (x1 - x0);
                x = VL;

                // Replace outside point with intersection point
                if (outcode == code0)
                {
                    x0 = x;
                    y0 = y;
                    code0 = getRegionCode(x0, y0);
                    cout << " Clipped P0 to: (" << x0 << "," << y0 << ")" << endl;
                }
                else
                {
                    x1 = x;
                    y1 = y;
                    code1 = getRegionCode(x1, y1);
                    cout << " Clipped P1 to: (" << x1 << "," << y1 << ")" << endl;
                }
            }
        }

        if (accept)
        {
            cout << " Final clipped line: (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ")" << endl;
            drawLine(x0, y0, x1, y1);
        }
        else
        {
            cout << " Line completely outside viewport - rejected" << endl;
        }
        cout << endl;
    }
}
void drawViewport()
{
    // Draw viewport boundary in yellow
    glColor3f(1.0, 1.0, 0.0); // Yellow for viewport boundary
    drawLine(VL, VT, VR, VT); // Top
    drawLine(VR, VT, VR, VB); // Right
    drawLine(VR, VB, VL, VB); // Bottom
    drawLine(VL, VB, VL, VT); // Left
    glColor3f(1.0, 1.0, 1.0); // Reset to white for lines
}
void displayInfo()
{
    cout << "=== Line Clipping Demo ===" << endl;
    cout << "Window size: " << width << " x " << height << endl;
    cout << "Viewport: (" << VL << "," << VB << ") to (" << VR << "," << VT << ")" << endl;
    cout << "Viewport size: " << (VR - VL) << " x " << (VT - VB) << endl;
    cout << "==========================" << endl
         << endl;
}
void readAndProcessCommands()
{
    string command;
    string filename = "commands.txt";

    ifstream fin(filename);

    if (fin.is_open())
    {
        cout << "Reading commands from file: " << filename << endl
             << endl;

        while (fin >> command)
        {
            if (command == "viewport")
            {
                fin >> VL >> VR >> VB >> VT;
                cout << ">>> Setting viewport: left=" << VL << ", right=" << VR
                     << ", bottom=" << VB << ", top=" << VT << endl;
                displayInfo();
                drawViewport();
            }
            else if (command == "line")
            {
                double x0, y0, x1, y1;
                fin >> x0 >> y0 >> x1 >> y1;
                cout << ">>> Drawing line..." << endl;
                clipAndDrawLine(x0, y0, x1, y1);
            }
            else if (command == "reset")
            {
                VL = 0;
                VR = width;
                VB = 0;
                VT = height;
                cout << ">>> Reset viewport to full window" << endl;
                displayInfo();
                drawViewport();
            }
            else if (command[0] == '#')
            {
                // Comment - skip the rest of the line
                string comment;
                getline(fin, comment);
                cout << "Comment: " << comment << endl;
            }
        }
        fin.close();
    }
    else
    {
        cout << "Unable to open file '" << filename << "'. Using default demonstration." << endl
             << endl;

        displayInfo();
        drawViewport();

        // Test lines with various clipping scenarios
        cout << ">>> Drawing demonstration lines..." << endl
             << endl;
    }
}
void displayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    readAndProcessCommands();

    glFlush();
}
int main(int ac, char **av)
{
    width = 800;
    height = 600;

    if (ac == 3)
    {
        width = atoi(av[1]);
        height = atoi(av[2]);
    }

    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line Clipping Demo - Cohen-Sutherland Algorithm");
    glutDisplayFunc(displayFunc);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Set up coordinate system to match window pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutMainLoop();
    return 0;
}