#include <GL/glut.h>

static int shoulder = 0, elbow = 0, hand = 0, finger1 = 0, finger2 = 0, finger3 = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Rotasi dan Translasi Bahu
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    // Gambar Lengan Atas
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Rotasi dan Translasi Siku
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    // Gambar Lengan Bawah
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Rotasi dan Translasi Telapak Tangan
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);

    // Gambar Telapak Tangan
    glPushMatrix();
    glScalef(1.0, 0.3, 0.6);
    glutWireCube(1.0);
    glPopMatrix();

    // Gambar Jari 1-3
    float finger_positions[3][3] = {{0.4, 0.2, 0.2}, {0.4, 0.2, 0.0}, {0.4, 0.2, -0.2}};
    int finger_angles[3] = {finger1, finger2, finger3};
    
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(finger_positions[i][0], finger_positions[i][1], finger_positions[i][2]);
        glRotatef((GLfloat)finger_angles[i], 1.0, 0.0, 0.0);
        glScalef(0.3, 0.1, 0.1);
        glutWireCube(1.0);
        glPopMatrix();
    }

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'h': hand = (hand + 5) % 360; break;
        case 'H': hand = (hand - 5) % 360; break;
        case '1': finger1 = (finger1 + 5) % 360; break;
        case '2': finger1 = (finger1 - 5) % 360; break;
        case '3': finger2 = (finger2 + 5) % 360; break;
        case '4': finger2 = (finger2 - 5) % 360; break;
        case '5': finger3 = (finger3 + 5) % 360; break;
        case '6': finger3 = (finger3 - 5) % 360; break;
        case 27: exit(0); break;
        default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lengan dengan Tiga Jari");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

