#include "Color.h"
#include <glut.h>

Color::Color(double red, double green, double blue) : red(red), green(green), blue(blue) {}

void Color::apply() {
	glColor3f(red, green, blue);
}
