// #include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef APPLE
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // gluLookAt Parameters Explained:
    // gluLookAt(eyeX, eyeY, eyeZ,    - Camera position in world space
    //           centerX, centerY, centerZ,  - Point camera is looking at
    //           upX, upY, upZ)       - Up direction vector

    gluLookAt(3.0, 3.0, 3.0,  // Eye position - where the camera is
              0.0, 0.0, 0.0,  // Look at point - what the camera is looking at
              0.0, 1.0, 0.0); // Up vector - which way is "up"

    // Draw the main cube
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(1.0);

    // Draw coordinate axes to understand the space
    glBegin(GL_LINES);

    // X-axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-2.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 0.0f, 0.0f);

    // Y-axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -2.0f, 0.0f);
    glVertex3f(0.0f, 2.0f, 0.0f);

    // Z-axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -2.0f);
    glVertex3f(0.0f, 0.0f, 2.0f);

    glEnd();

    // Draw the camera position and look-at point for visualization
    glPointSize(8.0f);
    glBegin(GL_POINTS);

    // Camera position (Yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(3.0f, 3.0f, 3.0f);

    // Look-at point (Cyan)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glEnd();

    // Draw a line from camera to look-at point
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(3.0f, 3.0f, 3.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC key
        exit(0);
        break;
    }
}

void printExplanation()
{
    printf("\n=== gluLookAt Explanation ===\n");
    printf("gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);\n\n");
    printf("Eye Position (3.0, 3.0, 3.0):\n");
    printf("  - The camera is located at coordinates (3, 3, 3)\n");
    printf("  - This is 3 units right, 3 units up, and 3 units forward from origin\n\n");

    printf("Look At Point (0.0, 0.0, 0.0):\n");
    printf("  - The camera is pointing towards the origin (0, 0, 0)\n");
    printf("  - The cube is drawn at the origin\n\n");

    printf("Up Vector (0.0, 1.0, 0.0):\n");
    printf("  - Defines which direction is 'up' for the camera\n");
    printf("  - (0,1,0) means the positive Y-axis is up\n");
    printf("  - If this was (1,0,0), the camera would be rotated 90 degrees\n\n");

    printf("Visualization in the window:\n");
    printf("  - White wireframe: The cube at origin\n");
    printf("  - Red line: X-axis, Green line: Y-axis, Blue line: Z-axis\n");
    printf("  - Yellow point: Camera position at (3,3,3)\n");
    printf("  - Cyan point: Look-at point at origin (0,0,0)\n");
    printf("  - Yellow line: Camera's line of sight\n");
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Understanding gluLookAt");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    printExplanation();

    glutMainLoop();
    return 0;
}