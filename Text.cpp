#include "Text.h"
#include <glut.h>

Text::Text(double x, double y, std::string text, Color color, void* font)
	: x(x), y(y), text(text), color(color), font(font) {}

void Text::draw() {
	color.apply();
	glRasterPos2d(x, y);
	for (int i = 0; i < text.length(); i++) {
		glutBitmapCharacter(font, text[i]);
	}
}

void Text::setText(std::string text) {
	this->text = text;
}
