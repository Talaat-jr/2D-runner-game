#include "Bird.h"
#include "Color.h"
#include <cmath>
#include <glut.h>

Bird::Bird(double x, double y, double* speed)
	: x(x), y(y), speed(speed), angle(0) {};


void Bird::move(double dx, double dy) {
	x += dx;
	y += dy;
}

void Bird::draw() {
	glPushMatrix();
	glTranslatef(x, y, 0);

	double size = 20;
    drawBird(x, y, size);

	glPopMatrix();
}

void Bird::drawBird(float x, float y, float size) {

	Color white = Color(1.0f, 0.0f, 0.0f);
	Color lightBlue = Color(0.5f, 0.5f, 1.0f);
	Color orange = Color(1.0f, 0.5f, 0.0f);
	Color lightSkin = Color(1.0f, 0.8f, 0.6f);


    // 1. Bird Body (Using the original square for body)
	white.apply();
    glBegin(GL_QUADS);
    glVertex2f(-size, -size); // Bottom-left
    glVertex2f(size, -size);  // Bottom-right
    glVertex2f(size, size);   // Top-right
    glVertex2f(-size, size);  // Top-left
    glEnd();

    // 2. Bird Head (Smaller square on top of the body)
	lightSkin.apply();
    glBegin(GL_QUADS);
    glVertex2f(size * 0.2f, size * 0.7f);   // Bottom-left of the head
    glVertex2f(size * 0.6f, size * 0.7f);   // Bottom-right of the head
    glVertex2f(size * 0.6f, size * 1.1f);   // Top-right of the head
    glVertex2f(size * 0.2f, size * 1.1f);   // Top-left of the head
    glEnd();

    // 3. Bird Beak (Triangle in front of the head)
	orange.apply();
    glBegin(GL_TRIANGLES);
    glVertex2f(size * 0.6f, size * 0.9f);  // Tip of the beak
    glVertex2f(size * 0.75f, size * 0.95f); // Top corner of the beak
    glVertex2f(size * 0.75f, size * 0.85f); // Bottom corner of the beak
    glEnd();

    // 4. Bird Wings (Triangles on either side of the body)
	lightBlue.apply();
    glBegin(GL_TRIANGLES);
    // Left Wing
    glVertex2f(-size, 0.0f);       // Body-side point
    glVertex2f(-size * 1.5f, size * 0.5f); // Top-left wing
    glVertex2f(-size * 1.5f, -size * 0.5f); // Bottom-left wing
    // Right Wing
    glVertex2f(size, 0.0f);        // Body-side point
    glVertex2f(size * 1.5f, size * 0.5f); // Top-right wing
    glVertex2f(size * 1.5f, -size * 0.5f); // Bottom-right wing
    glEnd();

}

void Bird::animate() {
	x += *speed;
	y = 100 * sin(x / 100)+ 450;
	if (y > 470) y = 470;
    if (x > 600) x = 0;
}
