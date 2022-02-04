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

shared_ptr<shape> make_shape(shared_ptr<demogData> county, double block_size) {
    return make_shared<ellipse>(0, 0, block_size, block_size, color(255, 0, 0));
}

int main() {

    dataAQ theAnswers;
    dataAQ policeAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics.csv", DEMOG);

//    //debug print out - uncomment if you want to double check your data
     for (const auto &obj : theData) {
       std::cout << *obj << std::endl; }


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

//    cout << *policeAnswers.getStatePoliceData("CA") << endl; //**fix** incidents involving unarmed or armed w. toy weapons (~50 off)
//    cout << "\n\n";
//    cout << *theAnswers.getStateData("CA") << endl; // **fix** native hawaiian/pacific islander (zeroing out), county/housing section (dataAQ wrong)

    theAnswers.reportTopTenStatesPS();  // **fix** sorting (error: invalid operands to binary expression)

    // Example of using the DataDraw class
    //TODO does below work with size?
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
    double max_fb = (*max_element(stateData.begin(), stateData.end(), [](auto a, auto b) -> bool {
                        return a->getForeignBornP() < b->getForeignBornP();
                    }))->getForeignBornP();
    std::sort(stateData.begin(), stateData.end(), [](auto a, auto b) -> bool {
        return a->getState() < b->getState();
    });
    drawer.addShapeForObject(stateData, function<shared_ptr<shape>(shared_ptr<demogState>, double)>([=](const shared_ptr<demogState>& county, double block_size) -> shared_ptr<shape> {
                 cout << county->getState() << " " << county->getForeignBornP() << endl;
                double scaled = county->getForeignBornP() / max_fb;
                double size = scaled * block_size / 2.0;
                return make_shared<ellipse>(0, 0, size, size, colorMap[round(scaled * 9)]);
            }));
    drawer.draw("test_abstraction.ppm");

    return 0;
}
