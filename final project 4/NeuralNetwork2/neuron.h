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
    
    double feedForward();
    void setInputVal(double val);
    double getInputVal();
    bool getHasInputVal();
    
    void addSource(Neuron* source);
    void addSource(Connection* connection);
    vector<Connection*> getSources();
    
private:
    double outputVal;
    double inputVal; // direct input value from user (for bias or input neurons)
    bool hasInputVal;
    
    vector<Connection*> sources;
};

#endif // NEURON_H
