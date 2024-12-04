
#include "HealthBar.h"
#include <cmath>
#include <iostream>
#include <glut.h>


HealthBar::HealthBar(double x, double y, int maxLives, Player* player)
	: x(x), y(y), maxLives(maxLives), player(player) {}

void HealthBar::draw() {
    int playerLives = player->getLives();
	HealthBar::drawLives(playerLives, maxLives);
}

void HealthBar::drawLives(int lives, int maxLives) {
    float startX = x;
    float startY = y;
    float spacing = 30.15f;
    float heartSize = 20.0f;

	Color red = Color(1.0f, 0.0f, 0.0f);
	Color black = Color(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < maxLives; i++) {
        if (i < lives) {
			drawHeart(startX + i * spacing, startY, heartSize, red);
        }
		else {
			drawHeart(startX + i * spacing, startY, heartSize, black);
		}
    }
}


void HealthBar::drawHeart(float x, float y, float size, Color color) {
	color.apply();

    // Left half of the heart
    glBegin(GL_TRIANGLE_FAN);
	color.apply();
    glVertex2f(x, y);
    for (int i = 0; i <= 100; i++) {
        float angle = i * 2.0f * 3.14159f / 100;
        glVertex2f(x - size * 0.3f + cos(angle) * size * 0.3f,
            y + sin(angle) * size * 0.3f);
    }
    glEnd();

    // Right half of the heart
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 100; i++) {
        float angle = i * 2.0f * 3.14159f / 100;
        glVertex2f(x + size * 0.3f + cos(angle) * size * 0.3f,
            y + sin(angle) * size * 0.3f);
    }
    glEnd();

    // Bottom triangle of the heart
    glBegin(GL_TRIANGLES);
    glVertex2f(x - size * 0.6f, y);
    glVertex2f(x + size * 0.6f, y);
    glVertex2f(x, y - size);
    glEnd();
}
