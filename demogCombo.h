#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "Ethnicity.h"
#include "RegionData.h"
#include "demogData.h"

/*
  class to represent state data - fairly redundent at this point but will use
  inheritence later - FILL IN
*/

class demogCombo : public demogData, public RegionData {
  public:
//TODO fix the constructor calls in other files to instantiate as percents, not counts!!
      using getterFunc = double (demogCombo::*)() const;
      demogCombo(string inS, double in65, double in18,
       double in5, int totPop20, Ethnicity ethnicity,
       double mIncome, double homeowners, double pph, double vet,
       double highSchool, double bachelors, double foreign, double hUnits,
       double females, int counties) : demogData(inS, in65, in18, in5, totPop20, ethnicity, mIncome, homeowners, pph, vet, highSchool, bachelors, foreign, hUnits, females), RegionData(),
           counties(counties) {}


   int getCounties() const { return counties; }

  friend std::ostream& operator<<(std::ostream &out, const demogCombo &SD);

  private:

  const int counties;

};
#endif
