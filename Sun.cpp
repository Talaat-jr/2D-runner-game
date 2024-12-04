#include "Sun.h"
#include "Color.h"
#include <cmath>
#include <glut.h>

Sun::Sun(double x, double y)
	: x(x), y(y), angle(0) {};

void Sun::draw() {

	Color yellow = Color(1.0f, 1.0f, 0.0f);
	Color orangeYellow = Color(1.0f, 0.8f, 0.0f);
	Color orange = Color(1.0f, 0.6f, 0.0f);
	Color lightYellow = Color(1.0f, 0.9f, 0.5f);

	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, 1);

	double size = 150;
	yellow.apply();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center of the sun
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 2.0f * 3.14159f / 20;
        glVertex2f(cos(angle) * size * 0.5f, sin(angle) * size * 0.5f); // Circle radius = 0.5 * size
    }
    glEnd();

    // 2. Sun Rays (GL_LINES) - Radiating lines for sunbeams
	orangeYellow.apply();
    glBegin(GL_LINES);
    for (int i = 0; i < 12; ++i) {
        float angle = i * 2.0f * 3.14159f / 12; // 12 rays
        glVertex2f(cos(angle) * size * 0.6f, sin(angle) * size * 0.6f); // Start of the ray (just outside the core)
        glVertex2f(cos(angle) * size, sin(angle) * size); // End of the ray
    }
    glEnd();

    // 3. Triangular Rays (GL_TRIANGLES) - Large triangular sunbeams
	orange.apply();
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; ++i) {
        float angle = i * 2.0f * 3.14159f / 8;
        glVertex2f(cos(angle) * size * 0.6f, sin(angle) * size * 0.6f); // Base-left of triangle
        glVertex2f(cos(angle + 3.14159f / 16) * size * 1.2f, sin(angle + 3.14159f / 16) * size * 1.2f); // Tip of triangle
        glVertex2f(cos(angle + 3.14159f / 8) * size * 0.6f, sin(angle + 3.14159f / 8) * size * 0.6f); // Base-right of triangle
    }
    glEnd();

    // 4. Outer Glow or Ring (GL_LINE_LOOP) - A ring around the sun for decoration
	lightYellow.apply();
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 40; ++i) {
        float angle = i * 2.0f * 3.14159f / 40;
        glVertex2f(cos(angle) * size * 1.3f, sin(angle) * size * 1.3f); // Outer ring with radius 1.3 * size
    }
    glEnd();

	glPopMatrix();
}

void Sun::animate() {
	angle += 0.1;
	if (angle > 360) {
		angle -= 360;
	}
}