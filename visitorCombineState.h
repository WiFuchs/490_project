#ifndef VCOMBOS_H
#define VCOMBOS_H


#include "visitorCombine.h"
#include <memory>

class visitorCombineState : public visitorCombine {
public:
    visitorCombineState() {}

	void visit(shared_ptr<demogData> data) {
        auto mapEntry = allComboDemogData.find(data->getState());
        if(mapEntry == allComboDemogData.end()){
            allComboDemogData.insert(pair<string, shared_ptr<psCombo> >(data->getState(), make_shared<psCombo>(data->getState(), 0, 0, 0, 0, 0, data->getState(), Ethnicity(0,0,0,0,0,0,0,0,0))));
            mapEntry = allComboDemogData.find(data->getState());
        }

        shared_ptr<demogCombo> comboData = mapEntry->second;
        *comboData += *data;
    }

    void visit(shared_ptr<psData> data) {
        auto mapEntry = allComboPoliceData.find(data->getState());
        if(mapEntry == allComboPoliceData.end()){
            allComboPoliceData.insert(pair<string, shared_ptr<psCombo> >(data->getState(), make_shared<psCombo>(data->getState(), 0, 0, 0, 0, 0, data->getState(), Ethnicity(0,0,0,0,0,0,0,0,0))));
            mapEntry = allComboPoliceData.find(data->getState());
        }

        shared_ptr<psCombo> comboData = mapEntry->second;
        *comboData += *data;
    }

    private:
       //inherited
};

#endif
