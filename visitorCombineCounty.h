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
	void visit(shared_ptr<demogData> obj) {
        //fill in

    }
    
    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj) {
        //fill in
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

          cityToCounty[cityKey] = std::stoi(countyfips);

          //cout << "line: " << line << endl;
          //cout << "pair (city, county): " << city << ", " << county << " state " << state << " fip" << countyfips <<  endl;
        }

        // Close file
        myFile.close();
      }
    }


    private:
        //only inherited data at this point
        //helper map to create aggregates from city -> county
        std::map<string, int> cityToCounty;
};

#endif
