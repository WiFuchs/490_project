//
// Created by Will Fuchs on 2/16/22.
//

#ifndef INC_490_PROJECT_VISITORCOMBINE_H
#define INC_490_PROJECT_VISITORCOMBINE_H

#include <map>
#include "Visitor.h"
#include "demogCombo.h"
#include "psCombo.h"
using namespace std;

class visitorCombine : public Visitor{
public:
    shared_ptr<demogCombo> getComboDemogData(string regionName) {return comboDemog.find(regionName)->second;}
    shared_ptr<psCombo> getComboPoliceData(string regionName)  {return comboPolice.find(regionName)->second;}
    std::map<string, shared_ptr<demogCombo> >& getComboDemog() {return comboDemog;}
    std::map<string, shared_ptr<psCombo> > & getComboPolice() {return comboPolice;}

protected:
    std::map<string, shared_ptr<psCombo> > comboPolice;
    std::map<string, shared_ptr<demogCombo> > comboDemog;
};


#endif//INC_490_PROJECT_VISITORCOMBINE_H
