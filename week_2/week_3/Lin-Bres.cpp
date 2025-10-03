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
vector<pair<int, int>> lines; // Store pairs of points for lines
void drawDot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

/* // template
void drawLineBresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    // variables, what are they?   // <-- HERE


    int n = dy > dx ? dy : dx;      // it doesn't stop on loop so i use longer end instead

    for (int i=0;i<n;i++)
    {
        drawDot(x1, y1);
    

        if (x1 == x2 && y1 == y2) break;

        int pk = 2*dy - dx;

        std::cout << x1 << " " << y1 << " " << pk << std::endl;

        if (pk < 0)
        {
            // do something                 // <-- HERE
            pk = pk + 2*dy;
            x1++;
        }
        if (pk >= 0)
        {
            // do something                 // <-- HERE
            pk = pk + 2*dy - 2*dx;
            x1++;
            y1++;
        }
    }
}
*/

// my function
void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int n = dy > dx ? dy : dx;

    for (int i=0;i<n;i++) {
        drawDot(x1, y1);
        int e2 = 2*err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
        // std::cout << x1 << " " << y1 << std::endl;
    }

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // <-- HERE

    // Draw all lines using Bresenham algorithm
    for (size_t i = 0; i + 1 < lines.size(); i += 2)
    {
        drawLineBresenham(lines[i].first, lines[i].second,
                          lines[i + 1].first, lines[i + 1].second);
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    y = screenHeight - y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        lines.push_back({x, y});
        cout << "Point at (" << x << ", " << y << ")" << endl;

        if (lines.size() % 2 == 0)
        {
            cout << "Line drawn using Bresenham algorithm" << endl;
        }
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        lines.clear();  // <== ERROR: change from circles.clear() to lines.clear()
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
    glClearColor(0.0, 0.0, 0.0, 1.0); // <-- HERE
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glPointSize(2.0); // <-- HERE
}

int main(int argc, char** argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize(screenWidth, screenHeight);
 glutInitWindowPosition(100, 100);  // <-- HERE
 glutCreateWindow("Midpoint Circle Algorithm");

 init();
 glutDisplayFunc(display);
 glutMouseFunc(mouse);
 glutKeyboardFunc(keyboard);

 cout << "=== Bresenham Line Algorithm ===" << endl;
 cout << "Click two points to draw a line" << endl;
 cout << "Space - Clear Screen" << endl;
 cout << "Q - Quit" << endl;

 glutMainLoop();
 return 0;
}