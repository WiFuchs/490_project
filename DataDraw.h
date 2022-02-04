//
// Created by Will Fuchs on 2/1/22.
//

#ifndef INC_490_PROJECT_DATADRAW_H
#define INC_490_PROJECT_DATADRAW_H

#include <vector>
#include "shape.h"
#include "color.h"

using namespace std;


class DataDraw {
public:
    explicit DataDraw(int sze) : size(sze) {}
    void setColors(vector<color> inC) {
        colors = inC;
}
    void draw(string filename);
    void clearShapes() {shapes.clear();}

    template<typename T>
    void addShapeForObject(const vector<T> objects, function<shared_ptr<shape>(T, double)> shape_creator, bool default_placement = true) {
        int num_objects = objects.size();
        int rows = ceil(sqrt(num_objects));
        int cols = rows;
        double block_size = size / double(rows);
        cout << block_size << endl;
        for (int i = 0; i < num_objects; i++) {
            auto obj = objects[i];
            shared_ptr<shape> new_shape = shape_creator(obj, block_size);
            if (default_placement) {
                double cur_row = floor(i / rows) + 0.5;
                double cur_col = i % cols + 0.5;
                new_shape->placeAt(block_size * cur_col, block_size * cur_row);
            }

            shapes.push_back(new_shape);
        }
    }
private:
    vector<shared_ptr<shape> > shapes;
    std::vector<color> colors;
    int size;
};



#endif//INC_490_PROJECT_DATADRAW_H
