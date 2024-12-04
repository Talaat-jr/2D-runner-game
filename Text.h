#pragma once

#include <string>
#include "Color.h"

class Text {
	double x, y;
	std::string text;

public:
	Color color;
	void* font;
	Text(double x, double y, std::string text, Color color, void* font);

	void draw();

	void setText(std::string text);
};
