#pragma once

class BoundingBox {
public:
	double x, y;
	double width, height;
	bool xyCentered;

	virtual ~BoundingBox() = default;

	BoundingBox(double x, double y, double width, double height, bool xyCentered);
	BoundingBox(double x, double y, double width, double height);

	bool isColliding(BoundingBox& other);

	double getStartX();
	double getStartY();
	double getEndX();
	double getEndY();
};