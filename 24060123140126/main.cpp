#include <GL/glut.h>
#include <cmath>

// Variabel global untuk contoh rotasi (opsional, misalnya roda berputar).
float angle = 0.0f;

// Inisialisasi tampilan dan proyeksi 2D
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Latar belakang putih
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Membuat proyeksi orthographic (koordinat -50 s/d 50)
    gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
}

// Fungsi untuk menggambar lingkaran (roda, matahari, dll)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for(int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Fungsi untuk menggambar mobil
void drawCar() {
    glPushMatrix();
        // Translasi posisi mobil ke tengah antara garis hijau dan biru (ban di y=0)
        glTranslatef(-10.0f, 2.0f, 0.0f);

        // Bagian badan mobil (bawah)
        glColor3f(0.0f, 0.0f, 0.8f);  // Warna biru
        glBegin(GL_QUADS);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(25.0f, 0.0f);
            glVertex2f(25.0f, 5.0f);
            glVertex2f(0.0f, 5.0f);
        glEnd();

        // Bagian atap mobil (atas)
        glColor3f(0.0f, 0.0f, 0.8f);
        glBegin(GL_QUADS);
            glVertex2f(3.0f, 5.0f);
            glVertex2f(18.0f, 5.0f);
            glVertex2f(18.0f, 10.0f);
            glVertex2f(5.0f, 10.0f);
        glEnd();

        // Jendela mobil
        glColor3f(0.9f, 0.9f, 0.9f);  // Warna abu-abu terang
        glBegin(GL_QUADS);
            glVertex2f(6.0f, 6.0f);
            glVertex2f(16.0f, 6.0f);
            glVertex2f(16.0f, 9.0f);
            glVertex2f(6.0f, 9.0f);
        glEnd();

        // Lampu depan mobil (headlight)
        glColor3f(1.0f, 1.0f, 0.0f);  // Kuning
        glBegin(GL_QUADS);
            glVertex2f(24.0f, 1.0f);
            glVertex2f(25.0f, 1.0f);
            glVertex2f(25.0f, 2.0f);
            glVertex2f(24.0f, 2.0f);
        glEnd();

        // Roda depan
        glPushMatrix();
            glTranslatef(6.0f, -2.0f, 0.0f);
            glColor3f(0.0f, 0.0f, 0.0f); // Hitam (ban)
            drawCircle(0.0f, 0.0f, 2.0f, 50);
            glColor3f(1.0f, 1.0f, 1.0f); // Putih (velg)
            drawCircle(0.0f, 0.0f, 1.0f, 50);
        glPopMatrix();

        // Roda belakang
        glPushMatrix();
            glTranslatef(18.0f, -2.0f, 0.0f);
            glColor3f(0.0f, 0.0f, 0.0f);
            drawCircle(0.0f, 0.0f, 2.0f, 50);
            glColor3f(1.0f, 1.0f, 1.0f);
            drawCircle(0.0f, 0.0f, 1.0f, 50);
        glPopMatrix();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Latar langit
    glColor3f(0.53f, 0.81f, 0.92f); // Sky Blue
    glBegin(GL_QUADS);
        glVertex2f(-50.0f, 50.0f);
        glVertex2f( 50.0f, 50.0f);
        glVertex2f( 50.0f,  0.0f);
        glVertex2f(-50.0f,  0.0f);
    glEnd();

    // Latar rumput
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-50.0f,  0.0f);
        glVertex2f( 50.0f,  0.0f);
        glVertex2f( 50.0f, -50.0f);
        glVertex2f(-50.0f, -50.0f);
    glEnd();

    // Matahari dipindahkan ke posisi baru
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(-35.0f, 35.0f, 5.0f, 50);

    // Gambar Mobil
    drawCar();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Car Scene - Blue Car");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

