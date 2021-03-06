#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <iostream>
#include "color.h"
#include "vec2.h"
#include "shape.h"

/* simple data representation of an implicit ellipse */
class ellipse : public shape {
  public:
	ellipse(double cX, double cY, double r1, double r2, color C) : shape{C, 0}, 
		center(cX, cY), radii(r1, r2) {}
	ellipse(vec2 inC, double r1, double r2, double d, color C) : shape{C, d},
		 center(inC), radii(r1, r2) {}
	ellipse(vec2 inC, vec2 inR, double d, color C) : shape{C, d},
		 center(inC), radii(inR) {}
	ellipse(double cX, double cY, double r1, double r2, double d, color C) : shape{C, d},
		center(cX, cY), radii(r1, r2) {}



	bool eval(double x, double y) const override {
		 return ( ((center.x()-x)*(center.x()-x))/(radii.x()*radii.x()) +
				((center.y()-y)*(center.y()-y))/(radii.y()*radii.y()) - 1.0f) < 0;
	}

	void translate(vec2 offSet) { center += offSet; }
	void setCenter(vec2 inCenter) { center = inCenter; }

    void placeAt(double x, double y) override {
        center = vec2(x, y);
    }

  private:
	vec2 center; //center point of ellipse
	vec2 radii; //radii of the ellipse
	//note lifted data
};

#endif