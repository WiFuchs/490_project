#ifndef VISITREP_H
#define VISITREP_H

#include "psData.h"
#include "demogData.h"
#include "Visitor.h"

class visitorReport : public Visitor {
public:
    visitorReport() : numVisited(0) {}

    void visit(shared_ptr<demogData> e) override {
        //fill in
    }
    
    void visit(shared_ptr<psData> e) override {
        //fill in
    }

    private:
    	int numVisited;
};

#endif