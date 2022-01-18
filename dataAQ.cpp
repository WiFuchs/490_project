/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include <iostream>
#include <algorithm>

dataAQ::dataAQ() {}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateData(std::vector<shared_ptr<demogData>> theData) {
  //FILL in

  //groups counties into groups based on state
  map<std::string, vector< shared_ptr<demogData> > > CountyGroupings;

  for (const auto &obj : theData) {
    demogData county = *obj;
    std::string countyState = county.getState();
    CountyGroupings[countyState].push_back(make_shared<demogData>(county));
  }

  //creates a map of State object which are aggregates of counties in that state
  for (auto entry : CountyGroupings) {
    string state = entry.first;

    int whiteAlone = 0;
    int blackAlone = 0;
    int aIndianANativeAlone = 0;
    int asianAlone = 0;
    int hawaiianPIslanderAlone = 0;
    int twoOrMore = 0;
    int hispanicOrLatino = 0;
    int whiteNotHispOrLat = 0;
    int popOver65 = 0;
    int popUnder18 = 0;
    int popUnder5 = 0;
    int medianIncome = 0;
    int homeowners = 0;
    int personsPerHouse = 0;
    int veterans = 0;
    int highSchoolDegree = 0;
    int bachelorsDegree = 0;
    int foreignBorn = 0;
    int housingUnits = 0;
    int females = 0;
    int stateTotalPop2020 = 0;
    int counties = 0;

    for (auto elem : entry.second) {
      whiteAlone += elem->getEthnicity().getWhiteAloneCount();
      blackAlone += elem->getEthnicity().getBlackAloneCount();
      aIndianANativeAlone += elem->getEthnicity().getAIndianANativeAloneCount();
      asianAlone += elem->getEthnicity().getAsianAloneCount();
      hawaiianPIslanderAlone += elem->getEthnicity().getHawaiianPIslanderAlone();
      twoOrMore += elem->getEthnicity().getTwoOrMoreCount();
      hispanicOrLatino += elem->getEthnicity().getHispanicOrLatinoCount();
      whiteNotHispOrLat += elem->getEthnicity().getWhiteNotHispOrLatCount();

      popOver65 += elem->getPopOver65Count();
      popUnder18 += elem->getPopUnder18Count();
      popUnder5 += elem->getPopUnder5Count();
      stateTotalPop2020 += elem->getTotalPopulation2020();

      homeowners += elem->getHomeowners();
      veterans += elem->getVeteransCount();
      highSchoolDegree += elem->getHighSchoolDegreeCount();
      bachelorsDegree += elem->getBachelorsDegreeCount();
      foreignBorn += elem->getForeignBornCount();
      housingUnits += elem->getHousingUnits();
      females += elem->getFemalesCount();
      counties += 1;

      medianIncome += elem->getMedianIncome();
      personsPerHouse += elem->getPersonsPerHouse();
    }

    medianIncome = medianIncome /  counties;
    personsPerHouse = personsPerHouse / stateTotalPop2020;

    Ethnicity e = Ethnicity(whiteAlone, blackAlone, aIndianANativeAlone,
                            asianAlone, hawaiianPIslanderAlone, twoOrMore,
                            hispanicOrLatino, whiteNotHispOrLat, stateTotalPop2020);

    shared_ptr<demogState> s = make_shared<demogState>(state, popOver65, popUnder18,
                      popUnder5, stateTotalPop2020, e, medianIncome, homeowners,
                      personsPerHouse, veterans, highSchoolDegree,
                      bachelorsDegree, foreignBorn, housingUnits, females, counties);

    AggregateStateData[state] = s;
    std::cout << *s << endl;
  }
  CountyGroupings.clear(); //delete county groupings map
}

//return the name of the state with the largest population under age 5
string dataAQ::youngestPop() {
  string youngestPopState;
  double youngestPopNumber = 0;

  for (auto entry : AggregateStateData) {
    double popUnder5;
    //get popUnder5 of state
    popUnder5 = entry.second->getPopUnder5P();
    if (popUnder5 > youngestPopNumber) {
      youngestPopNumber = popUnder5;
      youngestPopState = entry.first;
    }
  }
  return youngestPopState;
}

//return the name of the state with the largest population under age 18
string dataAQ::teenPop()  {
  string highestTeenPopState;
  double highestTeenPop;

  for (auto entry : AggregateStateData) {
    double popUnder18;
    popUnder18 = entry.second->getPopUnder18P();
    if (popUnder18 > highestTeenPop) {
      highestTeenPop = popUnder18;
      highestTeenPopState = entry.first;
    }
  }
  return highestTeenPopState;
}

//return the name of the state with the largest population over age 65
string dataAQ::wisePop()  {
  string oldPopState;
  double oldPop;

  for (auto entry : AggregateStateData) {
    double popOver65;
    popOver65 = entry.second->getPopOver65P();
    if (popOver65 > oldPop) {
      oldPop = popOver65;
      oldPopState = entry.first;
    }
  }
  return oldPopState;
}

//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS() {
  string underServeState;
  double underServePop = 100;

  for (auto entry : AggregateStateData) {
    double popWithoutHS;
    popWithoutHS = entry.second->getHighSchoolDegreeP();
    if (popWithoutHS < underServePop) {
      underServePop = popWithoutHS;
      underServeState = entry.first;
    }
  }
  return underServeState;
}

//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads() {
  string highGradState;
  double highGradPop;

  for (auto entry : AggregateStateData) {
    double collegeGrads;
    collegeGrads = entry.second->getBachelorsDegreeP();
    if (collegeGrads > highGradPop) {
      highGradPop = collegeGrads;
      highGradState = entry.first;
    }
  }
  return highGradState;
}

//return the name of the state with the largest population below the poverty line
string dataAQ::belowPoverty() {
  string lowIncomeState;
  double lowIncome = 10000000000;

  for (auto entry : AggregateStateData) {
    double income;
    income = entry.second->getMedianIncome();
    if (income < lowIncome) {
      lowIncome = income ;
      lowIncomeState = entry.first;
    }
  }
  return lowIncomeState;
}
