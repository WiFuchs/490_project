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

    double getWhiteAlone() const { return whiteAlone; }
    int getWhiteAloneCount() const {
      double count = totalPopulation2020 * (whiteAlone * .01);
      return round(count); }

    double getBlackAlone() const { return blackAlone; }
    int getBlackAloneCount() const {
      double count = totalPopulation2020 * (blackAlone * .01);
      return round(count); }

    double getAIndianANativeAlone() const { return aIndianANativeAlone; }
    int getAIndianANativeAloneCount() const {
      double count = totalPopulation2020 * (aIndianANativeAlone * .01);
      return round(count); }

    double getAsianAlone() const { return asianAlone; }
    int getAsianAloneCount() const {
      double count = totalPopulation2020 * (asianAlone * .01);
      return round(count); }

    double getHawaiianPIslanderAlone() const { return hawaiianPIslanderAlone; }
    int getHawaiianPIslanderAloneCount() const {
      double count = totalPopulation2020 * (hawaiianPIslanderAlone * .01);
      return round(count); }

    double getTwoOrMore() const { return twoOrMore; }
    int getTwoOrMoreCount() const {
      double count = totalPopulation2020 * (twoOrMore * .01);
      return round(count); }

    double getHispanicOrLatino() const { return hispanicOrLatino; }
    int getHispanicOrLatinoCount() const {
      double count = totalPopulation2020 * (hispanicOrLatino * .01);
      return round(count); }

    double getWhiteNotHispOrLat() const { return whiteNotHispOrLat; }
    int getWhiteNotHispOrLatCount() const {
      double count = totalPopulation2020 * (whiteNotHispOrLat * .01);
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
