#ifndef ETHNICITY_H
#define ETHNICITY_H

#include <iostream>
#include <math.h>

using namespace std;

class Ethnicity {
  public:

    Ethnicity(double white, double black, double IndianOrNative,
      double asian, double hawaiianPIslander, double twoOrMore,
      double hispOrLat, double whiteNotHOrL, int totPop20) :
        whiteAlone(white), blackAlone(black), aIndianANativeAlone(IndianOrNative),
        asianAlone(asian), hawaiianPIslanderAlone(hawaiianPIslander),
        twoOrMore(twoOrMore), hispanicOrLatino(hispOrLat),
        whiteNotHispOrLat(whiteNotHOrL), totalPopulation2020(totPop20) {}

    double getTotalPopulation2020() const { return totalPopulation2020; }
    int getWhiteAlone() const { return whiteAlone; }
    int getWhiteAloneCount() const {
        double count = whiteAlone * totalPopulation2020;
        return round(count); }

    int getBlackAlone() const { return blackAlone; }
    int getBlackAloneCount() const {
      double count = blackAlone * totalPopulation2020;
      return round(count); }

    int getAIndianANativeAlone() const { return aIndianANativeAlone; }
    int getAIndianANativeAloneCount() const {
      double count = totalPopulation2020 * aIndianANativeAlone;
      return round(count); }

    int getAsianAlone() const { return asianAlone; }
    int getAsianAloneCount() const {
      double count = totalPopulation2020 * asianAlone;
      return round(count); }

    int getHawaiianPIslanderAlone() const { return hawaiianPIslanderAlone; }
    int getHawaiianPIslanderAloneCount() const {
      double count = totalPopulation2020 * hawaiianPIslanderAlone;
      return round(count); }

    int getTwoOrMore() const { return twoOrMore; }
    int getTwoOrMoreCount() const {
      double count = totalPopulation2020 * twoOrMore;
      return round(count); }

    int getHispanicOrLatino() const { return hispanicOrLatino; }
    int getHispanicOrLatinoCount() const {
      double count = totalPopulation2020 * hispanicOrLatino;
      return round(count); }

    int getWhiteNotHispOrLat() const { return whiteNotHispOrLat; }
    int getWhiteNotHispOrLatCount() const {
      double count = totalPopulation2020 * whiteNotHispOrLat;
      return round(count); }

    friend std::ostream& operator<<(std::ostream &out, const Ethnicity &E);

  private:
      const double whiteAlone;
      const double blackAlone;
      const double aIndianANativeAlone;
      const double asianAlone;
      const double hawaiianPIslanderAlone;
      const double twoOrMore;
      const double hispanicOrLatino;
      const double whiteNotHispOrLat;
      const int totalPopulation2020;

};
#endif
