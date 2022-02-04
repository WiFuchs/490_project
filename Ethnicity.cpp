#include "Ethnicity.h"
#include <sstream>
#include <math.h>
#include <iomanip>

/* print county demographic data */
/* fill in any other data to make printing easy  */
std::ostream& operator<<(std::ostream &out, const Ethnicity &E) {
  out << "\nRacial Demographics Info:";
  out << "\n% American Indian and Alaska Native percent: " << (E.getAIndianANativeAlone() * 100);
  out <<  " count: " << E.getAIndianANativeAloneCount();
  out << "\n% Asian American percent: " << E.getAsianAlone() * 100;
  out <<  " count: " << E.getAsianAloneCount();
  out << "\n% Black/African American percent: " << E.getBlackAlone() * 100;
  out <<  " count: " << E.getBlackAloneCount();
  out << "\n% Hispanic or Latinx percent: " << E.getHispanicOrLatino() * 100;
  out <<  " count: " << E.getHispanicOrLatinoCount();
  out << "\n% Native Hawaiian and Other Pacific Islander: " << E.getHawaiianPIslanderAlone() * 100;
  out <<  " count: " << E.getHawaiianPIslanderAloneCount();
  out << "\n% Two or More Races percent: " << E.getTwoOrMore() * 100;
  out <<  " count: " << E.getTwoOrMoreCount();
  out << "\n% White (inclusive): " << E.getWhiteAlone() * 100;
  out <<  " count: " << E.getWhiteAloneCount();
  out << "\n% White (nonHispanic): " << E.getWhiteNotHispOrLat() * 100;
  out <<  " count: " << E.getWhiteNotHispOrLatCount();
  out << "\n% Unspecified: " << E.getUnspecified() * 100;
  out <<  " count: " << E.getUnspecifiedCount();

  return out;
}
