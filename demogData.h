#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include<iostream>
#include <math.h>
#include "Ethnicity.h"
#include "regionData.h"

using namespace std;

/*
  class to represent county demographic data
  from CORGIS - fill in with any data we agree as a class we want to include
*/
class demogData : public regionData, public std::enable_shared_from_this<demogData> {
  public:
    demogData(string inN, string inS, double in65, double in18,
        double in5, int totPop20, Ethnicity ethnicity,
        double mIncome, double homeowners, double pph, double vet,
        double highSchool, double bachelors, double foreign, int hUnits,
        double females) : regionData(),
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), totalPopulation2020(totPop20),
            ethnicity(ethnicity), medianIncome(mIncome), homeOwnershipRate(homeowners),
            personsPerHouse(pph), veterans(vet), highSchoolDegree(highSchool),
            bachelorsDegree(bachelors), foreignBorn(foreign),
            housingUnits(hUnits), females(females) {}

    string getName() const { return name; }

    Ethnicity getEthnicity() const { return ethnicity; }

    //Population Info
    double getPopOver65() const { return popOver65; }
    int getPopOver65Count() const {
      double count = totalPopulation2020 * popOver65;
      return round(count); }
    double getPopUnder18() const { return popUnder18; }
    int getPopUnder18Count() const {
      double count = totalPopulation2020 * popUnder18;
      return round(count); }
    double getPopUnder5() const { return popUnder5; }
    int getPopUnder5Count() const {
      double count = totalPopulation2020 * popUnder5;
      return round(count); }
    int getTotalPopulation2020() const { return totalPopulation2020; }

    //Education Info
    double getHighSchoolDegree() const { return highSchoolDegree; }
    int getHighSchoolDegreeCount() const {
      double count = totalPopulation2020 * highSchoolDegree;
      return round(count); }

    double getBachelorsDegree() const { return bachelorsDegree * 100; } //*100 fixed std dev Y; 23% instead of .23 etc...
    int getBachelorsDegreeCount() const {
      double count = totalPopulation2020 * bachelorsDegree;
      return round(count); }

    //Housing info
    double getHomeOwnershipRate() const {
        if(0 > homeOwnershipRate) {
            cout << state << ": " << homeOwnershipRate << endl;
        }
        assert(0 <= homeOwnershipRate);
        assert(1 >= homeOwnershipRate);
        return homeOwnershipRate; }

    int getHomeownersCount() const {
      double count = housingUnits * homeOwnershipRate;
      return round(count); }
    string getState() const { return state; }
    double getPersonsPerHouse() const { return personsPerHouse; }
    int getHousingUnits() const { return housingUnits; }

    //Miscellaneous Info
    double getForeignBorn() const { return foreignBorn; }
    int getForeignBornCount() const {
      double count = totalPopulation2020 * foreignBorn;
      return round(count); }

    double getVeterans() const { return veterans; }
    int getVeteransCount() const {
        return round(veterans * totalPopulation2020); }
    double getMedianIncome() const { return medianIncome; }

    double getFemales() const { return females; }
    int getFemalesCount() const {
      double count = totalPopulation2020 * females;
      return round(count);}
    double getAvgPersonsPerHouse() const {return totalPopulation2020 / housingUnits; }

   friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

   void accept(class Visitor &v) override {
       v.visit(shared_from_this());
   }

   void print() const {
       cout << *this << endl;
   }

protected:
    const string name;
    const string state;
    double popOver65;
    double popUnder18;
    double popUnder5;
    int totalPopulation2020;

    Ethnicity ethnicity;
    double medianIncome;
    double homeOwnershipRate;
    double personsPerHouse;
    double veterans;
    double highSchoolDegree;
    double bachelorsDegree;
    double foreignBorn;
    int housingUnits;
    double females;

};
#endif
