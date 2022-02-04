#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "Ethnicity.h"

/*
  class to represent state data - fairly redundent at this point but will use
  inheritence later - FILL IN
*/

class demogState {
  public:

      using getterFunc = double (demogState::*)() const;
   demogState(string inS, int in65, int in18,
       int in5, int totPop20, Ethnicity ethnicity,
       int mIncome, int homeowners, double pph, int vet,
       int highSchool, int bachelors, int foreign, int hUnits,
       int females, int counties) :
           state(inS), popOver65(in65), popUnder18(in18),
           popUnder5(in5), totalPopulation2020(totPop20),
           ethnicity(ethnicity), medianIncome(mIncome), homeowners(homeowners),
           personsPerHouse(pph), veterans(vet), highSchoolDegree(highSchool),
           bachelorsDegree(bachelors), foreignBorn(foreign),
           housingUnits(hUnits), females(females), counties(counties) {}

   string getState() const { return state; }
   Ethnicity getEthnicity() const { return ethnicity; }

   //NOTE 1: these values are the counts from demogData NOT percentages

   //Population Info
   int getPopOver65() const { return popOver65; }
   double getPopOver65P() const { return (popOver65 / double(totalPopulation2020)) * 100; }

   int getPopUnder18() const { return popUnder18; }
   double getPopUnder18P() const { return (popUnder18 / double(totalPopulation2020)) * 100; }

   int getPopUnder5() const { return popUnder5; }
   double getPopUnder5P() const { return (popUnder5 / double(totalPopulation2020)) * 100; }

   int getTotalPopulation2020() const { return totalPopulation2020; }

   //Education Info
   int getHighSchoolDegree() const { return highSchoolDegree; }
   double getHighSchoolDegreeP() const { return (highSchoolDegree / double(totalPopulation2020)) * 100; }

   int getBachelorsDegree() const { return bachelorsDegree; }
   double getBachelorsDegreeP() const { return (bachelorsDegree / double(totalPopulation2020)) * 100; }

   //Housing info
   int getHomeowners() const { return homeowners; }
   double getHomeownersP() const { return (homeowners / double(totalPopulation2020)) * 100; }

   double getAvgPersonsPerHouse() const { return personsPerHouse; }
   double getPersonsPerHouseP() const { return (personsPerHouse / double(housingUnits)) * 100.0;}

   int getHousingUnits() const { return housingUnits; }

   //Miscellaneous Info
   int getForeignBorn() const { return foreignBorn; }
   double getForeignBornP() const { return (foreignBorn / double(totalPopulation2020)) * 100.0;}

   int getVeterans() const { return veterans; }
   double getVeteransP() const { return (veterans / double(totalPopulation2020)) * 100.0;}
   double getMedianIncome() const { return double(medianIncome); }
   int getFemales() const { return females; }
   double getFemalesP() const { return (females / double(totalPopulation2020)) * 100; }
   int getCounties() const { return counties; }

  friend std::ostream& operator<<(std::ostream &out, const demogState &SD);

  private:
  const string state;
  const int popOver65;
  const int popUnder18;
  const int popUnder5;
  const int totalPopulation2020;

  const Ethnicity ethnicity;
  const int medianIncome;
  const int homeowners;
  const double personsPerHouse;
  const int veterans;
  const int highSchoolDegree;
  const int bachelorsDegree;
  const int foreignBorn;
  const int housingUnits;
  const int females;
  const int counties;

};
#endif
