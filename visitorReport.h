//
// Created by Will Fuchs on 2/16/22.
//

#ifndef INC_490_PROJECT_VISITORREPORT_H
#define INC_490_PROJECT_VISITORREPORT_H

#include "Visitor.h"
#include "psCombo.h"
#include "psData.h"
#include "demogData.h"

class visitorReport : public Visitor {
public:
    void visit(class psCombo &data) {
        cout << "visited: " << data.getName() << ": " << data.getNumberOfCases();
    }
    void visit(class psData &data) {
        cout << "visited: " << data.getArmed();
    }
    void visit(class demogData &data) {
        cout << "visited: " << data.getName() << ": " << data.getPopOver65();
    }
};


#endif//INC_490_PROJECT_VISITORREPORT_H
