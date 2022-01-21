//
// Created by Will Fuchs on 1/20/22.
//

#ifndef INC_490_PROJECT_RECT_H
#define INC_490_PROJECT_RECT_H

#include "vec2.h"
#include "color.h"

/* simple data representation of a rectangle */
class Rect {
public:
    Rect(double x, double y, double w, double h, color c):
            topLeft(x, y), width(w), height(h), inC(c), depth(0) {}

    double eval(double x, double y) {
        double leftX, rightX, topY, bottomY;
        leftX = topLeft.x();
        topY = topLeft.y();
        rightX = leftX + width;
        bottomY = topY + height;

        if (x < rightX && x > leftX && y < bottomY && y > topY) {
            //if (x < 100 && x > 50 && y < 100 && y > 50) {
            // inside
            return -1;
        }
        return 1;
    }

    color getInC() const {return inC; }
    double getDepth() const {return depth; }

private:
    double width;
    double height;
    vec2 topLeft;
    color inC;
    double depth;

};

#endif //INC_490_PROJECT_RECT_H
