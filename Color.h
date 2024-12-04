#pragma once

class Color{
private:
	double red;
	double green;
	double blue;
public:
	Color(double red, double green, double blue);

	void apply();
};
