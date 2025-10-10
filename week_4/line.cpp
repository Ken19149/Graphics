#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
void drawLine()
{
    glBegin(GL_LINES);
    glVertex2f(-1.5f, 1.0f); // Start point
    glVertex2f(2.5f, -3.0f);  // End point
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawLine();
    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple Line");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glLineWidth(3.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    printf("Simple line drawn using GL_LINES\n");
    glutMainLoop();
    return 0;
}