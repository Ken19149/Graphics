#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
/*
void drawDot(int x, int y, double r, double g, double b) {
    // TODO: Implement dot drawing using OpenGL
    // Hint: Use glBegin(GL_POINTS), glColor3f(), glVertex2i(), glEnd()
    glBegin(GL_POINT);
    glColor3f(r, g, b);
    glVertex2i(x, y);
    glEnd();
}
*/
void drawDot(int x, int y) {
    // TODO: Implement dot drawing using OpenGL
    // Hint: Use glBegin(GL_POINTS), glColor3f(), glVertex2i(), glEnd()
    std::cout << std::to_string(x) << " " << std::to_string(y) << std::endl;
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int n = abs(dx) >= abs(dy) ? dx : dy;

    for (int i=0; i<=n; i++) {
        std::cout << std::to_string(x1) << " " << std::to_string(y1) << std::endl;
        if ((x1 == x2) && (y1 == y2)) return;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}
int main() {
    drawLine(0,100,100,500);
    return 0;
}
