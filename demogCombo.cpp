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
  out << "**US census data:State Info: " << SD.getState() << endl;
  out << "Number of Counties: " << SD.getCounties() << endl;
  out << "Total population: " << SD.getTotalPopulation2020() << endl;
  out << SD.getEthnicity() << endl;

  out << "--Population Age info:" << endl;
  out << "(under 5): " << SD.getPopUnder5P() << "% and total: " << SD.getPopUnder5() << endl;
  out << "(under 18): " << SD.getPopUnder18P() << "% and total: " << SD.getPopUnder18() << endl;
  out << "(over 65): " << SD.getPopOver65P() << "% and total: " << SD.getPopOver65() << endl;

  out << "--Population other demographics:" << endl;
  out << "(female): " << SD.getFemalesP() << "% and total: " << SD.getFemales() << endl;
  out << "(foreign born): " << SD.getForeignBornP() << "% and total: " << SD.getForeignBorn() << endl;
  out << "(veterans): " << SD.getVeteransP() << "% and total: " << SD.getVeterans() << endl;

  out << "--County housing/economy info" << endl;
  out << "(avg. persons per house): " << SD.getAvgPersonsPerHouse() << " and total: " << SD.getAvgPersonsPerHouse() << endl;
  out << "(home ownership): " << SD.getHomeownersP() << "% and total " << SD.getHomeowners() << endl;
  out << "(number house holds): " << SD.getHousingUnits() << endl;
  out << "medIncome: $" << SD.getMedianIncome() << " tot: " << endl;

  out << "--County education:" << endl;
  out << "(Bachelor or more): " << SD.getBachelorsDegreeP() << "% and total " << SD.getBachelorsDegree() << endl;
  out << "(high school or more): " << SD.getHighSchoolDegreeP() << "% and total " << SD.getHighSchoolDegree() << endl;
  return out;
}
