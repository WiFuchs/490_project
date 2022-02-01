#include "demogState.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>

//add member functions here

/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogState&SD) {
  out << std::setprecision(2) << std::fixed;
  out << "State Info: " << SD.getState() << endl;
  out << "Number of Counties: " << SD.getCounties() << endl;

  out << "Population info:" << endl;
  out << "(over 65): " << SD.getPopOver65P() << " and total: " << SD.getPopOver65() << endl;
  out << "(under 18): " << SD.getPopUnder18P() << " and total: " << SD.getPopUnder18() << endl;
  out << "(under 5): " << SD.getPopUnder5P() << " and total: " << SD.getPopUnder5() << endl;
  out << "(female): " << SD.getFemalesP() << " and total: " << SD.getFemales() << endl;

  out << "Education info:" << endl;
  out << "(Bachelor or more): " << SD.getBachelorsDegreeP() << " and total " << SD.getBachelorsDegree() << endl;
  out << "(high school or more): " << SD.getHighSchoolDegreeP() << " and total " << SD.getHighSchoolDegree() << endl;
  out << "medIncome: $" << SD.getMedianIncome() << endl;
  out << "Total population: " << SD.getTotalPopulation2020() << endl;

  return out;
}
