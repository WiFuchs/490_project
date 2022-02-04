#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "demogState.h"
#include "psData.h"
#include "psCombo.h"

/*
  data aggregator and query for testing
*/
class dataAQ {
  public:
    dataAQ();

    /* necessary function to aggregate the data - this CAN and SHOULD vary per
        student - depends on how they map, etc. */
    void createStateData(std::vector<shared_ptr<demogData>> theData);
    void createStatePoliceData(std::vector<shared_ptr<psData>> theData);

    //return the name of the state with the largest population under age 5
    shared_ptr<demogState> youngestPop();
    //return the name of the state with the largest population under age 18
    shared_ptr<demogState> teenPop();
    //return the name of the state with the largest population over age 65
    shared_ptr<demogState> wisePop();
    //return the name of the state with the largest population who did not finish high school
    shared_ptr<demogState> underServeHS();
    //return the name of the state with the largest population who completed college
    shared_ptr<demogState> collegeGrads();
    //return the name of the state with the largest population below the poverty line
    shared_ptr<demogState> belowPoverty();
    //return the name of the state with the largest population of foreign born people
    shared_ptr<demogState> mostForBorn();
    //return the name of the state with the fewest % homeowners
    shared_ptr<demogState> mostHomeowners();
    //return the name of the state with the highest % females
    shared_ptr<demogState> mostFemales();
    //return the name of the state with the highest % veterans
    shared_ptr<demogState> mostVeterans();

    //general max query
    shared_ptr<demogState> maxQuery(demogState::getterFunc getter);
    template<typename T>
    shared_ptr<psCombo> maxPSQuery(T getter) {
        return max_element(allStatePoliceData.begin(), allStatePoliceData.end(), createGenericComparator<psCombo, T>(getter))->second;
    }

    vector<shared_ptr<demogState>> getAllStateData(){ return allStates; }
    vector<shared_ptr<psCombo>> getAllPSData(){ return allPSData; }

    //getter given a state name return a pointer to demogState data
    shared_ptr<demogState> getStateData(string stateName) {/*fix this*/

      auto it = AggregateStateData.find(stateName);
      if (it == AggregateStateData.end()){
          cout << "HERE" << stateName << endl;
          return nullptr;
      }
      else {
        return it->second;
      }
    }

    //sort and report the top ten states in terms of number of police shootings
    void reportTopTenStatesPS();
    void reportBottomTenStatesHomeOwn();

    //shared_ptr<demogState> getStateData(string stateName) { return allStateData[stateName]; }
    shared_ptr<psCombo> getStatePoliceData(string stateName) { return allStatePoliceData[stateName]; }

    //must implement output per aggregate data
    friend std::ostream& operator<<(std::ostream &out, const dataAQ &allStateData);

    //core data private for dataAQ
    private:
        vector<shared_ptr<demogState>> allStates;
        vector<shared_ptr<psCombo>> allPSData;
      map<std::string, shared_ptr<demogState> > AggregateStateData;
      template <typename T, typename Getter>
      static function<bool(pair<string, shared_ptr<T>>, pair<string, shared_ptr<T>>)> createGenericComparator(Getter getter) {
          return [=] (const pair<string, shared_ptr<T>>& p1, const pair<string, shared_ptr<T>>& p2) -> bool {
              return (p1.second.get()->*getter)() < (p2.second.get()->*getter)();
          };
      }

      static std::function<bool(pair<std::string, shared_ptr<demogState>>, pair<std::string, shared_ptr<demogState>>)> createComparator(demogState::getterFunc getter);

      //std::map<string, shared_ptr<demogState>> allStateData;
      std::map<string, shared_ptr<psCombo>> allStatePoliceData;
};
#endif
