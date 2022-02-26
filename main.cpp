#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include "demogData.h"
#include "parse.h"
#include "DataDraw.h"
#include "ellipse.h"
#include "annulus.h"
#include "visitorReport.h"
#include "statTool.h"
#include "Visitor.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"

using namespace std;

/*
 * Authors: Sarah Hallam & Will Fuchs
 */


int main() {

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<regionData>> theData;
    read_csv(theData,"county_demographics.csv", DEMOG);

//    //debug print out - uncomment if you want to double check your data
//     for (const auto &obj : theData) {
//       std::cout << *obj << std::endl; }


    read_csv(theData, "fatal-police-shootings-data.csv", POLICE);

    //debug print out if needed left for your use in testing

//    int i = 0;
//    for (const auto &obj : thePoliceData) {
//        std::cout << *obj << std::endl;
//        i++;
//        if (i > 15)
//            break;
//    }

    //create a visitor to combine the state data
    visitorCombineState theStates;
    statTool::createStateData(theData, theStates);
    //theStates.printAllCombo();
    //create a visitor to combine the county data
    visitorCombineCounty theCounties("uscities.csv");
    statTool::createCountyData(theData, theCounties);
    cout << "number of unmatched incidents: " << theCounties.noMatch << endl;

    //305 at this moment
    //DEBUG only printing top ten for testing
    theCounties.printNCombo(1);
    cout << "stats work:" << endl;
    cout << "state home ownership and BA: " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getHomeowners,
                                          &demogData::getBachelorsDegree,
                                          &demogData::getHomeownersCount, &demogData::getBachelorsDegreeCount);
    cout << "county home ownership and BA: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties,
                                          &demogData::getHomeowners, &demogData::getBachelorsDegree,
                                          &demogData::getHomeownersCount, &demogData::getBachelorsDegreeCount);
    cout << "county PS mental illness to African American " << endl;
    statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI,
                                 &psCombo::getCountBlack);
    cout << "county PS mental illness to White " << endl;
    statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI,
                                 &psCombo::getCountWhite);
    cout << "State data Pop veterans and high school and up: " << endl;
    statTool::computeStatsDemogRegionData(&theStates,
                                          &demogData::getVeterans, &demogData::getHighSchoolDegree,
                                          &demogData::getVeteransCount, &demogData::getHighSchoolDegreeCount);
    cout << "done" << endl;


//    visitorReport report;
//    for (const auto &obj : theData) {
//        obj->accept(report);
//    }


    return 0;
}
