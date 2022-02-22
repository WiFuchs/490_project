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
        whiteAlone(white/ double(totPop20)), blackAlone(black/ double(totPop20)), aIndianANativeAlone(IndianOrNative/ double(totPop20)),
        asianAlone(asian/ double(totPop20)), hawaiianPIslanderAlone(hawaiianPIslander/ double(totPop20)),
        twoOrMore(twoOrMore/ double(totPop20)), hispanicOrLatino(hispOrLat/ double(totPop20)),
        whiteNotHispOrLat(whiteNotHOrL/ double(totPop20)), totalPopulation2020(totPop20), unspecified(0) {}

    Ethnicity(int white, int black, int IndianOrNative,
              int asian, int hispOrLat, int unspecified, int totPop20) :
                 whiteAlone(white / double(totPop20)), blackAlone(black / double(totPop20)), aIndianANativeAlone(IndianOrNative / double(totPop20)),
                 asianAlone(asian / double(totPop20)), hawaiianPIslanderAlone(0),
                 twoOrMore(0), hispanicOrLatino(hispOrLat / double(totPop20)), unspecified(unspecified / double(totPop20)),
                 whiteNotHispOrLat(0), totalPopulation2020(totPop20) {}

    double getTotalPopulation2020() const { return totalPopulation2020; }
    double getWhiteAlone() const { return whiteAlone; }
    int getWhiteAloneCount() const {
        double count = whiteAlone * totalPopulation2020;
        return round(count); }

    double getBlackAlone() const { return blackAlone; }
    int getBlackAloneCount() const {
      double count = blackAlone * totalPopulation2020;
      return round(count); }

    double getAIndianANativeAlone() const { return aIndianANativeAlone; }
    int getAIndianANativeAloneCount() const {
      double count = totalPopulation2020 * aIndianANativeAlone;
      return round(count); }

    double getAsianAlone() const { return asianAlone; }
    int getAsianAloneCount() const {
      double count = totalPopulation2020 * asianAlone;
      return round(count); }

    double getHawaiianPIslanderAlone() const { return hawaiianPIslanderAlone; }
    int getHawaiianPIslanderAloneCount() const {
      double count = totalPopulation2020 * hawaiianPIslanderAlone;
      return round(count); }

    double getTwoOrMore() const { return twoOrMore; }
    int getTwoOrMoreCount() const {
      double count = totalPopulation2020 * twoOrMore;
      return round(count); }

    double getHispanicOrLatino() const { return hispanicOrLatino; }
    int getHispanicOrLatinoCount() const {
      double count = totalPopulation2020 * hispanicOrLatino;
      return round(count); }

    double getWhiteNotHispOrLat() const { return whiteNotHispOrLat; }
    int getWhiteNotHispOrLatCount() const {
      double count = totalPopulation2020 * whiteNotHispOrLat;
      return round(count); }

    double getUnspecified() const {return unspecified;}
    int getUnspecifiedCount() const {return round(unspecified*totalPopulation2020);}

    friend std::ostream& operator<<(std::ostream &out, const Ethnicity &E);

    Ethnicity& operator+=(const Ethnicity& e) {
        whiteAlone += e.whiteAlone;
        blackAlone += e.blackAlone;
        aIndianANativeAlone += e.aIndianANativeAlone;
        asianAlone += e.asianAlone;
        hawaiianPIslanderAlone += e.hawaiianPIslanderAlone;
        twoOrMore += e.twoOrMore;
        unspecified += e.unspecified;
        hispanicOrLatino += e.hispanicOrLatino;
        whiteNotHispOrLat += e.whiteNotHispOrLat;
        totalPopulation2020 += e.totalPopulation2020;
        return *this;
    }




  private:
      double whiteAlone;
      double blackAlone;
      double aIndianANativeAlone;
      double asianAlone;
      double hawaiianPIslanderAlone;
      double twoOrMore;
      double unspecified;
      double hispanicOrLatino;
      double whiteNotHispOrLat;
      int totalPopulation2020;

};
#endif
