#ifndef NEURON_H
#define NEURON_H

#include "set"
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
    
    void addConnection(Neuron* source);
    void addConnection(Connection* connection);
    set<Connection*> getSources();
    
private:
    double outputVal;
    
    set<Connection*> sources;
//    set<Connection*> destinations;
};

#endif // NEURON_H
