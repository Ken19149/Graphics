#include <GL/glut.h>
#include <iostream>

int height, width;

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
        std::cout << x1 << " " << y1 << std::endl;
        if ((x1 == x2) && (y1 == y2)) return;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw a red line from (0.1, 0.1) to (0.9, 0.9)
    /*
    glBegin(GL_LINES);
    glColor3f(0, 1, 1);
    glVertex2i(1, 1); // Start point
    glVertex2i(0, -1); // End point
    glEnd();
    */
    drawLine(10,10,100,200);
    glBegin(GL_POINTS); // Start drawing points
    glColor3f(0, 1, 1);
        // glVertex2f(-0.5f, 0.5f); // Define a point
        // glVertex2f(0.0f, 0.0f);   // Define another point
        // glVertex2f(0.5f, -0.5f);  // Define a third point
    glVertex2i(0, 0);
    glVertex2i(1, 1);
    glVertex2i(10, 10);
    glVertex2i(25,25);
    glEnd();
    glFlush();
}
int main(int argc, char** argv) {
    height = 600;
    width = 800;
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutCreateWindow("OpenGL Line");
    glutDisplayFunc(display);
    gluOrtho2D(0, width, 0, height);
    glutMainLoop();
    return 0;
}