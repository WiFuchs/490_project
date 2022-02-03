#ifndef SHAPE_H
#define SHAPE_H
#include "vec2.h"
#include "color.h"

/* a base class for our lecture code! */
class shape {
  public:
  	shape(color theColor, double inDepth) : inC(theColor), depth(inDepth) {}
	color getInC() const {return inC; }
	double getDepth() const {return depth; }

    virtual bool eval(double x, double y) const = 0;
    virtual void placeAt(double x, double y) = 0;

  protected:
	color inC;
	double depth;
};

#endif