#pragma once

#include "BoundingBox.h"

class NoGravity : public BoundingBox {
	double x;
	double y;
	double angle;
	double duration;
	double startTime;
	double* speed;
public:
	static double NO_GRAVITY_WIDTH;
	static double NO_GRAVITY_HEIGHT;
	NoGravity(double x, double y, double duration, double* speed);

	void draw();

	void animate();

	void drawNoGravityPowerUp(float x, float y, float size);

	double getDuration();

	void move(double dx, double dy);
};