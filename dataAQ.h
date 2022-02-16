#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "demogCombo.h"
#include "psData.h"
#include "psCombo.h"
#include "State.h"

/*
  data aggregator and query for testing
*/
class dataAQ {
  public:
    dataAQ();

    /* necessary function to aggregate the data - this CAN and SHOULD vary per
        student - depends on how they map, etc. */
    void createStateData(const std::vector<shared_ptr<demogData>>& theData);
    void createStatePoliceData(const std::vector<shared_ptr<psData>>& theData);

    //return the name of the state with the largest population under age 5
    shared_ptr<demogCombo> youngestPop();
    //return the name of the state with the largest population under age 18
    shared_ptr<demogCombo> teenPop();
    //return the name of the state with the largest population over age 65
    shared_ptr<demogCombo> wisePop();
    //return the name of the state with the largest population who did not finish high school
    shared_ptr<demogCombo> underServeHS();
    //return the name of the state with the largest population who completed college
    shared_ptr<demogCombo> collegeGrads();
    //return the name of the state with the largest population below the poverty line
    shared_ptr<demogCombo> belowPoverty();
    //return the name of the state with the largest population of foreign born people
    shared_ptr<demogCombo> mostForBorn();
    //return the name of the state with the fewest % homeowners
    shared_ptr<demogCombo> mostHomeowners();
    //return the name of the state with the highest % females
    shared_ptr<demogCombo> mostFemales();
    //return the name of the state with the highest % veterans
    shared_ptr<demogCombo> mostVeterans();

    vector<shared_ptr<State>> getAllStateData(){ return allStates; }

    //getter given a state name return a pointer to demogCombo data
    shared_ptr<State> getStateData(string stateName) {/*fix this*/

      auto it = allStatesMap.find(stateName);
      if (it == allStatesMap.end()){
          return nullptr;
      }
      else {
        return it->second;
      }
    }

    //sort and report the top ten states in terms of number of police shootings
    void reportTopTenStatesPS();
    void reportBottomTenStatesHomeOwn();


    template<typename Getter>
    vector<shared_ptr<State>> genericDemogMaxN(Getter getter, unsigned long n = 1) {
        // sort the list
        sort(allStates.begin(), allStates.end(), createDemogGTComparator<Getter>(getter));

        // copy first n elements
        auto end = next(allStates.begin(), min(n, allStates.size()));
        return {allStates.begin(), end};
    }

    template<typename Getter>
    vector<shared_ptr<State>> genericDemogMinN(Getter getter, unsigned long n = 1) {
        // sort the list
        sort(allStates.begin(), allStates.end(), createDemogLTComparator<Getter>(getter));

        // copy first n elements
        auto end = next(allStates.begin(), min(n, allStates.size()));
        return {allStates.begin(), end};
    }

    template<typename Getter>
    vector<shared_ptr<State>> genericPSMaxN(Getter getter, unsigned long n = 1) {
        // sort the list
        sort(allStates.begin(), allStates.end(), createPSComparator<Getter>(getter));

        // copy first n elements
        auto end = next(allStates.begin(), min(n, allStates.size()));
        return {allStates.begin(), end};
    }


    //must implement output per aggregate data
    friend std::ostream& operator<<(std::ostream &out, const dataAQ &allStateData);

    //core data private for dataAQ
    private:
        vector<shared_ptr<State>> allStates;
        map<string, shared_ptr<State>> allStatesMap;

      template <typename Getter>
      static function<bool(shared_ptr<State>, shared_ptr<State>)> createDemogGTComparator(Getter getter) {
          return [=] (const shared_ptr<State>& p1, const shared_ptr<State>& p2) -> bool {
              return (p1->getDemoData().get()->*getter)() > (p2->getDemoData().get()->*getter)();
          };
      }

      template <typename Getter>
      static function<bool(shared_ptr<State>, shared_ptr<State>)> createDemogLTComparator(Getter getter) {
          return [=] (const shared_ptr<State>& p1, const shared_ptr<State>& p2) -> bool {
              return (p1->getDemoData().get()->*getter)() < (p2->getDemoData().get()->*getter)();
          };
      }
      template <typename Getter>
      static function<bool(shared_ptr<State>, shared_ptr<State>)> createPSComparator(Getter getter) {
          return [=] (const shared_ptr<State>& p1, const shared_ptr<State>& p2) -> bool {
              return (p1->getPSData().get()->*getter)() > (p2->getPSData().get()->*getter)();
          };
      }

};
#endif
