#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "demogState.h"

/*
  data aggregator and query for testing
*/
class dataAQ {
  public:
    dataAQ();

    /* necessary function to aggregate the data - this CAN and SHOULD vary per
        student - depends on how they map, etc. */
    void createStateData(std::vector<shared_ptr<demogData>> theData);

    //return the name of the state with the largest population under age 5
    string youngestPop();
    //return the name of the state with the largest population under age 18
    string teenPop();
    //return the name of the state with the largest population over age 65
    string wisePop();
    //return the name of the state with the largest population who did not finish high school
    string underServeHS();
    //return the name of the state with the largest population who completed college
    string collegeGrads();
    //return the name of the state with the largest population below the poverty line
    string belowPoverty();
    //return the name of the state with the largest population of foreign born people
    string mostForBorn();
    //return the name of the state with the fewest % homeowners
    string leastHomeowners();
    //return the name of the state with the highest % females
    string mostFemales();
    //return the name of the state with the highest % veterans
    string mostVeterans();

    //getter given a state name return a pointer to demogState data
    shared_ptr<demogState> getStateData(string stateName) {/*fix this*/

      auto it = AggregateStateData.find(stateName);
      if (it == AggregateStateData.end()){
        return nullptr;
      }
      else {
        return it->second;
      }
    }

    //must implement output per aggregate data
    friend std::ostream& operator<<(std::ostream &out, const dataAQ &allStateData);

    //core data private for dataAQ
    private:
      map<std::string, shared_ptr<demogState> > AggregateStateData;
      static std::function<bool(pair<std::string, shared_ptr<demogState>>, pair<std::string, shared_ptr<demogState>>)> createComparator(demogState::getterFunc getter);

};
#endif
