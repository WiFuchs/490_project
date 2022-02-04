//
// Created by Will Fuchs on 2/4/22.
//

#ifndef INC_490_PROJECT_STATE_H
#define INC_490_PROJECT_STATE_H

#include "psCombo.h"
#include "demogState.h"


class State {
public:
    shared_ptr<psCombo> getPSData() {return psData;}
    shared_ptr<demogState> getDemoData() {return demoData;}
private:
    shared_ptr<psCombo> psData;
    shared_ptr<demogState> demoData;
};


#endif//INC_490_PROJECT_STATE_H
