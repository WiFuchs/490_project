#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include<iostream>
#include <math.h>
#include "Ethnicity.h"

using namespace std;

/*
  class to represent county demographic data
  from CORGIS - fill in with any data we agree as a class we want to include
*/
class demogData {
  public:
    typedef double(demogData::*get_percent_function)(void) const;

    demogData(string inN, string inS, double in65, double in18,
        double in5, int totPop20, Ethnicity ethnicity,
        double mIncome, double homeowners, double pph, double vet,
        double highSchool, double bachelors, double foreign, double hUnits,
        double females) :
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), totalPopulation2020(totPop20),
            ethnicity(ethnicity), medianIncome(mIncome), homeowners(homeowners),
            personsPerHouse(pph), veterans(vet), highSchoolDegree(highSchool),
            bachelorsDegree(bachelors), foreignBorn(foreign),
            housingUnits(hUnits), females(females) {}

    string getName() const { return name; }
    string getState() const { return state; }

    Ethnicity getEthnicity() const { return ethnicity; }

    //Population Info
    double getPopOver65() const { return popOver65; }
    int getPopOver65Count() const {
      double count = totalPopulation2020 * (popOver65 * .01);
      return round(count); }
    double getPopUnder18() const { return popUnder18; }
    int getPopUnder18Count() const {
      double count = totalPopulation2020 * (popUnder18 * .01);
      return round(count); }
    double getPopUnder5() const { return popUnder5; }
    int getPopUnder5Count() const {
      double count = totalPopulation2020 * (popUnder5 * .01);
      return round(count); }
    int getTotalPopulation2020() const { return totalPopulation2020; }

    //Education Info
    double getHighSchoolDegree() const { return highSchoolDegree; }
    int getHighSchoolDegreeCount() const {
      double count = totalPopulation2020 * (highSchoolDegree * .01);
      return round(count); }

    double getBachelorsDegree() const { return bachelorsDegree; }
    int getBachelorsDegreeCount() const {
      double count = totalPopulation2020 * (bachelorsDegree * .01);
      return round(count); }

    //Housing info
    double getHomeowners() const { return homeowners; }
    int getHomeownersCount() const {
      double count = totalPopulation2020 * (homeowners * .01);
      return round(count); }

    double getPersonsPerHouse() const { return personsPerHouse; }
    double getHousingUnits() const { return housingUnits; }

    //Miscellaneous Info
    double getForeignBorn() const { return foreignBorn; }
    int getForeignBornCount() const {
      double count = totalPopulation2020 * (foreignBorn * .01);
      return round(count); }

    double getVeterans() const { return (veterans / totalPopulation2020) * 100; }
    int getVeteransCount() const { return veterans; }
    double getMedianIncome() const { return medianIncome; }

    double getFemales() const { return females; }
    int getFemalesCount() const {
      double count = totalPopulation2020 * (females * .01);
      return round(count);}

   friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

private:
    const string name;
    const string state;
    const double popOver65;
    const double popUnder18;
    const double popUnder5;
    const int totalPopulation2020;

    const Ethnicity ethnicity;
    const double medianIncome;
    const double homeowners;
    const double personsPerHouse;
    const double veterans;
    const double highSchoolDegree;
    const double bachelorsDegree;
    const double foreignBorn;
    const double housingUnits;
    const double females;

};
#endif
