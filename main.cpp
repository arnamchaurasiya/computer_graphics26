#include <GL/glut.h>
#include <cmath>
#include "stb_image.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

GLuint soldierTexture1, soldierTexture2, soldierTexture3, soldierTexture4;

float cloudOffset1 = 0, cloudOffset2 = 0, cloudOffset3 = 0;

float bullet1X = 300, bullet1Y = 280;
float bullet2X = 210, bullet2Y = 170;
float bullet3X = 550, bullet3Y = 205;

bool isFiring1 = false, isFiring2 = false, isFiring3 = false;

void playGunshotSound() {
    PlaySound(TEXT("gunshot.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void drawCircle(float cx, float cy, float r) {
    int num_segments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float angle = 2.0f * 3.1415926f * i / num_segments;
        glVertex2f(cx + r * cosf(angle), cy + r * sinf(angle));
    }
    glEnd();
}

void drawCloud1(float x) {
    glColor3f(1, 1, 1);
    drawCircle(x, 640, 15);
    drawCircle(x + 8, 645, 15);
    drawCircle(x + 15, 640, 15);
    drawCircle(x + 30, 638, 15);
}

void drawCloud2(float x) {
    glColor3f(1, 1, 1);
    drawCircle(x, 660, 15);
    drawCircle(x + 8, 665, 15);
    drawCircle(x + 15, 660, 15);
    drawCircle(x + 30, 658, 15);
}

void drawCloud3(float x) {
    glColor3f(1, 1, 1);
    drawCircle(x, 680, 15);
    drawCircle(x + 8, 685, 15);
    drawCircle(x + 15, 680, 15);
}

void drawBullet(float x, float y) {
    glColor3f(0.898f, 0.663f, 0.329f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 10, y + 3);
    glVertex2f(x, y + 3);
    glEnd();
}

void update(int value) {
    cloudOffset1 += 0.5f;
    cloudOffset2 += 0.3f;
    cloudOffset3 += 0.4f;

    if (isFiring1) {
        bullet1X += 6.0f;
        if (bullet1X > 1000) {
            isFiring1 = false;
        }
    }

    if (isFiring2) {
        bullet2X += 6.0f;
        if (bullet2X > 1000) {
            isFiring2 = false;
        }
    }

    if (isFiring3) {
        bullet3X += 5.0f;
        if (bullet3X > 1000) {
            isFiring3 = false;
        }
    }

    if (cloudOffset1 > 1200) cloudOffset1 = -300;
    if (cloudOffset2 > 1200) cloudOffset2 = -300;
    if (cloudOffset3 > 1200) cloudOffset3 = -300;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void drawPolygon(float vertices[][2], int count, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < count; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

void drawMountain1() {
    float mountain[6][2] = {
        {0, 400}, {0, 500}, {150, 620},
        {350, 450}, {300, 400}, {0, 400}
    };
    drawPolygon(mountain, 6, 0.408f, 0.431f, 0.235f);
}

void drawMountains() {
    float baseY = 400;
    float x = 300;
    float width = 300;
    float height = 180;

    for (int i = 0; i < 7; i++) {
        float peakX = x + width / 2;
        float peakY = baseY + height;

        float mountain[4][2] = {
            {x, baseY},
            {peakX, peakY},
            {x + width, baseY},
            {x, baseY}
        };

        drawPolygon(mountain, 4, 0.408f, 0.431f, 0.235f);

        x += width * 0.6f;
        width *= 0.9f;
        height *= 0.7f;
    }
}

void drawGround() {
    float ground[][2] = { {0, 0}, {1000, 0}, {1000, 400}, {0, 400} };
    drawPolygon(ground, 4, 0.518f, 0.518f, 0.298f);
}


void drawBunker() {
    glPushMatrix();  // Save current transformation matrix

    // ===== Modify these values to reposition and scale the bunker =====
    float bunkerOffsetX = 200.0f;  // Move horizontally
    float bunkerOffsetY = 20.0f;  // Move vertically
    float scale = 0.7f;           // Resize the whole bunker
    // ==================================================================

    // Apply translation and scaling around the base of the bunker
    glTranslatef(bunkerOffsetX, bunkerOffsetY, 0);  // Move bunker to new position
    glTranslatef(450, 250, 0);                      // Move origin to base
    glScalef(scale, scale, 1);                      // Scale
    glTranslatef(-450, -250, 0);                    // Move origin back

    float leftSide[][2] = { {450, 250}, {430, 350}, {620, 350}, {600, 250} };
    drawPolygon(leftSide, 4, 0.204f, 0.267f, 0.165f);

    float rightSide[][2] = { {600, 250}, {620, 350}, {820, 350}, {800, 250} };
    drawPolygon(rightSide, 4, 0.110f, 0.220f, 0.145f);

    float roof[][2] = { {430, 350}, {620, 450}, {820, 350}, {620, 350} };
    drawPolygon(roof, 4, 0.188f, 0.251f, 0.141f);

    float door[][2] = { {470, 250}, {470, 320}, {530, 320}, {530, 250} };
    drawPolygon(door, 4, 0.078f, 0.118f, 0.078f);

    float leftWindow[][2] = { {550, 300}, {550, 320}, {570, 320}, {570, 300} };
    drawPolygon(leftWindow, 4, 0.071f, 0.090f, 0.071f);

    float rightWindow1[][2] = { {650, 300}, {650, 320}, {680, 320}, {680, 300} };
    drawPolygon(rightWindow1, 4, 0.071f, 0.090f, 0.071f);

    float rightWindow2[][2] = { {700, 300}, {700, 320}, {730, 320}, {730, 300} };
    drawPolygon(rightWindow2, 4, 0.071f, 0.090f, 0.071f);

    glPopMatrix();  // Restore original transformation
}
void drawBunker2() {
    glPushMatrix();  // Save current transformation matrix

    // ==== Change these to reposition/scale the second bunker ====
    float bunkerOffsetX = -350.0f;  // Horizontal offset (change as needed)
    float bunkerOffsetY = 100.0f;   // Vertical offset (change as needed)
    float scale = 0.6f;            // Resize second bunker
    // ============================================================

    // Apply translation and scaling around the base of the bunker
    glTranslatef(bunkerOffsetX, bunkerOffsetY, 0);  // Move bunker to new position
    glTranslatef(450, 250, 0);                      // Move origin to base
    glScalef(scale, scale, 1);                      // Scale
    glTranslatef(-450, -250, 0);                    // Move origin back

    float leftSide[][2] = { {450, 250}, {430, 350}, {620, 350}, {600, 250} };
    drawPolygon(leftSide, 4, 0.204f, 0.267f, 0.165f);

    float rightSide[][2] = { {600, 250}, {620, 350}, {820, 350}, {800, 250} };
    drawPolygon(rightSide, 4, 0.110f, 0.220f, 0.145f);

    float roof[][2] = { {430, 350}, {620, 450}, {820, 350}, {620, 350} };
    drawPolygon(roof, 4, 0.188f, 0.251f, 0.141f);

    float door[][2] = { {470, 250}, {470, 320}, {530, 320}, {530, 250} };
    drawPolygon(door, 4, 0.078f, 0.118f, 0.078f);

    float leftWindow[][2] = { {550, 300}, {550, 320}, {570, 320}, {570, 300} };
    drawPolygon(leftWindow, 4, 0.071f, 0.090f, 0.071f);

    float rightWindow1[][2] = { {650, 300}, {650, 320}, {680, 320}, {680, 300} };
    drawPolygon(rightWindow1, 4, 0.071f, 0.090f, 0.071f);

    float rightWindow2[][2] = { {700, 300}, {700, 320}, {730, 320}, {730, 300} };
    drawPolygon(rightWindow2, 4, 0.071f, 0.090f, 0.071f);

    glPopMatrix();  // Restore original transformation
}



void drawSoldierImage(GLuint texture, float x, float y, float width, float height) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(x, y);
    glTexCoord2f(1, 0); glVertex2f(x + width, y);
    glTexCoord2f(1, 1); glVertex2f(x + width, y + height);
    glTexCoord2f(0, 1); glVertex2f(x, y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGround();
    drawMountain1();
    drawMountains();
    drawBunker();
    drawBunker2();

    drawSoldierImage(soldierTexture1, 150, 150, 160, 200);
    drawSoldierImage(soldierTexture2, 50, 10, 210, 250);
    drawSoldierImage(soldierTexture3, 400, 70, 160, 200);
    drawSoldierImage(soldierTexture4, 750, 80, 160, 200);

    drawCloud1(40 + cloudOffset1);
    drawCloud2(300 + cloudOffset2);
    drawCloud3(700 - cloudOffset3);

    if (isFiring1) drawBullet(bullet1X, bullet1Y);
    if (isFiring2) drawBullet(bullet2X, bullet2Y);
    if (isFiring3) drawBullet(bullet3X, bullet3Y);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
    case 'Q':
        if (!isFiring1) {
            bullet1X = 310;
            isFiring1 = true;
            playGunshotSound();
        }
        break;
    case 'w':
    case 'W':
        if (!isFiring2) {
            bullet2X = 260;
            isFiring2 = true;
            playGunshotSound();
        }
        break;
    case 'e':
    case 'E':
        if (!isFiring3) {
            bullet3X = 550;
            isFiring3 = true;
            playGunshotSound();
        }
        break;
    case 27:
        exit(0);
    }
}

void init() {
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 700);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* image;

    image = stbi_load("solider1.png", &width, &height, &channels, STBI_rgb_alpha);
    if (image) {
        glGenTextures(1, &soldierTexture1);
        glBindTexture(GL_TEXTURE_2D, soldierTexture1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(image);
    }

    image = stbi_load("solider2.png", &width, &height, &channels, STBI_rgb_alpha);
    if (image) {
        glGenTextures(1, &soldierTexture2);
        glBindTexture(GL_TEXTURE_2D, soldierTexture2);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(image);
    }

    image = stbi_load("solider3.png", &width, &height, &channels, STBI_rgb_alpha);
    if (image) {
        glGenTextures(1, &soldierTexture3);
        glBindTexture(GL_TEXTURE_2D, soldierTexture3);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(image);
    }

    image = stbi_load("solider4.png", &width, &height, &channels, STBI_rgb_alpha);
    if (image) {
        glGenTextures(1, &soldierTexture4);
        glBindTexture(GL_TEXTURE_2D, soldierTexture4);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(image);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Soldier Bullet Animation");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
