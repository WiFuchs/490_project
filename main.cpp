#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include "demogData.h"
#include "parse.h"
#include "dataAQ.h"

#include "rect.h"
#include "color.h"
#include "ppmR.h"

using namespace std;

void writeOut(ostream& out, ppmR& theWriter, vector<shared_ptr<Rect>> Rs) {

    color inC;
    color background(12, 34, 56);
    bool inTrue = false;

    //for every point in the 2D space
    for (int y=0; y < theWriter.height; y++) {
        for (int x =0; x < theWriter.width; x++) {
            inTrue = false;
            for (auto rect: Rs) {
                if (rect->eval(x, y) < 0){
                    inC = rect->getInC();
                    inTrue = true;
                }
            }
            if (inTrue) {
                theWriter.writePixel(out, x, y, inC);
            }
            else
                theWriter.writePixel(out, x, y, background);
        }
        theWriter.writeNewLine(out);
    }
}

bool compare_fb(shared_ptr<demogData> a, shared_ptr<demogData> b) {
    return a->getForeignBorn() < b->getForeignBorn();
}


int main(int argc, char *argv[]) {
    //cool to warm color map
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


    dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theData = read_csv(
            "county_demographics_2014_EDIT2.csv", DEMOG);

    //debug print out - uncomment if you want to double check your data
    // for (const auto &obj : theData) {
    //   std::cout << *obj << std::endl; }

    theAnswers.createStateData(theData);

    std::vector<std::shared_ptr<Rect>> counties;
    const int block_size = 10;
    int num_counties = theData.size();
    int size = ceil(sqrt(num_counties) * (block_size+1));
    double max_fb = (*max_element(theData.begin(), theData.end(), compare_fb))->getForeignBorn();
    for(int i = 0; i < theData.size(); i++) {
        cout << i << endl;
        int row = floor(i / double(size/double(block_size)));
        int col = i % (size/block_size);
        cout << "row: " << row << " col: " << col << endl;
        shared_ptr<demogData> countyData = theData[i];
        cout << "max_fb " << max_fb;
        int colorIdx = round((countyData->getForeignBorn() / max_fb) * 10);
        counties.push_back(make_shared<Rect>(col*block_size, row*block_size, block_size, block_size, colorMap[colorIdx]));
    }

    // file writing
    ofstream outFile;
    if (argc < 2) {
        cerr << "Error format: a.out outfileName" << endl;
    } else {
        ppmR theWriter(size, size);
        outFile.open(argv[1]);
        if (outFile) {
            cout << "writing an image of size: " << size << " " << size << " to: " << argv[1] << endl;
            theWriter.writeHeader(outFile);
            writeOut(outFile, theWriter, counties);
        } else {
            cout << "Error cannot open outfile" << endl;
            exit(0);
        }
    }


    return 0;
}
