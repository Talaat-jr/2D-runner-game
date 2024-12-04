#include "DoublePoint.h"
#include "Color.h"
#include <cmath>
#include <glut.h>

double DoublePoint::DOUBLE_POINT_WIDTH = 30;
double DoublePoint::DOUBLE_POINT_HEIGHT = 30;

DoublePoint::DoublePoint(double x, double y, double duration, double* speed)
	: BoundingBox(x, y, DOUBLE_POINT_WIDTH, DOUBLE_POINT_HEIGHT), x(x), y(y), duration(duration), startTime(glutGet(GLUT_ELAPSED_TIME)), speed(speed), angle(0) {}

void DoublePoint::draw() {
	glPushMatrix();
	glTranslatef(x, y, 0);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

	Color green = Color(0.0, 1.0, 0.0);
	Color yellow = Color(0.9f, 0.8f, 0.0f);
	Color red = Color(1.0f, 0.0f, 0.0f);
	Color blue = Color(0.0f, 0.0f, 1.0f);
	Color gold = Color(1.0f, 0.84f, 0.0f);

    double size = 20.0f;

    // 1. Circular Base (GL_TRIANGLE_FAN)
	yellow.apply();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center of the circle
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.14159f / 20;
        glVertex2f(cos(angle) * size, sin(angle) * size);
    }
    glEnd();

    // 2. First Star (GL_TRIANGLES)
	red.apply();
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 5; ++i) {
        float outerAngle = i * 2.0f * 3.14159f / 5.0f;
        float innerAngle = (i + 0.5f) * 2.0f * 3.14159f / 5.0f;
        glVertex2f(cos(outerAngle) * size * 0.6f, sin(outerAngle) * size * 0.6f);
        glVertex2f(cos(innerAngle) * size * 0.3f, sin(innerAngle) * size * 0.3f);
    }
    glEnd();

    // 3. Second Star (GL_TRIANGLES) rotated slightly for the "double" effect
	blue.apply();
    glPushMatrix();
    glRotatef(36.0f, 0.0f, 0.0f, 1.0f); // Rotate by 36 degrees
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 5; ++i) {
        float outerAngle = i * 2.0f * 3.14159f / 5.0f;
        float innerAngle = (i + 0.5f) * 2.0f * 3.14159f / 5.0f;
        glVertex2f(cos(outerAngle) * size * 0.6f, sin(outerAngle) * size * 0.6f);
        glVertex2f(cos(innerAngle) * size * 0.3f, sin(innerAngle) * size * 0.3f);
    }
    glEnd();
    glPopMatrix();

    // 4. "2X" Bar (GL_QUADS)
	gold.apply();
    glBegin(GL_QUADS);
    glVertex2f(-size * 0.4f, -size * 0.1f); // Bottom-left
    glVertex2f(size * 0.4f, -size * 0.1f);  // Bottom-right
    glVertex2f(size * 0.4f, size * 0.1f);   // Top-right
    glVertex2f(-size * 0.4f, size * 0.1f);  // Top-left
    glEnd();

    // 5. Radiating Outer Lines (GL_LINES) to give it a dynamic energy effect
	yellow.apply();
    glBegin(GL_LINES);
    for (int i = 0; i < 8; ++i) {
        float angle = i * 2.0f * 3.14159f / 8.0f;
        glVertex2f(cos(angle) * size * 0.7f, sin(angle) * size * 0.7f); // Inner point
        glVertex2f(cos(angle) * size * 1.0f, sin(angle) * size * 1.0f); // Outer point
    }
    glEnd();

	glPopMatrix();
}

void DoublePoint::animate() {
    angle += 1.0f;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
	x -= *speed;
	BoundingBox::x = x;
}

double DoublePoint::getDuration() {
    return duration;
}

void DoublePoint::move(double dx, double dy) {
    x += dx;
    y += dy;
}