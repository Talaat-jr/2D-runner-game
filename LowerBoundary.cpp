#include "LowerBoundary.h"
#include "Color.h"
#include <cmath>
#include <glut.h>

LowerBoundary::LowerBoundary(double x, double y)
	: x(x), y(y) {};

void LowerBoundary::draw() {
	glPushMatrix();
	glTranslatef(x, y, 0);

	Color brown = Color(0.6f, 0.4f, 0.2f);
	Color red = Color(1.0f, 0.0f, 0.0f);
	Color lightGray = Color(0.7f, 0.7f, 0.7f);
	Color green = Color(0.0f, 1.0f, 0.0f);

	double size =50.0f;

	brown.apply();
    glBegin(GL_QUADS);
    for (int i = -5; i <= 5; ++i) {
        glVertex2f(i * size * 2.0f, -size * 1.5f); // Bottom-left
        glVertex2f((i + 1) * size * 2.0f, -size * 1.5f); // Bottom-right
        glVertex2f((i + 1) * size * 2.0f, -size * 0.5f); // Top-right
        glVertex2f(i * size * 2.0f, -size * 0.5f); // Top-left
    }
    glEnd();

    // 2. Spikes (GL_TRIANGLES) - Triangles resembling spikes
	red.apply();
    glBegin(GL_TRIANGLES);
    for (int i = -5; i <= 5; ++i) {
        glVertex2f(i * size * 2.0f, -size * 0.5f); // Base-left of the spike
        glVertex2f((i + 0.5f) * size * 2.0f, 0.0f); // Top of the spike
        glVertex2f((i + 1) * size * 2.0f, -size * 0.5f); // Base-right of the spike
    }
    glEnd();

    // 3. Rocks or Bubbles (GL_TRIANGLE_FAN) - Circular shapes
	lightGray.apply();
    for (int i = -4; i <= 4; i += 2) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(i * size * 2.0f + size, -size); // Center of the circle
        for (int j = 0; j <= 20; ++j) {
            float angle = j * 2.0f * 3.14159f / 20;
            glVertex2f(i * size * 2.0f + size + cos(angle) * size * 0.4f, -size + sin(angle) * size * 0.4f);
        }
        glEnd();
    }

    // 4. Decorative Lines (GL_LINES) - Horizontal lines for detail
	green.apply();
    glBegin(GL_LINES);
    for (int i = -5; i <= 5; ++i) {
        glVertex2f(i * size * 2.0f, -size * 1.3f); // Start of line
        glVertex2f((i + 1) * size * 2.0f, -size * 1.3f); // End of line

        glVertex2f(i * size * 2.0f, -size * 0.7f); // Start of another line
        glVertex2f((i + 1) * size * 2.0f, -size * 0.7f); // End of another line
    }
    glEnd();
	glPopMatrix();
}