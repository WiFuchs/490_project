
#ifndef PARSE_H
#define PARSE_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> // std::stringstream
#include "regionData.h"

/*static functions to help parse CSV data */

/* For future assignments when we read different types of data */
enum typeFlag {
	DEMOG = 0,
	HOSPITAL = 1,
	POLICE = 2
};

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) ;

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss);

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile);

// Read one line from a CSV file for county demographic data specifically
shared_ptr<regionData> readCSVLineDemog(std::string theLine);
shared_ptr<regionData> readCSVLinePS(std::string theLine);

//read from a CSV file (for a given data type) return a vector of the data
void read_csv(std::vector<shared_ptr<regionData>>& data, std::string filename, typeFlag fileType);

#endif
