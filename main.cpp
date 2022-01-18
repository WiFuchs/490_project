#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"

using namespace std;

int main() {

    dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics.csv", DEMOG);

    //debug print out - uncomment if you want to double check your data
    // for (const auto &obj : theData) {
    //   std::cout << *obj << std::endl; }

    theAnswers.createStateData(theData);

    //one example of how to print required - ADD OTHERS
    cout << "*** the state that needs the most pre-schools**" << endl;
    string needPK = theAnswers.youngestPop();
    cout << "Name of state: " << needPK << endl;
    if (theAnswers.getStateData(needPK) != nullptr){
        cout << *(theAnswers.getStateData(needPK)) << endl;
    } else{
        cout << "Did you read the lab instructions?" << endl;
    }

    //NOW fill in these too
    cout << "*** the state that needs the most high schools**" << endl;
    cout << "Name of state: " << theAnswers.teenPop() << endl;
    //FILL IN

    cout << "*** the state that needs the most vaccines**" << endl;
    cout << "Name of state: " << theAnswers.wisePop() << endl;
    //FILL IN

    cout << "*** the state that needs the most help with education**" << endl;
    cout << "Name of state: " << theAnswers.underServeHS() << endl;
    //FILL IN

    cout << "*** the state with most college grads**" << endl;
    cout << "Name of state: " << theAnswers.collegeGrads() << endl;
    //FILL IN

    cout << "*** the state with largest percent of the population below the poverty line**" << endl;
    cout << "Name of state: " << theAnswers.belowPoverty() << endl;
    //FILL IN

    return 0;
}
