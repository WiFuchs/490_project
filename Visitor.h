#ifndef VISITOR_H
#define VISITOR_H

//#include "psData.h"
//#include "psCombo.h"
//#include "demogData.h"
class psData;
class demogData;
class psCombo;
/* a visitor can visit any of my specific data types */
class Visitor {
  public:
    virtual void visit(std::shared_ptr<psData> ps) = 0;
    virtual void visit(std::shared_ptr<demogData> d) = 0;
    virtual void visit(std::shared_ptr<psCombo> d) = 0;
};
#endif

