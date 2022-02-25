#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "Ethnicity.h"
#include "regionData.h"
#include "demogData.h"

/*
  class to represent state data - fairly redundent at this point but will use
  inheritence later - FILL IN
*/

class demogCombo : public demogData {
  public:
//TODO fix the constructor calls in other files to instantiate as percents, not counts!!
      demogCombo(string inS, double in65, double in18,
       double in5, int totPop20, Ethnicity ethnicity,
       double mIncome, double homeowners, double pph, double vet,
       double highSchool, double bachelors, double foreign, double hUnits,
       double females, int counties) : demogData(inS, inS, in65, in18, in5, totPop20, ethnicity, mIncome, homeowners, pph, vet, highSchool, bachelors, foreign, hUnits, females),
           counties(counties) {}


   int getCounties() const { return counties; }

   demogCombo& operator+=(const demogData& b) {
       counties += 1;

       // get counts
       int newPopOver65Count = getPopOver65Count() + b.getPopOver65Count();
       int newPopUnder18Count = getPopUnder18Count() + b.getPopUnder18Count();
       int newPopUnder5Count = getPopUnder5Count() + b.getPopUnder5Count();
       int totalPop = getTotalPopulation2020() + b.getTotalPopulation2020();
       int newHomeownersCount = getHomeownersCount() + b.getHomeownersCount();
       int newVeteransCount = getVeteransCount() + b.getVeteransCount();
       int newHSDegreeCount = getHighSchoolDegreeCount() + b.getHighSchoolDegreeCount();
       int newBachelorsDegreeCount = getBachelorsDegreeCount() + b.getBachelorsDegreeCount();
       int newForeignBornCount = getForeignBornCount() + b.getForeignBornCount();
       int newFemalesCount = getFemalesCount() + b.getFemalesCount();

       // convert to decimals
       popOver65 = double(newPopOver65Count) / totalPop;
       popUnder18 = double(newPopUnder18Count) / totalPop;
       popUnder5 = double(newPopUnder5Count) / totalPop;
       veterans = double(newVeteransCount) / totalPop;
       highSchoolDegree = double(newHSDegreeCount) / totalPop;
       bachelorsDegree = double(newBachelorsDegreeCount) / totalPop;
       foreignBorn = double(newForeignBornCount) / totalPop;
       females = double(newFemalesCount) / totalPop;
       homeowners = double(newHomeownersCount) / totalPop;

       // unique
       totalPopulation2020 = totalPop;
       medianIncome = (medianIncome * getTotalPopulation2020() + b.getMedianIncome() * b.getTotalPopulation2020()) / totalPop;
       personsPerHouse = (personsPerHouse * getTotalPopulation2020() + b.getPersonsPerHouse() * b.getTotalPopulation2020()) / totalPop;
       housingUnits = housingUnits + b.getHousingUnits();
       ethnicity += b.getEthnicity();

       return *this;
   }

  friend std::ostream& operator<<(std::ostream &out, const demogCombo &SD);

  private:

  int counties;

};
#endif
