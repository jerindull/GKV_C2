#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

// Fungsi pembantu untuk menggambar sebuah cuboid (balok)
void drawCuboid(float length, float height, float width, float r, float g, float b)
{
    glColor3f(r, g, b);
    glPushMatrix();
        glScalef(length, height, width);
        glutSolidCube(1.0f);
    glPopMatrix();
}

// Fungsi untuk menggambar sebuah roda menggunakan torus
void drawWheel(float xOff, float yOff, float zOff, float wheelRadius, float wheelThickness)
{
    glPushMatrix();
        glTranslatef(xOff, yOff, zOff);
        // Rotasi 90 derajat agar torus berdiri tegak (sesuai dengan orientasi roda)
        glRotatef(90, 0, 1, 0);
        glColor3f(0.0f, 0.0f, 0.0f); // warna hitam untuk ban
        glutSolidTorus(wheelThickness, wheelRadius, 12, 12);
    glPopMatrix();
}

// Variabel global untuk posisi dan orientasi mobil
float carPosX = 0.0f, carPosZ = 0.0f;
float carAngle = 0.0f;  // sudut rotasi mobil (dalam derajat)

// Fungsi untuk menggambar mobil 3D
void drawCar()
{
    glPushMatrix();
        // Pindahkan dan rotasi mobil sesuai variabel global
        glTranslatef(carPosX, 0.0f, carPosZ);
        glRotatef(carAngle, 0.0f, 1.0f, 0.0f);

        // 1. Badan mobil (bagian bawah) berwarna biru
        drawCuboid(4.0f, 0.5f, 2.0f, 0.0f, 0.0f, 0.8f);

        // 2. Atap mobil (bagian kabin)
        glPushMatrix();
            glTranslatef(0.0f, 0.5f, 0.0f);
            drawCuboid(2.5f, 0.5f, 1.8f, 0.0f, 0.0f, 0.8f);
        glPopMatrix();

       // 3. Jendela mobil menggunakan blending (transparansi)
glPushMatrix();
    // Turunkan posisi jendela secara keseluruhan agar lebih mendekati badan mobil
    glTranslatef(0.0f, 0.4f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Warna kaca: biru muda dengan transparansi
    glColor4f(0.8f, 0.9f, 1.0f, 0.5f);

    // Jendela depan (kaca depan) diperbaiki agar lebih presisi
    glPushMatrix();
        // Geser kaca depan ke depan dan lebih rendah
        glTranslatef(0.9f, 0.1f, 0.0f);
        // Skala: sangat tipis di sumbu x, tinggi dan lebar disesuaikan
        glScalef(0.01f, 0.3f, 1.4f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Jendela samping kiri
    glPushMatrix();
        // Geser ke sisi kiri dan sesuaikan posisi vertikal agar sejajar
        glTranslatef(0.0f, 0.1f, 1.0f);
        glScalef(1.8f, 0.3f, 0.01f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Jendela samping kanan
    glPushMatrix();
        // Geser ke sisi kanan
        glTranslatef(0.0f, 0.1f, -1.0f);
        glScalef(1.8f, 0.3f, 0.01f);
        glutSolidCube(1.0f);
    glPopMatrix();

    glDisable(GL_BLEND);
glPopMatrix();



        // 4. Lampu depan mobil (headlight) berwarna kuning
        glPushMatrix();
            glTranslatef(2.0f, 0.0f, 0.8f);
            drawCuboid(0.2f, 0.2f, 0.2f, 1.0f, 1.0f, 0.0f);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(2.0f, 0.0f, -0.8f);
            drawCuboid(0.2f, 0.2f, 0.2f, 1.0f, 1.0f, 0.0f);
        glPopMatrix();

        // 5. Roda mobil
        float wheelRadius = 0.4f;
        float wheelThickness = 0.1f;
        // Roda depan kanan
        drawWheel(1.5f, -0.3f, -1.0f, wheelRadius, wheelThickness);
        // Roda depan kiri
        drawWheel(1.5f, -0.3f, 1.0f, wheelRadius, wheelThickness);
        // Roda belakang kanan
        drawWheel(-1.5f, -0.3f, -1.0f, wheelRadius, wheelThickness);
        // Roda belakang kiri
        drawWheel(-1.5f, -0.3f, 1.0f, wheelRadius, wheelThickness);
    glPopMatrix();
}

// Inisialisasi pencahayaan dan depth testing
void initLightingAndDepth()
{
    // Latar belakang: langit biru
    glClearColor(0.5, 0.8, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Atur properti lampu
    GLfloat lightPos[]      = { 4.0f, 5.0f, 6.0f, 1.0f };
    GLfloat ambientLight[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat diffuseLight[]  = { 0.9f, 0.9f, 0.9f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

    // Izinkan penggunaan warna untuk material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Pastikan vektor normal selalu ternormalisasi
    glEnable(GL_NORMALIZE);
}

// Fungsi display: menggambar adegan
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Atur kamera: posisi, titik yang dilihat, dan arah atas
    gluLookAt(7.0, 4.0, 10.0,   // posisi kamera
              0.0, 0.0, 0.0,    // titik yang dilihat
              0.0, 1.0, 0.0);   // arah atas

    // Gambar tanah (sebagai alas hijau)
    glPushMatrix();
        glColor3f(0.3f, 0.7f, 0.3f);
        glTranslatef(0.0f, -0.5f, 0.0f);
        glScalef(20.0f, 0.01f, 20.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Gambar mobil
    drawCar();

    glutSwapBuffers();
}

// Fungsi reshape untuk menangani perubahan ukuran jendela
void reshape(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 1.0, 100.0);
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Callback untuk menangani input tombol panah (memutar mobil)
void specialKeys(int key, int x, int y)
{
    float turnSpeed = 5.0f; // kecepatan rotasi (dalam derajat)
    switch (key)
    {
        case GLUT_KEY_LEFT:
            carAngle += turnSpeed;
            break;
        case GLUT_KEY_RIGHT:
            carAngle -= turnSpeed;
            break;
    }
    glutPostRedisplay();
}

// Fungsi utama
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Blue Car");

    initLightingAndDepth();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);  // Callback untuk tombol panah

    glutMainLoop();
    return 0;
}
