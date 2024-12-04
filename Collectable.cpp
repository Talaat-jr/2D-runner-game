#include "collectable.h"
#include "Color.h"

#include <cmath>
#include <iostream>
#include <glut.h>

double Collectable::COLLECTABLE_WIDTH = 30;
double Collectable::COLLECTABLE_HEIGHT = 30;
double scaleFactor = 1.0;
bool growing = true;


Collectable::Collectable(double x, double y, double* speed)
    : width(COLLECTABLE_WIDTH), height(COLLECTABLE_HEIGHT), BoundingBox(x,y, COLLECTABLE_WIDTH*2, COLLECTABLE_HEIGHT*2), x(x), y(y), speed(speed) {}

void Collectable::draw() {

    Color blue = Color(0.0f, 0.0f, 1.0f);
    glPushMatrix();

    glTranslatef(x, y, 0.0f);
	glScaled(scaleFactor, scaleFactor, 1.0f);

	drawCoin(x, y, width/2);

    glPopMatrix();

}

void Collectable::animate() {
    x -= *speed;
    /*if (width != COLLECTABLE_WIDTH) {
		width = COLLECTABLE_WIDTH;
    }
    else {
		width = COLLECTABLE_WIDTH*1.5;
    }*/

    if (growing) {
        scaleFactor += 0.01f; // Increase scale
        if (scaleFactor >= 1.5f) { // Maximum size
            growing = false; // Start shrinking
        }
    }
    else {
        scaleFactor -= 0.01f; // Decrease scale
        if (scaleFactor <= 0.5f) { // Minimum size
            growing = true; // Start growing again
        }
    }
    BoundingBox::x = x;
}

void Collectable::move(double dx, double dy) {
    x += dx;
    y += dy;
}

void Collectable::drawCoin(float x, float y, float radius) {
	double size = radius;
	Color gold = Color(1.0f, 0.84f, 0.0f);
	Color lightYellow = Color(1.0f, 1.0f, 0.6f);
	Color darkYellow = Color(0.8f, 0.7f, 0.0f);

    // 1. Coin Base (GL_TRIANGLE_FAN)
	gold.apply();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center of the coin
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.14159f / 20;
        glVertex2f(cos(angle) * size, sin(angle) * size);
    }
    glEnd();

    // 2. Inner Shine (GL_TRIANGLE_FAN)
    lightYellow.apply();
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f); // Center of the shine
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.14159f / 20;
        glVertex2f(cos(angle) * size * 0.6f, sin(angle) * size * 0.6f);
    }
    glEnd();

    // 3. Border or Engraving (GL_LINES)
	darkYellow.apply();
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 40; ++i) {
        float angle = i * 2.0f * 3.14159f / 40;
        glVertex2f(cos(angle) * size * 0.9f, sin(angle) * size * 0.9f);
    }
    glEnd();
}
