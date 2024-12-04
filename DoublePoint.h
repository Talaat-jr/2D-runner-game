#pragma once

#include "BoundingBox.h"

class DoublePoint : public BoundingBox {
	double x;
	double y;
	double duration;
	double startTime;
	double angle;
	double* speed;
public:
	static double DOUBLE_POINT_WIDTH;
	static double DOUBLE_POINT_HEIGHT;
	DoublePoint(double x, double y, double duration, double* speed);

	void draw();

	void animate();

	void drawDoublePointsPowerUp(float x, float y, float size);

	double getDuration();

	void move(double dx, double dy);
};