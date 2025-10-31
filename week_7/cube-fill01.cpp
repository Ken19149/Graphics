#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set camera position
    gluLookAt(3.0, 3.0, 3.0,  // Eye position
              0.0, 0.0, 0.0,  // Look at point
              0.0, 1.0, 0.0); // Up vector
    
    // Draw a red solid cube in the center
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glutSolidCube(1.0);
    
    // Draw additional colored cubes around the center
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    glutSolidCube(0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta color
    glutSolidCube(0.5);
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 20.0); // Increased far plane
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("GLUT Solid Colored Cubes");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    // Enable smooth shading
    glShadeModel(GL_SMOOTH);
    
    // Enable lighting for better 3D effect (optional)
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Set light properties
    GLfloat lightPos[] = {5.0f, 5.0f, 5.0f, 1.0f};
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    
    // Enable color material so colors work with lighting
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    printf("Solid Colored Cubes using glutSolidCube\n");
    printf("Press ESC to exit\n");
    
    glutMainLoop();
    return 0;
}