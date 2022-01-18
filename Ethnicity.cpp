#include "Ethnicity.h"
#include <sstream>
#include <math.h>
#include <iomanip>

/* print county demographic data */
/* fill in any other data to make printing easy  */
std::ostream& operator<<(std::ostream &out, const Ethnicity &E) {

  out << "\n% American Indian and Alaska Native percent: " << E.getAIndianANativeAlone();
  out <<  " count: " << E.getAIndianANativeAloneCount();
  out << "\n% Asian American percent: " << E.getAsianAlone();
  out <<  " count: " << E.getAsianAloneCount();
  out << "\n% Black/African American percent: " << E.getBlackAlone();
  out <<  " count: " << E.getBlackAloneCount();
  out << "\n% Hispanic or Latinx percent: " << E.getHispanicOrLatino();
  out <<  " count: " << E.getHispanicOrLatinoCount();
  out << "\n% Native Hawaiian and Other Pacific Islander: " << E.getHawaiianPIslanderAlone();
  out <<  " count: " << E.getHawaiianPIslanderAloneCount();
  out << "\n% Two or More Races percent: " << E.getTwoOrMore();
  out <<  " count: " << E.getTwoOrMoreCount();
  out << "\n% White (inclusive): " << E.getWhiteAlone();
  out <<  " count: " << E.getWhiteAloneCount();
  out << "\n% White (nonHispanic): " << E.getWhiteNotHispOrLat();
  out <<  " count: " << E.getWhiteNotHispOrLatCount();

  return out;
}
