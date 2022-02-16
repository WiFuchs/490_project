//
// Created by Will Fuchs on 2/15/22.
//

#ifndef INC_490_PROJECT_REGIONDATA_H
#define INC_490_PROJECT_REGIONDATA_H

#include <string>
#include <vector>

class RegionData {
public:
    std::string getName() {return name;}
    std::vector<std::string> getStates() {return states;}
    int getPopulation() {return population;}
private:
    std::string name;
    std::vector<std::string> states;
    int population;
};


#endif//INC_490_PROJECT_REGIONDATA_H
