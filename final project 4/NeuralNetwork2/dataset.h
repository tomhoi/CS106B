#ifndef DATASET_H
#define DATASET_H

#include "dataentry.h"
#include "string"
#include <fstream>

using namespace std;

class DataSet
{
public:
    DataSet(string filename);
    ~DataSet();
    
    /**
     * @brief nextDataEntry
     * @param entry
     * @return - Returns whether or not DataSet should keep reading the file.
     */
    bool nextDataEntry(DataEntry& entry);
    
private:
    ifstream stream;
    bool isFailState();
};

#endif // DATASET_H
