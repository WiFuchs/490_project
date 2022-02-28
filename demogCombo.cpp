#include "demogCombo.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>

//add member functions here

/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogCombo &SD) {
  out << std::setprecision(2) << std::fixed;
  out << "**US census data:State Info: " << SD.getName() << endl;
  out << "Number of Counties: " << SD.getCounties() << endl;

  SD.print();

    return out;
}
