#ifndef NETWORK_H
#define NETWORK_H

#include "vector"
#include "neuron.h"

using namespace std;

class Network
{
public:
    /**
     * @brief Network
     * Single hidden layer
     * @param numInputs
     * @param numHiddenNeurons
     * @param numOutputs
     */
    Network(int numInputs, int numHiddenNeurons, int numOutputs);
    ~Network(); 
    
    double feedForward(vector<int>& inputData);
    void train(double output, double desired);
    
private:
    vector<Neuron*> inputLayer;
};

#endif // NETWORK_H
