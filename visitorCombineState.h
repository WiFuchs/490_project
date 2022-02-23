//
// Created by Sarah Hallam on 2/22/22.
//

#ifndef INC_490_PROJECT_VISITORCOMBINESTATE_H
#define INC_490_PROJECT_VISITORCOMBINESTATE_H
#include "visitorCombine.h"

class visitorCombineState : public visitorCombine {
    void visit(shared_ptr<psCombo> data) override;
    void visit(shared_ptr<psData> data) override;
    void visit(shared_ptr<demogData> data) override;
};


#endif//INC_490_PROJECT_VISITORCOMBINESTATE_H
