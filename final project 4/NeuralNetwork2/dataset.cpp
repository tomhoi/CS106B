#include "dataset.h"
#include <iostream>

DataSet::DataSet(string filename) {
    stream.open(filename.c_str());
    if (isFailState()) {
        cout << "can't open the file" << endl;
    }
}

DataSet::~DataSet() {
    stream.close();
}

bool DataSet::isFailState() {
    return !stream.good();
}

bool DataSet::nextDataEntry(DataEntry& entry) {
    string line;
    getline(stream, line);
    if (isFailState()) {
        return false;
    } else {
        entry = DataEntry(line);
        return true;
    }
}
