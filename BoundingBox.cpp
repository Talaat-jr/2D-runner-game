#include "BoundingBox.h"

BoundingBox::BoundingBox(double x, double y, double width, double height, bool xyCentered)
	: x(x), y(y), width(width), height(height), xyCentered(xyCentered) {};

BoundingBox::BoundingBox(double x, double y, double width, double height)
	: x(x), y(y), width(width), height(height), xyCentered(true) {};

bool BoundingBox::isColliding(BoundingBox& other) {
	/*return getStartX() < other.getEndX() && getEndX() > other.getStartX() &&
		getStartY() < other.getEndY() && getEndY() > other.getStartY();*/

	if (getEndX() < other.getStartX() || getStartX() > other.getEndX())
		return false;
	if (getEndY() < other.getStartY() || getStartY() > other.getEndY())
		return false;
	return true;
	//return !(getEndX() < other.getStartX() || getStartX() > other.getEndX() || getEndY() < other.getStartY() || getStartY() > other.getEndY());
}

double BoundingBox::getStartX() {
	if (!xyCentered) return x;
	return x - width / 2;
}

double BoundingBox::getStartY() {
	if (!xyCentered) return y;
	return y - height / 2;
}

double BoundingBox::getEndX() {
	if (!xyCentered) return x + width;
	return x + width / 2;
}

double BoundingBox::getEndY() {
	if (!xyCentered) return y + height;
	return y + height / 2;
}
