
#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
    cout << "Testing state data aggregation query..." << endl;

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics.csv", DEMOG);

    theAnswers.createStateData(theData);
    string youngestPop = theAnswers.youngestPop()->getState();
  	ASSERT_EQUALS("UT",youngestPop);
  	string bachelors = theAnswers.collegeGrads()->getState();
  	ASSERT_EQUALS("DC",bachelors);
    string forBorn = theAnswers.mostForBorn()->getState();
    ASSERT_EQUALS("CA", forBorn);
    string leastHomeowners = theAnswers.mostHomeowners()->getState();
    ASSERT_EQUALS("DC", leastHomeowners);
    string mostFemales = theAnswers.mostFemales()->getState();
    ASSERT_EQUALS("DC", mostFemales);
    string mostVeterans = theAnswers.mostVeterans()->getState();
    ASSERT_EQUALS("AK", mostVeterans);
  return 0;
}
