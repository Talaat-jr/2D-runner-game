#pragma once

#include "Player.h"
#include "Color.h"

class HealthBar {
	double x;
	double y;
	int maxLives;
	Player* player;
public:
	HealthBar(double x, double y, int maxLives, Player* player);

	void draw();

	void drawLives(int lives, int maxLives);

	void drawHeart(float x, float y, float size, Color color);

};