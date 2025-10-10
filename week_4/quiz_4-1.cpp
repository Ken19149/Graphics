#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
void drawCoordinateSystem()
{
    // Draw coordinate axes
    glBegin(GL_LINES);
    // X-axis (red)
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    // Y-axis (green)
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();
}

void drawOriginalLine(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    // Our original line (yellow)
    glBegin(GL_LINES);
    glColor3f(r, g, b);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawCoordinateSystem();
    drawOriginalLine(-0.5, 0.2, 1.5, 0.7, 1.0, 1.0, 1.0); // white line
    drawOriginalLine(-1.5, -0.2, 0.5, -0.7, 0.0, 0.0, 1.0); // blue line
    drawOriginalLine(-1.5, 1.5, 0.2, -0.4, 0.0, 1.0, 1.0); // cyan line
    drawOriginalLine(-0.3, 0.3, 2.5, -2.4, 1.0, 0.0, 1.0); // magenta line
    drawOriginalLine(-3.0, -0.4, 2.5, -0.4, 0.5, 0.5, 0.5); // gray line
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    printf("Viewport created: %d x %d pixels\n", w, h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // World window definition
    // gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    gluOrtho2D(-2.0, 2.0, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

void printTransformationInfo()
{
    printf("\n=== WORLD TO VIEWPORT TRANSFORMATION ===\n");
    printf("World Window: [%.1f, %.1f] x [%.1f, %.1f]\n", -1.0, 1.0, -1.0, 1.0);
    printf("Line Coordinates (World Space):\n");
    
    printf("\nWhite Line\n");
    printf(" Start: (%.1f, %.1f)\n", -0.5, 0.2);
    printf(" End: (%.1f, %.1f)\n", 1.5, 0.7);
    
    printf("\nBlue Line\n");
    printf(" Start: (%.1f, %.1f)\n", -1.5, -0.2);
    printf(" End: (%.1f, %.1f)\n", 0.5, -0.7);
    
    printf("\nCyan Line\n");
    printf(" Start: (%.1f, %.1f)\n", -1.5, 1.5);
    printf(" End: (%.1f, %.1f)\n", 0.2, -0.4);
    
    printf("\nMagenta Line\n");
    printf(" Start: (%.1f, %.1f)\n", -0.3, 0.3);
    printf(" End: (%.1f, %.1f)\n", 2.5, -2.4);
    
    printf("\nGray Line\n");
    printf(" Start: (%.1f, %.1f)\n", -3.0, -0.4);
    printf(" End: (%.1f, %.1f)\n", 2.5, -0.4);
    
    printf("\n=== CLIPPING ANALYSIS ===\n");
    printf("Clipping Window: [%.1f, %.1f] x [%.1f, %.1f]\n", -1.0, 1.0, -1.0, 1.0);
    printf("Line Status: COMPLETELY INSIDE - No clipping needed\n");
    printf("Both endpoints are within clipping boundaries\n");
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(300, 800); // w and h
    glutCreateWindow("World to Viewport & Line Clipping Demo");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glLineWidth(2.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    printTransformationInfo();
    glutMainLoop();
    return 0;
}