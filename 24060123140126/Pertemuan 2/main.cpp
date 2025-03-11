#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
     
    glColor3f(0.2f, 0.5f, 0.8f);
    
    float size = 0.15f;
    float offset = 0.05f;
    
    for (int i = 0; i < 3; i++) {
        float x = -0.25f + (size + offset) * i;
        glBegin(GL_QUADS);
        glVertex2f(x, -0.3f);
        glVertex2f(x + size, -0.3f);
        glVertex2f(x + size, -0.3f + size);
        glVertex2f(x, -0.3f + size);
        glEnd();
    }
    
    for (int i = 0; i < 2; i++) {
        float x = -0.175f + (size + offset) * i;
        glBegin(GL_QUADS);
        glVertex2f(x, -0.1f);
        glVertex2f(x + size, -0.1f);
        glVertex2f(x + size, -0.1f + size);
        glVertex2f(x, -0.1f + size);
        glEnd();
    }
    
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(-0.1f + size, 0.1f);
    glVertex2f(-0.1f + size, 0.1f + size);
    glVertex2f(-0.1f, 0.1f + size);
    glEnd();
    
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.5, 0.5, -0.5, 0.5);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Kubus Bertingkat");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

