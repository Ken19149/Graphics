#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set camera position
    gluLookAt(0.0, 0.0, 5.0,  // Eye position
              0.0, 0.0, 0.0,  // Look at point
              0.0, 1.0, 0.0); // Up vector
    

    // glutWireCube(1.0);
    glutWireSphere(1.0, 20, 20);
    // glutWireCone(1.0, 2.0, 20, 20);
    // glutWireTorus(0.5, 1.0, 20, 20);
    // glutWireTeapot(1.0);

    // Draw coordinate axes
    glBegin(GL_LINES);
    // X-axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-3.0f, 0.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, 0.0f);
    // Y-axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -3.0f, 0.0f);
    glVertex3f(0.0f, 3.0f, 0.0f);
    // Z-axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -8.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
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
    
    gluPerspective(30.0, (double)w / (double)h, 1.0, 1000.0);
    
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    static float fov = 30.0f;
    static float nearr = 1.0f;
    static float farr = 1000.0f;
     
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
        case 'w': case 'W': // Increase FOV - w
            fov += 5.0f;
            if (fov > 120.0f) fov = 120.0f;
            break;
        case 's': case 'S': // Decrease FOV - s
            fov -= 5.0f;
            if (fov < 10.0f) fov = 10.0f;
            break;
        case 'a': case 'A': // Move nearr plane closer - a
            nearr -= 0.5f;
            if (nearr < 0.1f) nearr = 0.1f;
            break;
        case 'd': case 'D': // Move nearr plane farrther - d
            nearr += 0.5f;
            break;
        case 'q': case 'Q': // Decrease farr plane - q
            farr -= 1.0f;
            if (farr < nearr + 0.1f) farr = nearr + 0.1f;
            break;
        case 'e': case 'E': // Increase farr plane - e
            farr += 1.0f;
            break;
        case 'r': case 'R': // Reset - r
            fov = 45.0f;
            nearr = 1.0f;
            farr = 10.0f;
            break;
    }
    
    if (key == 'w' || key == 'W' || key == 's' || key == 'S' || 
        key == 'a' || key == 'A' || key == 'd' || key == 'D' ||
        key == 'q' || key == 'Q' || key == 'e' || key == 'E' ||
        key == 'r' || key == 'R') {
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, glutGet(GLUT_WINDOW_WIDTH)/(float)glutGet(GLUT_WINDOW_HEIGHT), nearr, farr);
        glMatrixMode(GL_MODELVIEW);
        
        printf("FOV: %.1f°, Near: %.1f, Far: %.1f\n", fov, nearr, farr);
        glutPostRedisplay();
    }
}

void printExplanation() {
    printf("\n=== gluPerspective Explanation ===\n");
    printf("gluPerspective(45.0, aspect, 1.0, 10.0);\n\n");
    
    printf("Field of View (45.0 degrees):\n");
    printf("  - Vertical viewing angle in degrees\n");
    printf("  - Smaller = zoomed in (telephoto lens)\n");
    printf("  - Larger = zoomed out (wide-angle lens)\n");
    printf("  - Human eye is about 45-60 degrees\n\n");
    
    printf("Aspect Ratio (width/height):\n");
    printf("  - Ratio of window width to height\n");
    printf("  - Prevents distortion when window is resized\n");
    printf("  - Square window = 1.0, Wide window > 1.0\n\n");
    
    printf("Near Clipping Plane (1.0):\n");
    printf("  - Objects closer than this are NOT visible\n");
    printf("  - Think of it as the closest focus distance\n");
    printf("  - Cannot be 0 or negative\n\n");
    
    printf("Far Clipping Plane (10.0):\n");
    printf("  - Objects farrther than this are NOT visible\n");
    printf("  - Think of it as the farrthest focus distance\n");
    printf("  - Should be larger than nearr plane\n\n");
    
    printf("Interactive Controls:\n");
    printf("  W/S: Increase/Decrease Field of View\n");
    printf("  A/D: Move Near plane closer/farrther\n");
    printf("  Q/E: Move Far plane closer/farrther\n");
    printf("  R: Reset to default values\n");
    printf("  ESC: Exit\n\n");
    
    printf("Current: FOV=30.0°, Near=1.0, Far=1000.0\n");
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
    glutKeyboardFunc(keyboard);
    
    printExplanation();
    
    glutMainLoop();
    return 0;
}