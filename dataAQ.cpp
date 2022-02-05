/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include <iostream>
#include <algorithm>
#include "psData.h"

#include <vector>
#include <string>

dataAQ::dataAQ() {}

void dataAQ::createStatePoliceData(const std::vector<shared_ptr<psData>>& theData){
    map<std::string, vector< shared_ptr<psData> > > StateGroups;
    for (const auto &obj : theData) {
        psData shooting = *obj;
        std::string shootingState = shooting.getState();
        StateGroups[shootingState].push_back(make_shared<psData>(shooting));
    }

    for (const auto& entry : StateGroups) {
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
        int WhiteNH = 0;
        int Unspecified = 0; //what to do with this??
    //W: White, non-Hispanic B: Black, non-Hispanic A: Asian N: Native American H: Hispanic O: Unspecified None: unknown

        for (auto elem : entry.second) {
            if (elem->getSignsMentalIllness() == "TRUE"){signsMentalIllness += 1;}
            if (elem->getArmed() == "unarmed" or elem->getArmed() == "" or elem->getArmed() == "undetermined"){unArmedCount += 1;}
            if (elem->getArmed().find("toy") != string::npos){armedToy += 1;}
            if (elem->getBodyCam() == "TRUE"){bodyCam += 1;}

            if (elem->getEthnicity() == "A"){Asian += 1;}
            if (elem->getEthnicity() == "H"){Latinx += 1;}
            if (elem->getEthnicity() == "B"){Black += 1;}
            if (elem->getEthnicity() == "W"){WhiteNH += 1;}
            if (elem->getEthnicity() == "N"){FirstNation += 1;}
            if (elem->getEthnicity() == "O" or elem->getEthnicity() == ""){ Unspecified += 1;}
            cases += 1;
        }
        Ethnicity eth = Ethnicity(WhiteNH, Black, FirstNation, Asian, Latinx, Unspecified, cases);
        shared_ptr<psCombo> psC = make_shared<psCombo>(state, signsMentalIllness, unArmedCount, armedToy, bodyCam, cases, state, eth); //for p2 return state for region

        shared_ptr<State> curState = getStateData(state);
        if (curState == nullptr) {
            curState = make_shared<State>(state);
            allStatesMap[state] = curState;
            allStates.push_back(curState);
        }
        curState->setPSData(psC);
    }

    StateGroups.clear();
}

//bool psComparator(const pair<string, shared_ptr<psCombo>>& p1, const pair<string, shared_ptr<psCombo>>& p2) {
//    return (p1.second->getNumberOfCases() < p2.second->getNumberOfCases());
//}

//sort and report the top ten states in terms of number of police shootings
void dataAQ::reportTopTenStatesPS(){
//    //sort the data
//    std::sort(allStates.begin(), allStates.end(), [](const shared_ptr<State>& ps1, const shared_ptr<State>& ps2) -> bool {
//        return ps1->getPSData()->getNumberOfCases() > ps2->getPSData()->getNumberOfCases(); });

    vector<shared_ptr<State>> top10PSStates = genericPSMaxN(&psCombo::getNumberOfCases, 10);

    cout << "Top ten states sorted on number police shootings & the associated census data: " << endl;
    //print the mini report data
    for (const auto &state : top10PSStates ) {
        shared_ptr<psCombo> obj = state->getPSData();
        cout << state->getName() << endl;
        shared_ptr<demogState> demoState = state->getDemoData(); // get a pointer to the relevant state
        cout << "Total population: " << demoState->getTotalPopulation2020()  << " Percentage home ownership: " << demoState->getHomeownersP() << endl;
        cout.precision(12);
        double percentPop = (obj->getNumberOfCases() / double(demoState->getTotalPopulation2020())) * 100;
        cout << "Police shooting incidents: " << obj->getNumberOfCases() << " Percent of population: " << percentPop << endl;
        cout.precision(2);
    }

    //print the full report data
    cout << "**Full listings for top 3 police shootings & the associated census data: ";
    for (int i=0; i < 3; i++) {
        auto state = top10PSStates[i];
        cout << *(state->getDemoData()) << endl;
        cout << *(state->getPSData()) << endl;
    }
}

void dataAQ::reportBottomTenStatesHomeOwn(){
    //    //sort the data
    //    std::sort(allStates.begin(), allStates.end(), [](const shared_ptr<State>& ps1, const shared_ptr<State>& ps2) -> bool {
    //        return ps1->getPSData()->getNumberOfCases() > ps2->getPSData()->getNumberOfCases(); });

    vector<shared_ptr<State>> bottom10Homeown = genericDemogMinN(&demogState::getHomeownersP, 10);

    cout << "Bottom ten states sorted on % homeownership & the associated census data: " << endl;
    //print the mini report data
    for (const auto &state : bottom10Homeown) {
        shared_ptr<psCombo> obj = state->getPSData();
        cout << state->getName() << endl;
        shared_ptr<demogState> demoState = state->getDemoData(); // get a pointer to the relevant state
        cout << "Total population: " << demoState->getTotalPopulation2020()  << " Percentage home ownership: " << demoState->getHomeownersP() << endl;
        cout.precision(12);
        double percentPop = (obj->getNumberOfCases() / double(demoState->getTotalPopulation2020())) * 100;
        cout << "Police shooting incidents: " << obj->getNumberOfCases() << " Percent of population: " << percentPop << endl;
        cout.precision(2);
    }

    //print the full report data
    cout << "**Full listings for bottom 3 homeownership states & the associated census data: ";
    for (int i=0; i < 3; i++) {
        auto state = bottom10Homeown[i];
        cout << *(state->getDemoData()) << endl;
        cout << *(state->getPSData()) << endl;
    }
}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateData(const std::vector<shared_ptr<demogData>>& theData) {
  //groups counties into groups based on state
  map<std::string, vector< shared_ptr<demogData> > > CountyGroupings;

  for (const auto &obj : theData) {
    demogData county = *obj;
    std::string countyState = county.getState();
    CountyGroupings[countyState].push_back(make_shared<demogData>(county));
  }

  //creates a map of State object which are aggregates of counties in that state
  for (const auto& entry : CountyGroupings) {
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
    long medianIncome = 0;
    double homeowners = 0;
    double personsPerHouse = 0;
    int veterans = 0;
    int highSchoolDegree = 0;
    int bachelorsDegree = 0;
    int foreignBorn = 0;
    long housingUnits = 0;
    int females = 0;
    int stateTotalPop2020 = 0;
    int counties = 0;

    for (const auto& elem : entry.second) {
      whiteAlone += elem->getEthnicity().getWhiteAloneCount();
      blackAlone += elem->getEthnicity().getBlackAloneCount();
      aIndianANativeAlone += elem->getEthnicity().getAIndianANativeAloneCount();
      asianAlone += elem->getEthnicity().getAsianAloneCount();
      hawaiianPIslanderAlone += elem->getEthnicity().getHawaiianPIslanderAloneCount();
      twoOrMore += elem->getEthnicity().getTwoOrMoreCount();
      hispanicOrLatino += elem->getEthnicity().getHispanicOrLatinoCount();
      whiteNotHispOrLat += elem->getEthnicity().getWhiteNotHispOrLatCount();

      popOver65 += elem->getPopOver65Count();
      popUnder18 += elem->getPopUnder18Count();
      popUnder5 += elem->getPopUnder5Count();
      stateTotalPop2020 += elem->getTotalPopulation2020();

      homeowners += elem->getHomeownersCount();
      veterans += elem->getVeteransCount();
      highSchoolDegree += elem->getHighSchoolDegreeCount();
      bachelorsDegree += elem->getBachelorsDegreeCount();
      foreignBorn += elem->getForeignBornCount();
      housingUnits += elem->getHousingUnits();
      females += elem->getFemalesCount();
      counties += 1;

      medianIncome += elem->getMedianIncome() * elem->getHousingUnits();
      personsPerHouse += elem->getPersonsPerHouse();
    }
    medianIncome = medianIncome / double(housingUnits);  //aggregate of county level average income / # counties
    personsPerHouse = double(personsPerHouse) / double(housingUnits);

    Ethnicity e = Ethnicity(whiteAlone, blackAlone, aIndianANativeAlone,
                            asianAlone, hawaiianPIslanderAlone, twoOrMore,
                            hispanicOrLatino, whiteNotHispOrLat, stateTotalPop2020);
    shared_ptr<demogState> s = make_shared<demogState>(state, popOver65, popUnder18,
                      popUnder5, stateTotalPop2020, e, medianIncome, homeowners,
                      personsPerHouse, veterans, highSchoolDegree,
                      bachelorsDegree, foreignBorn, housingUnits, females, counties);
    shared_ptr<State> curState = getStateData(state);
    if (curState == nullptr) {
        curState = make_shared<State>(state);
        allStatesMap[state] = curState;
        allStates.push_back(curState);
    }
    curState->setDemoData(s);
  }

  CountyGroupings.clear(); //delete county groupings map
}


shared_ptr<demogState> dataAQ::youngestPop() {
    return genericDemogMaxN(&demogState::getPopUnder5P)[0]->getDemoData();
}

shared_ptr<demogState> dataAQ::mostHomeowners() {
    return genericDemogMaxN(&demogState::getHomeownersP)[0]->getDemoData();

}

shared_ptr<demogState> dataAQ::mostFemales() {
    return genericDemogMaxN(&demogState::getFemalesP)[0]->getDemoData();

}

shared_ptr<demogState> dataAQ::mostVeterans() {
    return genericDemogMaxN(&demogState::getVeteransP)[0]->getDemoData();

}

//return the name of the state with the largest population of foreign born people
shared_ptr<demogState> dataAQ::mostForBorn() {
    return genericDemogMaxN(&demogState::getForeignBornP)[0]->getDemoData();
}

//return the name of the state with the largest population who did receive bachelors degree and up
shared_ptr<demogState> dataAQ::collegeGrads() {
    return genericDemogMaxN(&demogState::getBachelorsDegreeP)[0]->getDemoData();
}
