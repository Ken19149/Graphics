#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

// GLuint textureID;

// Create a simple checkerboard texture programmatically
GLuint createCheckerboardTexture(int x)
{
    GLuint textureID;
    const int texSize = (int) pow(2, x);
    GLubyte texture[texSize][texSize][3];
    for (int i = 0; i < texSize; i++)
    {
        for (int j = 0; j < texSize; j++)
        {
            // Create checkerboard pattern
            int checkSize = 8;
            int pattern = ((i / checkSize) + (j / checkSize)) % 2;
            GLubyte color = pattern ? 255 : 128;  // White and gray
            texture[i][j][0] = color;             // Red
            texture[i][j][1] = color;             // Green
            texture[i][j][2] = pattern ? 255 : 0; // Blue (adds some color variation)
        }
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texSize, texSize, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return textureID;
}

// Function to draw a textured cube manually
void drawTexturedCube(int x)
{
    // glBindTexture(GL_TEXTURE_2D, textureID);
    glBindTexture(GL_TEXTURE_2D, createCheckerboardTexture(x));
    glBegin(GL_QUADS);
    // Front face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // Back face
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // Top face
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    // Bottom face
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    // Right face
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // Left face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Set camera position
    gluLookAt(3.0, 3.0, 3.0,  // Eye position
              0.0, 0.0, 0.0,  // Look at point
              0.0, 1.0, 0.0); // Up vector
    // Draw textured cube in the center
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawTexturedCube(4);
    glDisable(GL_TEXTURE_2D);

    // Draw additional colored cubes around the center
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glutSolidCube(0.5);
    drawTexturedCube(5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glutSolidCube(0.5);
    drawTexturedCube(6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    glutSolidCube(0.5);
    drawTexturedCube(7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta color
    drawTexturedCube(8);
    glutSolidCube(0.5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 20.0);
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

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Set light properties
    GLfloat lightPos[] = {5.0f, 5.0f, 5.0f, 1.0f};
    GLfloat lightAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    // Enable color material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // Create checkerboard texture
    // createCheckerboardTexture(6);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("GLUT Textured and Colored Cubes - Checkerboard Texture");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    printf("Textured Cube with Checkerboard Pattern\n");
    printf("Press ESC to exit\n");
    glutMainLoop();
    return 0;
}
