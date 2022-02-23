//
// Created by Will Fuchs on 2/15/22.
//

#ifndef INC_490_PROJECT_VISITOR_H
#define INC_490_PROJECT_VISITOR_H

#include "psCombo.h"
#include "psData.h"
#include "demogData.h"

class Visitor {
public:
    virtual void visit(shared_ptr<psCombo> data) = 0;
    virtual void visit(shared_ptr<psData> data) = 0;
    virtual void visit(shared_ptr<demogData> data) = 0;
};


#endif//INC_490_PROJECT_VISITOR_H
