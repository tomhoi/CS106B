#ifndef NEURON_H
#define NEURON_H

#include "set"

using namespace std;

class Neuron
{
public:
    Neuron(double weight);
    Neuron();
    ~Neuron();
    
    double calculateOutput();
    double getOutputVal();
    double getWeight();
    double adjustWeight(double deltaWeight);
    
    void addInputNeuron(Neuron* input);
    void addOutputNeuron(Neuron* output);
//    vector<Neuron*> getInputs();
//    vector<Neuron*> getOutputs();
    
private:
    double outputVal;
    double weight;
    
    set<Neuron*> inputs;
    set<Neuron*> outputs;
};

#endif // NEURON_H
