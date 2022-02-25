//
// Created by Will Fuchs on 2/15/22.
//

#ifndef INC_490_PROJECT_REGIONDATA_H
#define INC_490_PROJECT_REGIONDATA_H

#include <string>
#include <set>
#include "Visitor.h"


class regionData {
public:
    std::string getName() {return name;}
    std::set<std::string> getStates() {return states;}
    int getPopulation() {return population;}
    virtual void accept(class Visitor &v) = 0;
private:
    std::string name;
    std::set<std::string> states;
    int population;
};


#endif//INC_490_PROJECT_REGIONDATA_H
