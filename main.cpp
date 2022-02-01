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


    std::vector<shared_ptr<psData>> thePoliceData = read_csvPolice(
            "fatal-police-shootings-data.csv", POLICE);

    //debug print out if needed left for your use in testing

    int i = 0;
    for (const auto &obj : thePoliceData) {
        std::cout << *obj << std::endl;
        i++;
        if (i > 15)
            break;
    }

    theAnswers.createStateData(theData);

    return 0;
}
