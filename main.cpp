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
#include "annulus.h"

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
    //drawer.draw("homeowners_fb.ppm");
    drawer.clearShapes();

    // draw police shooting data and median income on one plot
    double max_income = theAnswers.genericDemogMaxN(&demogCombo::getMedianIncome)[0]->getDemoData()->getMedianIncome();
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
    //drawer.draw("income_ps.ppm");

    theAnswers.reportBottomTenStatesHomeOwn();
    theAnswers.reportTopTenStatesPS();


    drawer.clearShapes();
    //TODO: why do we need to use raw pointers there?
    double max_demo_white = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
        return a->getDemoData()->getEthnicity().getWhiteAlone() < b->getDemoData()->getEthnicity().getWhiteAlone();
    })->get()->getDemoData()->getEthnicity().getWhiteAlone();
    double max_ps_white = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
                              return a->getPSData()->getRaceEthnicity().getWhiteAlone() < b->getPSData()->getRaceEthnicity().getWhiteAlone();
                          })->get()->getPSData()->getRaceEthnicity().getWhiteAlone();
    double biggest = max(max_demo_white, max_ps_white);
    drawer.addShapeForObject(stateData, function<shared_ptr<shape>(shared_ptr<State>, double)>([=](const shared_ptr<State>& state, double block_size) -> shared_ptr<shape> {
                                 double ps_white = state->getPSData()->getRaceEthnicity().getWhiteAlone();
                                 double demo_white = state->getDemoData()->getEthnicity().getWhiteAlone();
                                 double scale = max(ps_white, demo_white) / biggest;
                                 double small_scale = min(ps_white, demo_white) / biggest;
                                 double outer = scale * block_size / 2.0;
                                 double inner = small_scale * block_size / 2.0;
                                 return make_shared<annulus>(0, 0, inner, outer, colorMap[ps_white > demo_white ? 9 : 0]);
                             }));
    drawer.draw("ps_rings_white.ppm");
    
    drawer.clearShapes();
    //TODO: why do we need to use raw pointers there?
    double max_demo_black = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
                                return a->getDemoData()->getEthnicity().getBlackAlone() < b->getDemoData()->getEthnicity().getBlackAlone();
                            })->get()->getDemoData()->getEthnicity().getBlackAlone();
    double max_ps_black = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
                              return a->getPSData()->getRaceEthnicity().getBlackAlone() < b->getPSData()->getRaceEthnicity().getBlackAlone();
                          })->get()->getPSData()->getRaceEthnicity().getBlackAlone();
    biggest = max(max_demo_black, max_ps_black);
    drawer.addShapeForObject(stateData, function<shared_ptr<shape>(shared_ptr<State>, double)>([=](const shared_ptr<State>& state, double block_size) -> shared_ptr<shape> {
                                 double ps_black = state->getPSData()->getRaceEthnicity().getBlackAlone();
                                 double demo_black = state->getDemoData()->getEthnicity().getBlackAlone();
                                 double scale = max(ps_black, demo_black) / biggest;
                                 double small_scale = min(ps_black, demo_black) / biggest;
                                 double outer = scale * block_size / 2.0;
                                 double inner = small_scale * block_size / 2.0;
                                 return make_shared<annulus>(0, 0, inner, outer, colorMap[ps_black > demo_black ? 9 : 0]);
                             }));
    drawer.draw("ps_rings_black.ppm");

    drawer.clearShapes();
    //TODO: why do we need to use raw pointers there?
    double max_demo_asian = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
                                return a->getDemoData()->getEthnicity().getAsianAlone() < b->getDemoData()->getEthnicity().getAsianAlone();
                            })->get()->getDemoData()->getEthnicity().getAsianAlone();
    double max_ps_asian = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
                              return a->getPSData()->getRaceEthnicity().getAsianAlone() < b->getPSData()->getRaceEthnicity().getAsianAlone();
                          })->get()->getPSData()->getRaceEthnicity().getAsianAlone();
    biggest = max(max_demo_asian, max_ps_asian);
    drawer.addShapeForObject(stateData, function<shared_ptr<shape>(shared_ptr<State>, double)>([=](const shared_ptr<State>& state, double block_size) -> shared_ptr<shape> {
                                 double ps_asian = state->getPSData()->getRaceEthnicity().getAsianAlone();
                                 double demo_asian = state->getDemoData()->getEthnicity().getAsianAlone();
                                 double scale = max(ps_asian, demo_asian) / biggest;
                                 double small_scale = min(ps_asian, demo_asian) / biggest;
                                 double outer = scale * block_size / 2.0;
                                 double inner = small_scale * block_size / 2.0;
                                 return make_shared<annulus>(0, 0, inner, outer, colorMap[ps_asian > demo_asian ? 9 : 0]);
                             }));
    drawer.draw("ps_rings_asian.ppm");

    drawer.clearShapes();
    //TODO: why do we need to use raw pointers there?
    double max_demo_firstNations = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
                                return a->getDemoData()->getEthnicity().getAIndianANativeAlone() < b->getDemoData()->getEthnicity().getAIndianANativeAlone();
                            })->get()->getDemoData()->getEthnicity().getAIndianANativeAlone();
    double max_ps_firstNations = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
                              return a->getPSData()->getRaceEthnicity().getAIndianANativeAlone() < b->getPSData()->getRaceEthnicity().getAIndianANativeAlone();
                          })->get()->getPSData()->getRaceEthnicity().getAIndianANativeAlone();
    biggest = max(max_demo_firstNations, max_ps_firstNations);
    drawer.addShapeForObject(stateData, function<shared_ptr<shape>(shared_ptr<State>, double)>([=](const shared_ptr<State>& state, double block_size) -> shared_ptr<shape> {
                                 double ps_firstNations = state->getPSData()->getRaceEthnicity().getAIndianANativeAlone();
                                 double demo_firstNations = state->getDemoData()->getEthnicity().getAIndianANativeAlone();
                                 double scale = max(ps_firstNations, demo_firstNations) / biggest;
                                 double small_scale = min(ps_firstNations, demo_firstNations) / biggest;
                                 double outer = scale * block_size / 2.0;
                                 double inner = small_scale * block_size / 2.0;
                                 return make_shared<annulus>(0, 0, inner, outer, colorMap[ps_firstNations > demo_firstNations ? 9 : 0]);
                             }));
    drawer.draw("ps_rings_firstNations.ppm");
    
    
    drawer.clearShapes();
    //TODO: why do we need to use raw pointers there?
    double max_demo_latinx = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
                                return a->getDemoData()->getEthnicity().getHispanicOrLatino() < b->getDemoData()->getEthnicity().getHispanicOrLatino();
                            })->get()->getDemoData()->getEthnicity().getHispanicOrLatino();
    double max_ps_latinx = max_element(stateData.begin(), stateData.end(), [](shared_ptr<State> a, shared_ptr<State> b) {
                              return a->getPSData()->getRaceEthnicity().getHispanicOrLatino() < b->getPSData()->getRaceEthnicity().getHispanicOrLatino();
                          })->get()->getPSData()->getRaceEthnicity().getHispanicOrLatino();
    biggest = max(max_demo_latinx, max_ps_latinx);
    drawer.addShapeForObject(stateData, function<shared_ptr<shape>(shared_ptr<State>, double)>([=](const shared_ptr<State>& state, double block_size) -> shared_ptr<shape> {
                                 double ps_latinx = state->getPSData()->getRaceEthnicity().getHispanicOrLatino();
                                 double demo_latinx = state->getDemoData()->getEthnicity().getHispanicOrLatino();
                                 double scale = max(ps_latinx, demo_latinx) / biggest;
                                 double small_scale = min(ps_latinx, demo_latinx) / biggest;
                                 double outer = scale * block_size / 2.0;
                                 double inner = small_scale * block_size / 2.0;
                                 return make_shared<annulus>(0, 0, inner, outer, colorMap[ps_latinx > demo_latinx ? 9 : 0]);
                             }));
    drawer.draw("ps_rings_latinx.ppm");


    return 0;
}
