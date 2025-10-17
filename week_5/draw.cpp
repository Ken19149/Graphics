#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
void drawLine()
{
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.0f); // Start point
    glVertex2f(0.5f, 0.0f);  // End point
    glEnd();
}

void drawCircleLine()
{
    int segments = 3;   // Number of triangle segments
    float radius = 0.5f; // Circle radius
    float angle;

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i <= segments; i++)
    {
        angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // drawLine();

    drawCircleLine();

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