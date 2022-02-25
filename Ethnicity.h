#ifndef ETHNICITY_H
#define ETHNICITY_H

#include <iostream>
#include <math.h>

using namespace std;

class Ethnicity {
  public:

    Ethnicity(int white, int black, int IndianOrNative,
                int asian, int hawaiianPIslander, int twoOrMore,
                int hispOrLat, int whiteNotHOrL, int totPop20) :
        whiteAlone(white), blackAlone(black), aIndianANativeAlone(IndianOrNative),
        asianAlone(asian), hawaiianPIslanderAlone(hawaiianPIslander),
        twoOrMore(twoOrMore), hispanicOrLatino(hispOrLat),
        whiteNotHispOrLat(whiteNotHOrL), totalPopulation2020(totPop20), unspecified(0) {}

    Ethnicity(int white, int black, int IndianOrNative,
              int asian, int hispOrLat, int unspecified, int totPop20) :
                 whiteAlone(white ), blackAlone(black ), aIndianANativeAlone(IndianOrNative),
                 asianAlone(asian ), hawaiianPIslanderAlone(0),
                 twoOrMore(0), hispanicOrLatino(hispOrLat ), unspecified(unspecified ),
                 whiteNotHispOrLat(0), totalPopulation2020(totPop20) {}

    double getTotalPopulation2020() const { return totalPopulation2020; }
    double getWhiteAlone() const { return whiteAlone / double(totalPopulation2020); }
    int getWhiteAloneCount() const {
        return whiteAlone; }

    double getBlackAlone() const { return blackAlone / double(totalPopulation2020); }
    int getBlackAloneCount() const {
      return blackAlone; }

    double getAIndianANativeAlone() const { return aIndianANativeAlone / double(totalPopulation2020); }
    int getAIndianANativeAloneCount() const {
      return aIndianANativeAlone; }

    double getAsianAlone() const { return asianAlone / double(totalPopulation2020); }
    int getAsianAloneCount() const {
      return asianAlone; }

    double getHawaiianPIslanderAlone() const { return hawaiianPIslanderAlone / double(totalPopulation2020); }
    int getHawaiianPIslanderAloneCount() const {
      return hawaiianPIslanderAlone; }

    double getTwoOrMore() const { return twoOrMore / double(totalPopulation2020); }
    int getTwoOrMoreCount() const {
      return twoOrMore; }

    double getHispanicOrLatino() const { return hispanicOrLatino / double(totalPopulation2020); }
    int getHispanicOrLatinoCount() const {
      return hispanicOrLatino; }

    double getWhiteNotHispOrLat() const { return whiteNotHispOrLat/ double(totalPopulation2020); }
    int getWhiteNotHispOrLatCount() const {
      return whiteNotHispOrLat; }

    double getUnspecified() const {return unspecified / double(totalPopulation2020);}
    int getUnspecifiedCount() const {return unspecified;}

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
      int whiteAlone;
      int blackAlone;
      int aIndianANativeAlone;
      int asianAlone;
      int hawaiianPIslanderAlone;
      int twoOrMore;
      int unspecified;
      int hispanicOrLatino;
      int whiteNotHispOrLat;
      int totalPopulation2020;

};
#endif
