#ifndef VISITREP_H
#define VISITREP_H

#include "psData.h"
#include "demogData.h"
#include "Visitor.h"

class visitorReport : public Visitor {
public:
    visitorReport() : numVisited(0) {}

    void visit(shared_ptr<demogData> e) override {
        cout << *e << endl;
    }
    
    void visit(shared_ptr<psData> e) override {
        cout << *e << endl;
    }

    void visit(std::shared_ptr<psCombo> d) override {
        cout << d << endl;
    }


    private:
    	int numVisited;
};

#endif