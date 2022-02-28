#include "demogData.h"
#include "Ethnicity.h"
#include <sstream>
#include <math.h>
#include <iomanip>

/* print county demographic data */
/* fill in any other data to make printing easy  */
std::ostream& operator<<(std::ostream &out, const demogData &DD) {
    out << "County Demographics Info: " << DD.getName();
    out << std::setprecision(2) << std::fixed;
    out << " total population: " << DD.getTotalPopulation2020();

    out << "\ntotal Racial Demographics Count: " << DD.getEthnicity();

    //consider re-writing with getters....
    out << "\n--Population Age Info:";
    out << "\n(under 5): " << DD.getPopUnder5() * 100;
    out <<  " and total: " << DD.getPopUnder5Count();
    out << "\n(under 18): " << DD.getPopUnder18() * 100;
    out <<  " and total: " << DD.getPopUnder18Count();
    out << "\n(over 65): " << DD.getPopOver65() * 100;
    out <<  " and total: " << DD.getPopOver65Count();

    out << "\n--Population other demographics";
    out << "\n(female): " << DD.getFemales() * 100;
    out <<  " and total: " << DD.getFemalesCount();
    out <<"\n(foreign born): " << DD.getForeignBorn() * 100;
    out <<  " and total: " << DD.getForeignBornCount();
    out <<"\n(veterans): " <<  DD.getVeterans() * 100;
    out <<  " and total: " << DD.getVeteransCount();

    out << "\n--County housing/economy info: ";
    out <<"\n(avg. persons per house): " << DD.getPersonsPerHouse();
    out <<  " and total: " << "???";
    out <<"\n(home ownership): " << DD.getHomeOwnershipRate() * 100;
    out <<  " and total: " << DD.getHomeownersCount();
    out <<"\n(number housing units): " << DD.getHousingUnits();
    out <<"\n(medium income): $" << DD.getMedianIncome();

    out <<"\n--County education:";
    out <<"\n(Bachelor or more): " << DD.getBachelorsDegree() * 100;
    out <<  " and total: " << DD.getBachelorsDegreeCount();

    out <<"\n(high school or more): " << DD.getHighSchoolDegree() * 100;
    out <<  " and total: " << DD.getHighSchoolDegreeCount();

    return out;
}
