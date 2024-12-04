#pragma once

#include "BoundingBox.h"

class Collectable : public BoundingBox {
    double x;
    double y;
	double width;
	double height;
    double* speed;

public:
    static double COLLECTABLE_WIDTH;
    static double COLLECTABLE_HEIGHT;

    class Collectable(double x, double y, double* speed);

    void draw();

    void animate();

    void move(double dx, double dy);

	void drawCoin(float x, float y, float radius);
};