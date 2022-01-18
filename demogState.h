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
   //FILL IN
   demogState(string inS, double in65, double in18,
       double in5, int totPop20, Ethnicity ethnicity,
       double mIncome, double homeowners, double pph, double vet,
       double highSchool, double bachelors, double foreign, double hUnits,
       double females, int counties) :
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
   double getPopOver65() const { return popOver65; }
   double getPopOver65P() const { return (popOver65 / totalPopulation2020) * 100; }

   double getPopUnder18() const { return popUnder18; }
   double getPopUnder18P() const { return (popUnder18 / totalPopulation2020) * 100; }

   double getPopUnder5() const { return popUnder5; }
   double getPopUnder5P() const { return (popUnder5 / totalPopulation2020) * 100; }

   int getTotalPopulation2020() const { return totalPopulation2020; }

   //Education Info
   double getHighSchoolDegree() const { return highSchoolDegree; }
   double getHighSchoolDegreeP() const { return (highSchoolDegree / totalPopulation2020) * 100; }

   double getBachelorsDegree() const { return bachelorsDegree; }
   double getBachelorsDegreeP() const { return (bachelorsDegree / totalPopulation2020) * 100; }

   //Housing info
   double getHomeowners() const { return homeowners; }
   double getHomeownersP() const { return (homeowners / totalPopulation2020) * 100; }
   double getPersonsPerHouse() const { return personsPerHouse; }
   double getHousingUnits() const { return housingUnits; }

   //Miscellaneous Info
   double getForeignBorn() const { return foreignBorn; }
   double getVeterans() const { return veterans; }
   double getMedianIncome() const { return medianIncome; }
   double getFemales() const { return females; }
   double getFemalesP() const { return (females / totalPopulation2020) * 100; }
   int getCounties() const { return counties; }

  friend std::ostream& operator<<(std::ostream &out, const demogState &SD);

  private:
	//DATA here
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
  const int counties;

};
#endif
