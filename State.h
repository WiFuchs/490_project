//
// Created by Will Fuchs on 2/4/22.
//

#ifndef INC_490_PROJECT_STATE_H
#define INC_490_PROJECT_STATE_H

#include "psCombo.h"
#include "demogCombo.h"
using namespace std;


class State {
public:
    explicit State(string name) : name(name) {}
    shared_ptr<psCombo> getPSData() const {return psData;}
    shared_ptr<demogCombo> getDemoData() const {return demoData;}
    void setPSData(shared_ptr<psCombo> data) {psData = data;}
    void setDemoData(shared_ptr<demogCombo> data) {demoData = data;}
    string getName() {return name;}

private:
    string name;
    shared_ptr<psCombo> psData;
    shared_ptr<demogCombo> demoData;
};


#endif//INC_490_PROJECT_STATE_H
