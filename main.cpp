#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"
#include "DataDraw.h"
#include "ellipse.h"

using namespace std;

/*
 * Authors: Sarah Hallam & Will Fuchs
 */


int main() {

    dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics.csv", DEMOG);

//    //debug print out - uncomment if you want to double check your data
//     for (const auto &obj : theData) {
//       std::cout << *obj << std::endl; }


    std::vector<shared_ptr<psData>> thePoliceData = read_csvPolice(
            "fatal-police-shootings-data.csv", POLICE);

    //debug print out if needed left for your use in testing

//    int i = 0;
//    for (const auto &obj : thePoliceData) {
//        std::cout << *obj << std::endl;
//        i++;
//        if (i > 15)
//            break;
//    }

    theAnswers.createStateData(theData);

    theAnswers.createStatePoliceData(thePoliceData);

    theAnswers.reportTopTenStatesPS();

    // Example of using the DataDraw class
    std::array<color, 10> colorMap;
    colorMap[0] = color(91, 80, 235); //cool
    colorMap[1] = color(95, 166, 245);
    colorMap[2] = color(99, 223, 220);
    colorMap[3] = color(95, 245, 155);
    colorMap[4] = color(128, 235, 96); //midway
    colorMap[5] = color(235, 235, 75);
    colorMap[6] = color(245, 213, 91);
    colorMap[7] = color(223, 170, 94);
    colorMap[8] = color(245, 134, 91);
    colorMap[9] = color(235, 91, 101); //warm
    DataDraw drawer = DataDraw(600);
    auto stateData = theAnswers.getAllStateData();


    // draw foreign born and homeowners on one plot
    double max_fb = theAnswers.mostForBorn()->getForeignBornP();
    double max_homeown = theAnswers.mostHomeowners()->getHomeownersP();
    std::sort(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) -> bool {
        return a->getName() < b->getName();
    });
    drawer.addShapeForObject(stateData, function<shared_ptr<shape>(shared_ptr<State>, double)>([=](const shared_ptr<State>& state, double block_size) -> shared_ptr<shape> {
                                 double scaled = state->getDemoData()->getHomeownersP() / max_homeown;
                                 double size = scaled * block_size / 2.0;
                                 return make_shared<ellipse>(0, 0, size, size, colorMap[round(scaled * 9)]);
                             }));
    drawer.addShapeForObject(stateData, function<shared_ptr<shape>(shared_ptr<State>, double)>([=](const shared_ptr<State>& state, double block_size) -> shared_ptr<shape> {
                double scaled = state->getDemoData()->getForeignBornP() / max_fb;
                double size = scaled * block_size / 2.0;
                return make_shared<ellipse>(0, 0, size, size, colorMap[round(scaled * 9)]);
            }));
    drawer.draw("homeowners_fb.ppm");
    drawer.clearShapes();

    // draw police shooting data and median income on one plot
    double max_income = theAnswers.genericDemogMaxN(&demogState::getMedianIncome)[0]->getDemoData()->getMedianIncome();
    int max_incidents = theAnswers.genericPSMaxN(&psCombo::getNumberOfCases)[0]->getPSData()->getNumberOfCases();
    drawer.addShapeForObject(stateData,function<shared_ptr<shape>(shared_ptr<State>, double)>([=](const shared_ptr<State>& state, double block_size) -> shared_ptr<shape> {
                                 double scaled = state->getDemoData()->getMedianIncome() / double(max_income);
                                 double size = scaled * block_size / 2.0;
                                 return make_shared<ellipse>(0, 0, size, size, colorMap[round(scaled * 9)]);
                             }));
    drawer.addShapeForObject(stateData,function<shared_ptr<shape>(shared_ptr<State>, double)>([=](const shared_ptr<State>& state, double block_size) -> shared_ptr<shape> {
                                 double scaled = state->getPSData()->getNumberOfCases() / double(max_incidents);
                                 double size = scaled * block_size / 2.0;
                                 return make_shared<ellipse>(0, 0, size, size, colorMap[round(scaled * 9)]);
                             }));
    drawer.draw("income_ps.ppm");
    return 0;
}
