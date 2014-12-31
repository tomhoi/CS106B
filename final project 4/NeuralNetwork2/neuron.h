#ifndef NEURON_H
#define NEURON_H

#include "vector"
#include "connection.h"

using namespace std;

class Connection;

class Neuron
{
public:
    Neuron();
    ~Neuron();
    
    double calculateOutput();
    double getOutputVal();
    void setInputVal(int val);
    
    void addSource(Neuron* source);
    void addSource(Connection* connection);
    vector<Connection*> getSources();
    
private:
    double outputVal;
    int inputVal; // direct input value from user (for bias or input neurons)
    bool hasInputVal;
    
    vector<Connection*> sources;
};

#endif // NEURON_H
