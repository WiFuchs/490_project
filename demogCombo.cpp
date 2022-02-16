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
  out << "Total population: " << SD.getTotalPopulation2020() << endl;
  out << SD.getEthnicity() << endl;

  out << "--Population Age info:" << endl;
  out << "(under 5): " << SD.getPopUnder5() << "% and total: " << SD.getPopUnder5Count() << endl;
  out << "(under 18): " << SD.getPopUnder18() << "% and total: " << SD.getPopUnder18Count() << endl;
  out << "(over 65): " << SD.getPopOver65() << "% and total: " << SD.getPopOver65Count() << endl;

  out << "--Population other demographics:" << endl;
  out << "(female): " << SD.getFemales() << "% and total: " << SD.getFemalesCount() << endl;
  out << "(foreign born): " << SD.getForeignBorn() << "% and total: " << SD.getForeignBornCount() << endl;
  out << "(veterans): " << SD.getVeterans() << "% and total: " << SD.getVeteransCount() << endl;

  out << "--County housing/economy info" << endl;
  out << "(avg. persons per house): " << SD.getAvgPersonsPerHouse() << " and total units: " << SD.getHousingUnits() << endl;
  out << "(home ownership): " << SD.getHomeowners() << "% and total " << SD.getHomeownersCount() << endl;
  out << "(number house holds): " << SD.getHousingUnits() << endl;
  out << "medIncome: $" << SD.getMedianIncome() << " tot: " << endl;

  out << "--County education:" << endl;
  out << "(Bachelor or more): " << SD.getBachelorsDegree() << "% and total " << SD.getBachelorsDegreeCount() << endl;
  out << "(high school or more): " << SD.getHighSchoolDegree() << "% and total " << SD.getHighSchoolDegreeCount() << endl;
  return out;
}
