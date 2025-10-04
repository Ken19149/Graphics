#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <vector>
#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;
int screenWidth = 800;                     // HERE
int screenHeight = 600;                    // HERE
vector<pair<pair<int, int>, int>> circles; // Store (center, radius)
bool drawingCircle = false;
int circleCenterX, circleCenterY;
void drawDot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Bresenham Circle Drawing Algorithm
void drawCircleBresenham(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int pk = 3 - 2 * r;

    while (x <= y)
    {
        // Draw all eight symmetric points
        drawDot(xc + x, yc + y); // Quadrant1
        drawDot(xc + y, yc + x); // ... Quadrant2
        drawDot(xc + y, yc - x); // ... Quadrant3
        drawDot(xc + x, yc - y); // ... Quadrant4
        drawDot(xc - x, yc - y); // ... Quadrant5
        drawDot(xc - y, yc - x); // ... Quadrant6
        drawDot(xc - y, yc + x); // ... Quadrant7
        drawDot(xc - x, yc + y); // ... Quadrant8
        x++;
        if (pk < 0)
        {
            // pk ... case #1  <-- HERE
            pk = pk + 4*x + 6;
        }
        else
        {
            y--;
            // pk ... case #2  <-- HERE
            pk = pk + 4*(x-y) + 10;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // <-- HERE

    // Draw all circles using Bresenham algorithm
    for (const auto &circle : circles)
    {
        drawCircleBresenham(circle.first.first, circle.first.second, circle.second);
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    y = screenHeight - y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (!drawingCircle)
        {
            circleCenterX = x;
            circleCenterY = y;
            drawingCircle = true;
            cout << "Circle center at (" << x << ", " << y << ")" << endl;
        }
        else
        {
            int radius = (int)sqrt(pow(x - circleCenterX, 2) + pow(y - circleCenterY, 2));
            circles.push_back({{circleCenterX, circleCenterY}, radius});
            drawingCircle = false;
            cout << "Circle with radius: " << radius << " (Bresenham Algorithm)" << endl;
        }
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        circles.clear();
        cout << "Screen cleared" << endl;
    }
    else if (key == 'q' || key == 'Q')
    {
        exit(0);
    }
    glutPostRedisplay();
}
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glPointSize(2.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100); // <-- HERE
    glutCreateWindow("Bresenham Circle Algorithm");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    cout << "=== Bresenham Circle Algorithm ===" << endl;
    cout << "Click for center, then click for radius" << endl;
    cout << "Space - Clear Screen" << endl;
    cout << "Q - Quit" << endl;

    glutMainLoop();
    return 0;
}