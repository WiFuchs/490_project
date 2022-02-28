/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>
#include "demogData.h"
#include "psData.h"

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) {
    temp.erase(
        remove(temp.begin(), temp.end(), '\"' ),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss) {
    string data, junk;
    //ignore the first quotes
    std::getline(ss, junk, '\"');
    //read the data (not to comma as some data includes comma (Hospital names))
    std::getline(ss, data, '\"');
    //read to comma final comma (to consume and prep for next)
    std::getline(ss, junk, ',');
    //data includes final quote (see note line 18)
    return stripQuotes(data);
}

string getFieldNQ(std::stringstream &ss)
{
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while(std::getline(ss, colname, ',')) {
    //    std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<regionData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);
    string name = getField(ss);
    string state = getField(ss);
    double popOver65 = max(stod(getField(ss))/100.0, 0.0);
    double popUnder18 = max(stod(getField(ss))/100.0, 0.0);
    double popUnder5 = max(stod(getField(ss))/100.0, 0.0);
    double bachelorDegreeUp = max(stod(getField(ss))/100.0, 0.0);
    double highSchoolUp = max(stod(getField(ss))/100.0, 0.0);
    //skip 1
    getField(ss);
    //store initial data as percent (then convert to count)
    double FirstNation= stod(getField(ss))/100.0;
    double Asian= stod(getField(ss))/100.0;
    double Black= stod(getField(ss))/100.0;
    double Latinx= stod(getField(ss))/100.0;
    double HIPacificIsle= stod(getField(ss))/100.0;
    double MultiRace= stod(getField(ss))/100.0;
    double White= stod(getField(ss))/100.0;
    double WhiteNH = stod(getField(ss))/100.0;
    double homeOwnRate = max(stod(getField(ss))/100.0, 0.0);
    int numHouseHold = max(stoi(getField(ss)), 0);
    //skip 2
    getField(ss);
    getField(ss);
    float avgPerPerHouse = max(stod(getField(ss)), 0.0);
    //turn into mathematical percent
    long int houseIncome = max(stoi(getField(ss)), 0);
    //skip 1
    getField(ss);
    double foreignBorn= max(stod(getField(ss))/100.0, 0.0);
    //skip 5
    for (int i=0; i < 5; i++)
        getField(ss);
    double popFemale = max(stod(getField(ss))/100.0, 0.0);
    int veteransCount = max(stoi(getField(ss)), 0);
    int totalPop2020 = stoi(getField(ss));

    double veterans = veteransCount / double(totalPop2020);
    //community racial mix created with counts not percents

    Ethnicity ethnicity = Ethnicity(round(White*totalPop2020), round(Black*totalPop2020), round(FirstNation*totalPop2020), round(Asian*totalPop2020), round(HIPacificIsle*totalPop2020),
                                    round(MultiRace*totalPop2020), round(Latinx*totalPop2020), round(WhiteNH*totalPop2020), totalPop2020);

    return make_shared<demogData>(name, state, popOver65, popUnder18, popUnder5, totalPop2020,
                                  ethnicity, houseIncome, homeOwnRate, avgPerPerHouse, veterans,
                                  highSchoolUp, bachelorDegreeUp, foreignBorn, numHouseHold,
                                  popFemale);
}

shared_ptr<regionData> readCSVLinePolice(std::string theLine) {
    std::stringstream ss(theLine);
    //TO DO read in the fields - use getFieldNQ as no quotes!!
    getField(ss); //ignore id
    string name = getField(ss);
    //skip 2
    getField(ss);
    getField(ss);
    //fill in
    string armed = getField(ss);
    getField(ss);
    getField(ss);
    string ethnicity = getField(ss);
    string city = getField(ss);
    string state = getField(ss);
    string mentalIll = getField(ss);
    getField(ss);
    getField(ss);
    string bodyCam = getField(ss);
    getField(ss);
    getField(ss);
    getField(ss);
    /* TO DO fix */
    return make_shared<psData>(state, city, name, ethnicity, mentalIll, armed, bodyCam);
}


// Rewrite as one method - maybe replace typeFlag with search on columns
void read_csv(std::vector<shared_ptr<regionData>>& theData, std::string filename, typeFlag fileType) {

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

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                theData.push_back(readCSVLineDemog(line));
            } else if (fileType == POLICE) {
                theData.push_back(readCSVLinePolice(line));
            }else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }

}



