#include "Ethnicity.h"
#include <sstream>
#include <math.h>
#include <iomanip>

/* print county demographic data */
/* fill in any other data to make printing easy  */
std::ostream& operator<<(std::ostream &out, const Ethnicity &E) {
  out << "\nRacial Demographics Info:";
  out << "\n% American Indian and Alaska Native percent: " << (E.getAIndianANativeAlone() / E.getTotalPopulation2020()) * 100;
  out <<  " count: " << E.getAIndianANativeAlone();
  out << "\n% Asian American percent: " << (E.getAsianAlone() / E.getTotalPopulation2020()) * 100;
  out <<  " count: " << E.getAsianAlone();
  out << "\n% Black/African American percent: " << (E.getBlackAlone() / E.getTotalPopulation2020()) * 100;
  out <<  " count: " << E.getBlackAlone();
  out << "\n% Hispanic or Latinx percent: " << (E.getHispanicOrLatino() / E.getTotalPopulation2020()) * 100;
  out <<  " count: " << E.getHispanicOrLatino();
  out << "\n% Native Hawaiian and Other Pacific Islander: " << (E.getHawaiianPIslanderAlone() / E.getTotalPopulation2020()) * 100;
  out <<  " count: " << E.getHawaiianPIslanderAlone();
  out << "\n% Two or More Races percent: " << (E.getTwoOrMore() / E.getTotalPopulation2020()) * 100;
  out <<  " count: " << E.getTwoOrMore();
  out << "\n% White (inclusive): " << (E.getWhiteAlone() / E.getTotalPopulation2020()) * 100;
  out <<  " count: " << E.getWhiteAlone();
  out << "\n% White (nonHispanic): " << (E.getWhiteNotHispOrLat() / E.getTotalPopulation2020()) * 100;
  out <<  " count: " << E.getWhiteNotHispOrLat();

  return out;
}
