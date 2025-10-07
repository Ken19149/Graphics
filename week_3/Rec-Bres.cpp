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
int screenWidth = 800;
int screenHeight = 600;
vector<pair<int, int>> rectangles; // Store pairs of points for rectangles
bool drawingRectangle = false;
int rectStartX, rectStartY;
void drawDot(int x, int y)
{
    glBegin(GL_POINTS); // <-- HERE
    glVertex2i(x, y);   // <-- HERE
    glEnd();
}

void drawLineBresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int n = dy > dx ? dy : dx;

    for (int i = 0; i < n; i++)
    {
        drawDot(x1, y1);
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
        // std::cout << x1 << " " << y1 << std::endl;
    }
}

void drawRectangle(int x1, int y1, int x2, int y2)
{
    // Draw all four sides using Bresenham line algorithm
    drawLineBresenham(x1, y1, x2, y1); // Top
    drawLineBresenham(x2, y1, x2, y2); // Right        // <-- HERE
    drawLineBresenham(x2, y2, x1, y2); // Bottom       // <-- HERE
    drawLineBresenham(x1, y2, x1, y1); // Left

    // cout << "Rectangle drawn using line algorithm" << endl;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // <-- HERE

    /*
    // Draw all rectangles
    for (const auto &rect : rectangles)
    {
        // drawRectangle(rect.first.first, rect.first.second, rect.second.first, rect.second.second);
    } 
    */
   // rewrite the loop

   for (size_t i = 0; i + 1 < rectangles.size(); i += 2)
    {
        drawRectangle(rectangles[i].first, rectangles[i].second,
                          rectangles[i + 1].first, rectangles[i + 1].second);
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    y = screenHeight - y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        /*
        if (!drawingRectangle)
        {
            rectStartX = x;
            rectStartY = y;
            drawingRectangle = true;
            cout << "Rectangle start at (" << x << ", " << y << ")" << endl;
        }
        else
        {
            // rectangles.push_back({{rectStartX, rectStartY}, {x, y}});
            rectangles.push_back({x, y});
            drawingRectangle = false;
            cout << "Rectangle completed!" << endl;
        }
        */

        // the above template doesn't work so used template from the previous bresenham instead :D
        rectangles.push_back({x, y});
        cout << "Rectangle start at (" << x << ", " << y << ")" << endl;

        if (rectangles.size() % 2 == 0)
        {
            cout << "Rectangle completed!" << endl;
        }
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        rectangles.clear();
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

int main(int argc, char** argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize(screenWidth, screenHeight);
 glutInitWindowPosition(100, 100);
 glutCreateWindow("Rectangle Drawing using Line Algorithm");

 init();
 glutDisplayFunc(display);
 glutMouseFunc(mouse);
 glutKeyboardFunc(keyboard);

 cout << "=== Rectangle Drawing ===" << endl;
 cout << "Click two opposite corners to draw rectangle" << endl;
 cout << "Using Bresenham line algorithm for all sides" << endl;
 cout << "Space - Clear Screen" << endl;
 cout << "Q - Quit" << endl;

 glutMainLoop(); // <-- HERE
 return 0;
}