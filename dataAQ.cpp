/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include <iostream>
#include <algorithm>
#include "psData.h"
#include "psEthnicity.h"

#include <vector>
#include <string>

dataAQ::dataAQ() {}

void dataAQ::createStatePoliceData(std::vector<shared_ptr<psData>> theData){
    map<std::string, vector< shared_ptr<psData> > > StateGroups;
    for (const auto &obj : theData) {
        psData shooting = *obj;
        std::string shootingState = shooting.getState();
        StateGroups[shootingState].push_back(make_shared<psData>(shooting));
    }

    for (auto entry : StateGroups) {
        string state = entry.first;
        int signsMentalIllness = 0;
        int unArmedCount = 0;
        int armedToy = 0;
        int bodyCam = 0;
        int cases = 0;

        int FirstNation = 0;
        int Asian = 0;
        int Black = 0;
        int Latinx = 0;
        //int HIPacificIsle = 0;
        //int MultiRace = 0;
        int White = 0;
        int WhiteNH = 0;
        int Other = 0; //what to do with this??
    //W: White, non-Hispanic B: Black, non-Hispanic A: Asian N: Native American H: Hispanic O: Other None: unknown

        for (auto elem : entry.second) {
            if (elem->getSignsMentalIllness() == "TRUE"){signsMentalIllness += 1;}
            if (elem->getArmed() == "unarmed" or elem->getArmed() == "" or elem->getArmed() == "undetermined"){unArmedCount += 1;}
            if (elem->getArmed() == "toy weapon"){armedToy += 1;}
            if (elem->getBodyCam() == "TRUE"){bodyCam += 1;}

            if (elem->getEthnicity() == "A"){Asian += 1;}
            if (elem->getEthnicity() == "H"){Latinx += 1;}
            if (elem->getEthnicity() == "B"){Black += 1;}
            if (elem->getEthnicity() == "W"){WhiteNH += 1;}
            if (elem->getEthnicity() == "N"){FirstNation += 1;}
            if (elem->getEthnicity() == "O" or elem->getEthnicity() == ""){Other += 1;}
            White = WhiteNH + Latinx;
            cases += 1;
        }
        psEthnicity eth = psEthnicity(WhiteNH, Black, Asian, FirstNation, Latinx, Other, cases); //fix other... new class?

        shared_ptr<psCombo> psC = make_shared<psCombo>(state, signsMentalIllness, unArmedCount, armedToy, bodyCam, cases, state, eth); //for p2 return state for region
        allStatePoliceData[state] = psC;

    }
    StateGroups.clear();
}

//bool psComparator(const pair<string, shared_ptr<psCombo>>& p1, const pair<string, shared_ptr<psCombo>>& p2) {
//    return (p1.second->getNumberOfCases() < p2.second->getNumberOfCases());
//}

//sort and report the top ten states in terms of number of police shootings
void dataAQ::reportTopTenStatesPS(){
    //FILL in
    //sort the data
    vector<shared_ptr<psCombo>> mapCopy;
    for( auto it = allStatePoliceData.begin(); it != allStatePoliceData.end(); it++){
        mapCopy.push_back(it->second);
    }
    std::sort(mapCopy.begin(), mapCopy.end(), [](auto ps1, auto ps2) -> bool {
        return ps1->getNumberOfCases() > ps2->getNumberOfCases(); });

    cout << "Top ten states sorted on number police shootings & the associated census data: " << endl;
    //print the mini report data
    int i = 0;
    for (const auto &obj : mapCopy) {
        cout << *obj << endl; //state string
        shared_ptr<demogState> state = this->getStateData(obj->getRegion()); // get a pointer to the relevant state

        cout << "Total population: " << state->getTotalPopulation2020()  << " Percentage home ownership: " << state->getHomeownersP() << endl;
        cout.precision(12);
        double percentPop = (obj->getNumberOfCases() / double(state->getTotalPopulation2020())) * 100;
        cout << "Police shooting incidents: " << obj->getNumberOfCases() << " Percent of population: " << percentPop << endl;
        cout.precision(2);
        i++;
        if (i > 9)
            break;
    }

    //print the full report data
    cout << "**Full listings for top 3 police shootings & the associated census data: ";

}


//string dataAQ::youngestPop() {
//    auto youngestPopComparator = createComparator(&demogState::getPopUnder5P);
//    shared_ptr<demogState> youngestPopState = max_element(AggregateStateData.begin(), AggregateStateData.end(), youngestPopComparator)->second;
//    return youngestPopState->getState();
//}

bool bachelorsComparator (const pair<string, shared_ptr<demogState>>& p1, const pair<string, shared_ptr<demogState>>& p2) {
    return (p1.second->getBachelorsDegree() < p2.second->getBachelorsDegree());
}

void dataAQ::reportBottomTenStatesHomeOwn(){
    //FILL in
    //std::sort(allStateData.begin(), allStateData.end(), bachelorsComparator);
    //std::sort(allStateData.begin(), allStateData.end(), []());
}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateData(std::vector<shared_ptr<demogData>> theData) {
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
    double personsPerHouse = 0;
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
    medianIncome = double(medianIncome) / double(counties);  //aggregate of county level average income / # counties

    personsPerHouse = double(personsPerHouse) / double(housingUnits);

    Ethnicity e = Ethnicity(whiteAlone, blackAlone, aIndianANativeAlone,
                            asianAlone, hawaiianPIslanderAlone, twoOrMore,
                            hispanicOrLatino, whiteNotHispOrLat, stateTotalPop2020);

    shared_ptr<demogState> s = make_shared<demogState>(state, popOver65, popUnder18,
                      popUnder5, stateTotalPop2020, e, medianIncome, homeowners,
                      personsPerHouse, veterans, highSchoolDegree,
                      bachelorsDegree, foreignBorn, housingUnits, females, counties);

    AggregateStateData[state] = s;
    //std::cout << *s << endl;
  }
  CountyGroupings.clear(); //delete county groupings map
}

//bool compareYoungest(const pair<string, shared_ptr<demogState>>& p1, const pair<string, shared_ptr<demogState>>& p2) {
//    return p1.second->getPopUnder5P() < p2.second->getPopUnder5P();
//}


//return the name of the state with the largest population under age 5
string dataAQ::youngestPop() {
    auto youngestPopComparator = createComparator(&demogState::getPopUnder5P);
  shared_ptr<demogState> youngestPopState = max_element(AggregateStateData.begin(), AggregateStateData.end(), youngestPopComparator)->second;

  return youngestPopState->getState();
}

string dataAQ::leastHomeowners() {
    auto leastHomeownersComparator = createComparator(&demogState::getHomeownersP);
    shared_ptr<demogState> leastHomeownersState = min_element(AggregateStateData.begin(), AggregateStateData.end(), leastHomeownersComparator)->second;

    return leastHomeownersState->getState();
}

string dataAQ::mostFemales() {
    auto femalesComparator = createComparator(&demogState::getFemalesP);
    shared_ptr<demogState> mostFemalesState = max_element(AggregateStateData.begin(), AggregateStateData.end(), femalesComparator)->second;

    return mostFemalesState->getState();
}

string dataAQ::mostVeterans() {
    auto veteransComparator = createComparator(&demogState::getVeteransP);
    shared_ptr<demogState> mostVeteransState = max_element(AggregateStateData.begin(), AggregateStateData.end(), veteransComparator)->second;

    return mostVeteransState->getState();
}

//return the name of the state with the largest population of foreign born people
string dataAQ::mostForBorn() {
    auto mostForBornComparator = [] (const pair<string, shared_ptr<demogState>>& p1, const pair<string, shared_ptr<demogState>>& p2) -> bool {
        return p1.second->getForeignBorn() < p2.second->getForeignBorn();
    };
    shared_ptr<demogState> mostForBornState = max_element(AggregateStateData.begin(), AggregateStateData.end(), mostForBornComparator)->second;

    return mostForBornState->getState();
}


// helper function to return a comparator for any getter in our demogState class
std::function<bool(const pair<std::string, shared_ptr<demogState>>, const pair<std::string, shared_ptr<demogState>>)> dataAQ::createComparator(demogState::getterFunc getter) {
    return [=] (const pair<string, shared_ptr<demogState>>& p1, const pair<string, shared_ptr<demogState>>& p2) -> bool {
        return (p1.second.get()->*getter)() < (p2.second.get()->*getter)();
    };
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
