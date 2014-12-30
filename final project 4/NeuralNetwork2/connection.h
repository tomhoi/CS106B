#ifndef CONNECTION_H
#define CONNECTION_H

#include "neuron.h"

class Neuron;

class Connection
{
public:
    Connection(Neuron* to, Neuron* from);
    ~Connection();
    
    double getWeight();
    double adjustWeight(double deltaWeight);
    
    Neuron* getSource();
    Neuron* getDestination();
    
private:
    double weight;
    Neuron* to;
    Neuron* from;
};

#endif // CONNECTION_H
