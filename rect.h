#ifndef RECT_H
#define RECT_H

#include "shape.h"
#include "vec2.h"

/* simple data representation of a rectangle */
class Rect : public shape {
  public:
	Rect(double x, double y, double inWidth, double inHeight, color C, double deep) : shape(C, deep),
		center(x, y), width(inWidth), height(inHeight) {}



	bool eval(double x, double y) const override {
        vec2 upperL = vec2(center.x() - width/2, center.y() - height/2);
        vec2 lowerR = vec2(center.x() + width/2, center.y() + height/2);
		if ((x >= upperL.x() && x <= lowerR.x()) && (y >= upperL.y() && y <= lowerR.y())) {
			return true;
		}
		return false;
	}

    void placeAt(double x, double y) override {
        center = vec2(x, y);
    }

  private:
	vec2 center;
	double width;
    double height;
};

#endif