// rainbow cube

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set camera position
    gluLookAt(3.0, 4.0, 2.0,  // Eye position
              0.0, 0.0, 0.0,  // Look at point
              0.0, 0.0, 1.0); // Up vector


    // try drawing gradient lines to create cube
    // B -> RGB | W -> CMY | R -> MY | G -> CY | B -> CM
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // black
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);     // red
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // black
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);     // green
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);    // black
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);     // blue
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);       // white
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);      // cyan
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);       // white
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);      // magenta
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);       // white
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);      // yellow
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);     // red
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);      // magenta
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);     // red
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);      // yellow
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);     // green
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);      // cyan

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);     // green
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);      // yellow
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);     // blue
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);      // cyan
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);     // blue
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);      // magenta
    glEnd();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // gluPerspective Parameters Explained:
    // gluPerspective(45.0,           - Field of view angle in degrees (vertical)
    //                (double)w/(double)h, - Aspect ratio (width/height)
    //                1.0,            - Near clipping plane
    //                10.0);          - Far clipping plane
    
    gluPerspective(45.0, (double)w / (double)h, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    
}  


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Understanding gluPerspective");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2.0f);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}