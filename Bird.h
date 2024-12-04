#pragma once

class Bird {
	double x;
	double y;
	double angle;
	double* speed;
public:
	Bird(double x, double y, double* speed);

	void draw();

	void animate();

	void drawBird(float x, float y, float size);

	void move(double dx, double dy);
};