#pragma once

class Sun {
	double x;
	double y;
	double angle;
public:
	Sun(double x, double y);

	void draw();

	void animate();
};