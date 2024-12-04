#include "NoGravity.h"
#include "Color.h"
#include <cmath>
#include <glut.h>

double NoGravity::NO_GRAVITY_WIDTH = 30;
double NoGravity::NO_GRAVITY_HEIGHT = 30;

NoGravity::NoGravity(double x, double y, double duration, double* speed)
	: BoundingBox(x, y, NO_GRAVITY_WIDTH, NO_GRAVITY_HEIGHT), x(x), y(y), duration(duration), startTime(glutGet(GLUT_ELAPSED_TIME)), speed(speed), angle(0) {};

void NoGravity::draw() {
	glPushMatrix();
	glTranslatef(x, y, 0);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    double size = 40.0f;
	drawNoGravityPowerUp(x, y, size);

	glPopMatrix();
}

void NoGravity::animate() {
    angle += 1.0f;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }

	x -= *speed;
	BoundingBox::x = x;
}

double NoGravity::getDuration() {
    return duration;
}

void NoGravity::move(double dx, double dy) {
    x += dx;
    y += dy;
}

void NoGravity::drawNoGravityPowerUp(float x, float y, float size) {

	Color blue = Color(0.0f, 0.5f, 1.0f);
	Color lightBlue = Color(0.0f, 0.8f, 1.0f);
	Color darkBlue = Color(0.0f, 0.4f, 0.8f);

    // 1. Central Circle (GL_TRIANGLE_FAN)
	blue.apply();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center of the circle
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.14159f / 20;
        glVertex2f(cos(angle) * size * 0.4f, sin(angle) * size * 0.4f);
    }
    glEnd();

    // 2. Upward Arrows (GL_TRIANGLES)
	lightBlue.apply();
    glBegin(GL_TRIANGLES);
    // Left Arrow
    glVertex2f(-size * 0.2f, size * 0.2f);
    glVertex2f(-size * 0.1f, size * 0.4f);
    glVertex2f(-size * 0.3f, size * 0.4f);

    // Right Arrow
    glVertex2f(size * 0.2f, size * 0.2f);
    glVertex2f(size * 0.3f, size * 0.4f);
    glVertex2f(size * 0.1f, size * 0.4f);
    glEnd();

    // 3. Base Rectangle (GL_QUADS)
	darkBlue.apply();
    glBegin(GL_QUADS);
    glVertex2f(-size * 0.2f, -size * 0.4f);
    glVertex2f(size * 0.2f, -size * 0.4f);
    glVertex2f(size * 0.2f, -size * 0.35f);
    glVertex2f(-size * 0.2f, -size * 0.35f);
    glEnd();

    // 4. Radiating Lines (GL_LINES)
	lightBlue.apply();
    glBegin(GL_LINES);
    // Left Lines
    glVertex2f(-size * 0.45f, size * 0.15f);
    glVertex2f(-size * 0.3f, size * 0.15f);

    glVertex2f(-size * 0.45f, -size * 0.15f);
    glVertex2f(-size * 0.3f, -size * 0.15f);

    // Right Lines
    glVertex2f(size * 0.3f, size * 0.15f);
    glVertex2f(size * 0.45f, size * 0.15f);

    glVertex2f(size * 0.3f, -size * 0.15f);
    glVertex2f(size * 0.45f, -size * 0.15f);
    glEnd();
}

