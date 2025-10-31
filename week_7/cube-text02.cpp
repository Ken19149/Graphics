#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

GLuint textureID;

GLuint loadTexture(const char* filename) {
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb);
    
    if (!image) {
        printf("Error: Could not load texture file: %s\n", filename);
        printf("Make sure the file exists in the current directory\n");
        return 0;
    }
    
    printf("Successfully loaded texture: %s (%dx%d, %d channels)\n", filename, width, height, channels);
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_image_free(image);
    return texture;
}

// Function to draw a textured cube manually
void drawTexturedCube(GLuint textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glBegin(GL_QUADS);
    
    /*
    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    */

    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(3.0f, 3.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 3.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    
    // Back face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    
    // Top face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    
    // Bottom face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    
    // Left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set camera position
    gluLookAt(3.0, 3.0, 3.0,  // Eye position
              0.0, 0.0, 0.0,  // Look at point
              0.0, 1.0, 0.0); // Up vector
    
    // Draw textured cube in the center
    glEnable(GL_TEXTURE_2D);
    drawTexturedCube(loadTexture("C:\\Users\\Student\\Ken 6681371\\Graphics\\week_7\\textures\\hello_adjust.jpg")); // center
    // drawTexturedCube();
    glDisable(GL_TEXTURE_2D);
    
    // Draw additional colored cubes around the center
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    // glColor3f(0.0f, 1.0f, 0.0f); // Green color
    // glutSolidCube(0.5);
    drawTexturedCube(loadTexture("C:\\Users\\Student\\Ken 6681371\\Graphics\\week_7\\textures\\ken_adjust.jpg")); // near
    // drawTexturedCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawTexturedCube(loadTexture("C:\\Users\\Student\\Ken 6681371\\Graphics\\week_7\\textures\\pattern.jpg")); // back
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    drawTexturedCube(loadTexture("C:\\Users\\Student\\Ken 6681371\\Graphics\\week_7\\textures\\top.jpg")); // top
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    drawTexturedCube(loadTexture("C:\\Users\\Student\\Ken 6681371\\Graphics\\week_7\\textures\\creeper.jpg")); // bottom
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
    }
}

void init() {
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
    
    // Load texture from file
    printf("Loading texture.jpg...\n");
    textureID = loadTexture("C:\\Users\\Student\\Ken 6681371\\Graphics\\week_7\\textures\\hello_adjust.jpg");
    // textureID = loadTexture(".\\week_7\\textures\\texture.jpg");
    
    if (textureID == 0) {
        printf("Creating fallback texture instead...\n");
        // Create a simple fallback texture
        const int texSize = 64;
        GLubyte texture[texSize][texSize][3];
        for (int i = 0; i < texSize; i++) {
            for (int j = 0; j < texSize; j++) {
                texture[i][j][0] = (i * 4) % 256;  // Red gradient
                texture[i][j][1] = (j * 4) % 256;  // Green gradient  
                texture[i][j][2] = 128;             // Blue constant
            }
        }
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texSize, texSize, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("GLUT Textured Cube with texture.jpg");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    printf("\n=== Texture Loading Info ===\n");
    printf("Looking for: texture.jpg\n");
    printf("Current directory contents should include:\n");
    system("ls -la *.jpg *.jpeg *.png 2>/dev/null || echo 'No image files found in current directory'");
    printf("============================\n\n");
    
    glutMainLoop();
    
    return 0;
}