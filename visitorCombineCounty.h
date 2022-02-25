#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include <cassert>

class visitorCombineCounty : public visitorCombine {
public:
    int noMatch;
    visitorCombineCounty(std::string filename) {
        noMatch = 0;
        read_csvCityCounty(filename);
    }

    //store demographic data by county name
	void visit(shared_ptr<demogData> data) override {
        auto mapEntry = allComboDemogData.find(data->getName());
        if(mapEntry == allComboDemogData.end()){
            allComboDemogData.insert(pair<string, shared_ptr<demogCombo> >(data->getName(), make_shared<demogCombo>(data->getName(), 0, 0, 0, 0, Ethnicity(0,0,0,0,0,0,0,0,0), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)));
            mapEntry = allComboDemogData.find(data->getName());
        }

        shared_ptr<demogCombo> comboData = mapEntry->second;
        *comboData += *data;
    }
    
    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj) override {
        string cityKey = obj->getCity() + obj->getState();
        auto countyIt = cityToCounty.find(cityKey);
        if (countyIt == cityToCounty.end()) {
            noMatch++;
            return;
        }
        string county = countyIt->second;

        auto mapEntry = allComboPoliceData.find(county);
        if(mapEntry == allComboPoliceData.end()){
            allComboPoliceData.insert(pair<string, shared_ptr<psCombo> >(county, make_shared<psCombo>(obj->getState(), 0, 0, 0, 0, 0, county, Ethnicity(0,0,0,0,0,0,0,0,0))));
            mapEntry = allComboPoliceData.find(county);
        }

        shared_ptr<psCombo> comboData = mapEntry->second;
        *comboData += *obj;
    }

    //helper to create map from city to county
    void read_csvCityCounty(std::string filename) {
     // Create an input filestream
     std::ifstream myFile(filename);

     // Make sure the file is open
     if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
     }

     if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and enter into the map
        while(std::getline(myFile, line)) {

          std::stringstream ss(line);

          string city = getField(ss);
          string junk1 = getField(ss);  //"city_ascii","city_alt"
          string junk0 = getField(ss);
          string state = getField(ss);
          string junk2 = getField(ss); //"state_name"
          string countyfips = getField(ss);
          string county = getField(ss);

          string cityKey = city+state;
          string countyKey = county+state;

          cityToCounty[cityKey] = countyKey;//std::stoi(countyfips);

//          cout << "line: " << line << endl;
//          cout << "pair (city, county): " << city << ", " << county << " state " << state << " fip" << countyfips <<  endl;
        }

        // Close file
        myFile.close();
      }
    }

    void visit(std::shared_ptr<psCombo> d) override {
        assert(false);
    }

    private:
        //only inherited data at this point
        //helper map to create aggregates from city -> county
        std::string stripCounty(string inWord) {
//            string compareS = "County";
//            /* some names include the word 'county' - strip */
//            std::string::size_type i = inWord.find(compareS);
//            if (i != std::string::npos) {
//                inWord.erase(i-1, compareS.length()+1);
//            }
            //apostrophe issue - strip will result in lack of rep - better solution?
            string symbol = "\'";
            std::string::size_type i = inWord.find(symbol);
            if (i != std::string::npos) {
                inWord.erase(i-1, symbol.length()+1);
            }
            //strip Alaska designator
            string borough = "and Borough";
            i = inWord.find(borough);
            if (i != std::string::npos) {
                inWord.erase(i-1, borough.length()+1);
            }
            string borough1 = "Borough";
            i = inWord.find(borough1);
            if (i != std::string::npos) {
                inWord.erase(i-1, borough1.length()+1);
            }
            string ca = "Census Area";
            i = inWord.find(ca);
            if (i != std::string::npos) {
                inWord.erase(i-1, ca.length()+1);
            }
            ca = "Parish";
            i = inWord.find(ca);
            if (i != std::string::npos) {
                inWord.erase(i-1, ca.length()+1);
            }
            inWord = "'" + inWord + "'";
            return inWord;
        }
        std::map<string, string> cityToCounty;

};

#endif
