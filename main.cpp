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

    statTool statToolHelper;
    visitorCombineState vCombineState;
    statToolHelper.createStateData(theData, vCombineState);

    visitorCombineCounty vCombineCounty("uscities.csv");
    statToolHelper.createCountyData(theData, vCombineCounty);
    cout << "here" << endl;
    int i = 0;
    for (auto elem : vCombineState.getComboDemog()) {
        i++;
        cout << *elem.second << endl;
        if (i > 20) {
            break;
        }
    }
    cout << "unmatched: " << vCombineCounty.noMatch << endl;
    cout << "done" << endl;


//    visitorReport report;
//    for (const auto &obj : theData) {
//        obj->accept(report);
//    }


    return 0;
}
