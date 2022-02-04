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
        allPSData.push_back(psC);
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

    vector<shared_ptr<psCombo>> allPSData;
    for( auto it = allStatePoliceData.begin(); it != allStatePoliceData.end(); it++){
        allPSData.push_back(it->second);}

    std::sort(allPSData.begin(), allPSData.end(), [](auto ps1, auto ps2) -> bool {
        return ps1->getNumberOfCases() > ps2->getNumberOfCases(); });

    cout << "Top ten states sorted on number police shootings & the associated census data: " << endl;
    //print the mini report data
    int i = 0;
    for (const auto &obj : allPSData ) {
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

      homeowners += elem->getHomeownersCount();
      veterans += elem->getVeteransCount();
      highSchoolDegree += elem->getHighSchoolDegreeCount();
      bachelorsDegree += elem->getBachelorsDegreeCount();
      foreignBorn += elem->getForeignBornCount();
      housingUnits += elem->getHousingUnits();
      females += elem->getFemalesCount();
      counties += 1;

      int old_income = medianIncome;
      medianIncome += elem->getMedianIncome() * elem->getHousingUnits();
      if (old_income > medianIncome) {
          cout << "whoops: " << elem->getName() << ": " << elem->getHousingUnits() << " : " << elem->getMedianIncome() << endl;
      }
      personsPerHouse += elem->getPersonsPerHouse();
    }
    medianIncome = double(medianIncome) / double(housingUnits);  //aggregate of county level average income / # counties
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

  for(auto & it : AggregateStateData){
      allStates.push_back(it.second);
  }
  CountyGroupings.clear(); //delete county groupings map
}


//TODO can these be simplified further into one max/min that takes in the getter and returns the max/min element from the state data collection?
shared_ptr<demogState> dataAQ::youngestPop() {
    return max_element(AggregateStateData.begin(), AggregateStateData.end(), createComparator(&demogState::getPopUnder5P))->second;

}

shared_ptr<demogState> dataAQ::mostHomeowners() {
    return max_element(AggregateStateData.begin(), AggregateStateData.end(), createComparator(&demogState::getHomeownersP))->second;

}

shared_ptr<demogState> dataAQ::mostFemales() {
    return max_element(AggregateStateData.begin(), AggregateStateData.end(), createComparator(&demogState::getFemalesP))->second;

}

shared_ptr<demogState> dataAQ::mostVeterans() {
    return max_element(AggregateStateData.begin(), AggregateStateData.end(), createComparator(&demogState::getVeteransP))->second;

}

shared_ptr<demogState> dataAQ::maxQuery(demogState::getterFunc getter) {
    return max_element(AggregateStateData.begin(), AggregateStateData.end(), createComparator(getter))->second;
}

//return the name of the state with the largest population of foreign born people
shared_ptr<demogState> dataAQ::mostForBorn() {
    return max_element(AggregateStateData.begin(), AggregateStateData.end(), createComparator(&demogState::getForeignBornP))->second;
}


// helper function to return a comparator for any getter in our demogState class
std::function<bool(const pair<std::string, shared_ptr<demogState>>, const pair<std::string, shared_ptr<demogState>>)> dataAQ::createComparator(demogState::getterFunc getter) {
    return [=] (const pair<string, shared_ptr<demogState>>& p1, const pair<string, shared_ptr<demogState>>& p2) -> bool {
        return (p1.second.get()->*getter)() < (p2.second.get()->*getter)();
    };
}


//return the name of the state with the largest population under age 18
shared_ptr<demogState> dataAQ::teenPop()  {
    return max_element(AggregateStateData.begin(), AggregateStateData.end(), createComparator(&demogState::getPopUnder18P))->second;
}

//return the name of the state with the largest population who did receive bachelors degree and up
shared_ptr<demogState> dataAQ::collegeGrads() {
    return max_element(AggregateStateData.begin(), AggregateStateData.end(), createComparator(&demogState::getBachelorsDegreeP))->second;

}
