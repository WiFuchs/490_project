//
// Created by Will Fuchs on 2/5/22.
//

#ifndef INC_490_PROJECT_ANNULUS_H
#define INC_490_PROJECT_ANNULUS_H

#include <iostream>
#include "color.h"
#include "vec2.h"
#include "shape.h"


class annulus : public shape {
public:
    annulus(double cX, double cY, double rInner, double rOuter, color C) : shape(C, 0),
                                                                   center(cX, cY), innerRad(rInner), outerRad(rOuter) {}



    bool eval(double x, double y) const override {
        bool inOuterCircle = (((center.x()-x)*(center.x()-x))/(outerRad*outerRad) +
                              ((center.y()-y)*(center.y()-y))/(outerRad*outerRad) - 1.0f) < 0;
        bool inInnerCircle = (((center.x()-x)*(center.x()-x))/(innerRad*innerRad) +
                              ((center.y()-y)*(center.y()-y))/(innerRad*innerRad) - 1.0f) < 0;;
        return inOuterCircle && !inInnerCircle;
    }

    void translate(vec2 offSet) { center += offSet; }
    void setCenter(vec2 inCenter) { center = inCenter; }

    void placeAt(double x, double y) override {
        center = vec2(x, y);
    }

private:
    vec2 center; //center point of ellipse
    float innerRad;
    float outerRad;
};


#endif//INC_490_PROJECT_ANNULUS_H
