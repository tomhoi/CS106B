#ifndef DATAENTRY_H
#define DATAENTRY_H

#include "vector"
#include "string"

using namespace std;

class DataEntry
{
public:
    DataEntry(string line);
    ~DataEntry();
    
    vector<int> getValues();
    int getAnswer();
    
    void print();
    
private:
    vector<int> values;
    int answer;
};

#endif // DATAENTRY_H
