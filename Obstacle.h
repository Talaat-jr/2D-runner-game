#pragma once

#include "BoundingBox.h"

class Obstacle : public BoundingBox{
    double x;
    double y;
	double* speed;
public:
    static double OBSTACLE_WIDTH;
    static double OBSTACLE_HEIGHT;

    Obstacle(double x, double y, double* speed);

    void draw();

    void animate();

    void move(double dx, double dy);
};