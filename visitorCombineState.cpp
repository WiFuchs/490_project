//
// Created by Sarah Hallam on 2/22/22.
//

#include "visitorCombineState.h"
#include "psCombo.h"

void visitorCombineState::visit(shared_ptr<psCombo> data) override{
    cout << "this should never happen" << endl;
}

void visitorCombineState::visit(shared_ptr<psData> data) override{
    auto mapEntry = comboPolice.find(data->getState());
    if(mapEntry == comboPolice::end){
        comboPolice.insert(pair<string, shared_ptr<psCombo>>(data->getState(), make_shared<psCombo>(data->getState(), 0, 0, 0, 0, 0, data->getState(), Ethnicity(0,0,0,0,0,0,0,0,0))));
        mapEntry = comboPolice.find(data->getState());
    }

    shared_ptr<psCombo> comboData = mapEntry->second;
    *comboData += *data;
}

void visitorCombineState::visit(shared_ptr<demogData> data) override{}

