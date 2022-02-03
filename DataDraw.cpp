//
// Created by Will Fuchs on 2/1/22.
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>

#include "DataDraw.h"
#include "ppmR.h"
using namespace std;

void DataDraw::draw(string filename) {
    ofstream outFile;
    ppmR theWriter(size, size);
    outFile.open(filename);
    if (outFile) {
        cout << "writing an image of size: " << size << " " << size << " to: " << filename << endl;
        theWriter.writeHeader(outFile);
    } else {
        cout << "Error cannot open outfile" << endl;
        return;
    }

    color background(12, 34, 56);
    color inC = background;
    bool inTrue = false;

    //for every point in the 2D space
    for (int y=0; y < theWriter.height; y++) {
        for (int x =0; x < theWriter.width; x++) {
            inTrue = false;
            for (auto cur_shape: shapes) {
                if (cur_shape->eval(x, y)){
                    inC = cur_shape->getInC();
                    inTrue = true;
                }
            }
            if (inTrue) {
                theWriter.writePixel(outFile, x, y, inC);
            }
            else
                theWriter.writePixel(outFile, x, y, background);
        }
        theWriter.writeNewLine(outFile);
    }

}