#include <OpenGL/gl.h>
#include <GLUT/glut.h>
void display() {
glClear(GL_COLOR_BUFFER_BIT);
// Draw a red line from (0.1, 0.1) to (0.9, 0.9)
glBegin(GL_LINES);
glColor3f(1.0, 0.0, 0.0); // Red
glVertex2f(0.1, 0.1); // Start point
glVertex2f(0.9, 0.9); // End point
glEnd();
glFlush();
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutCreateWindow("OpenGL Line");
glutDisplayFunc(display);
glutMainLoop();
return 0;
}