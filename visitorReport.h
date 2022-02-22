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
    void visit(shared_ptr<psCombo> data) {
        cout << "visited: " << data.getName() << ": " << data.getNumberOfCases();
    }
    void visit(shared_ptr<psData> data) {
        cout << "visited: " << data.getArmed();
    }
    void visit(shared_ptr<demogData> data) {
        cout << "visited: " << data.getName() << ": " << data.getPopOver65();
    }
};


#endif//INC_490_PROJECT_VISITORREPORT_H
