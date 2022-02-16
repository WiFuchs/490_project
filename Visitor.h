//
// Created by Will Fuchs on 2/15/22.
//

#ifndef INC_490_PROJECT_VISITOR_H
#define INC_490_PROJECT_VISITOR_H

class Visitor {
public:
    virtual void visit(class psCombo &data) = 0;
    virtual void visit(class psData &data) = 0;
    virtual void visit(class demogData &data) = 0;
};


#endif//INC_490_PROJECT_VISITOR_H
