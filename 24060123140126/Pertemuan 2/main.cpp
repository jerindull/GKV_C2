#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
     
    glColor3f(0.2f, 0.5f, 0.8f);
    
    float size = 0.15f;
    float offset = 0.05f;
    
    for (int i = 0; i < 3; i++) {
        float x = -0.2f + (size + offset) * i;
        float y = 0.2f;
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
        glEnd();
    }
    
    for (int i = 0; i < 2; i++) {
        float x = 0.0f;
        float y = -0.05f - (size + offset) * i;
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
        glEnd();
    }
    
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
    glutCreateWindow("Huruf T");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

