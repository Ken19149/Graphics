// circle viewport transformation

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
void drawCircleLine()
{
    int segments = 36; // You can adjust this number
    float radius = 0.7f;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawCircleLine();

    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 0.51, -1.7, 22.0);   // high (|n| > 1): squish right, squish left, squish up, squish down
                                        // low (0 < |n| < 1): 
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Simple Circle Line");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glLineWidth(3.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    printf("Simple circle line drawn using GL_LINE_LOOP\n");

    glutMainLoop();
    return 0;
}