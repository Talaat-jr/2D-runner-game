#include "obstacle.h"
#include "Color.h"
#include <cmath>
#include <glut.h>

double Obstacle::OBSTACLE_WIDTH = 25;
double Obstacle::OBSTACLE_HEIGHT = 25;
double angle = 0.0f;


Obstacle::Obstacle(double x, double y, double* speed)
	: BoundingBox(x, y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT), x(x), y(y), speed(speed){}

void Obstacle::draw() {
    int bladeCount = 25;
	float size = 25.0f;
    Color red = Color(1.0f, 0.0f, 0.0f);
	Color black = Color(0.0f, 0.0f, 0.0f);
	Color darkGray = Color(0.3f, 0.3f, 0.3f);

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // Blades (triangles)
    red.apply();
    for (int i = 0; i < bladeCount; ++i) {
        float angle = i * 2.0f * 3.14159f / bladeCount;
        float x1 = cos(angle) * size;
        float y1 = sin(angle) * size;
        float x2 = cos(angle + 0.1f) * size * 0.7f;
        float y2 = sin(angle + 0.1f) * size * 0.7f;

        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f); // Center point
        glVertex2f(x1, y1); // End of the blade
        glVertex2f(x2, y2); // Slightly off-center for width
        glEnd();
    }

    // Center block (rectangle)
    darkGray.apply();
    glBegin(GL_QUADS);
    glVertex2f(-size / 6, -size / 6);
    glVertex2f(size / 6, -size / 6);
    glVertex2f(size / 6, size / 6);
    glVertex2f(-size / 6, size / 6);
    glEnd();

    glPopMatrix();
}

void Obstacle::animate() {
    angle += 1.0f;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }

	x -= *speed;
	BoundingBox::x = x;
}

void Obstacle::move(double dx, double dy) {
    x += dx;
    y += dy;
}
