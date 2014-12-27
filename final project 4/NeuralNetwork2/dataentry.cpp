#include "dataentry.h"
#include "cstdlib"
#include <iostream>

void parseLine(string line, vector<int>& parsed);

DataEntry::DataEntry(string line) {
    parseLine(line, values);
    answer = values.back();
    values.pop_back(); // remove answer
}

DataEntry::~DataEntry() {
    
}

void parseLine(string line, vector<int>& parsed) {
    char currChar;
    int currIndex = 0;
    string currToken;
    
    while (currIndex < line.length()) {
        currChar = line[currIndex];
        if (currChar == ' ' || currChar == ',') { // space or comma
            if (!currToken.empty()) {
                parsed.push_back(atoi(currToken.c_str()));
                currToken.clear();
            }
        } else { // number
            currToken += currChar;
        }
        currIndex++;
    }
    parsed.push_back(atoi(currToken.c_str())); // last token
}

void DataEntry::print() {
    cout << "VALUES: ";
    for (int val : values) {
        cout << val << " ";
    }
    cout << endl << "ANSWER: " << answer << endl;
}
