#include <GL/glut.h>
#include <math.h>

float angle = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0); glVertex2f(-0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0); glVertex2f( 0.5, -0.5);
        glColor3f(0.0, 0.0, 1.0); glVertex2f( 0.0,  0.5);
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void timer(int value) {
    angle += 2.0f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL Test");

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
