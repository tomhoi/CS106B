#include "network.h"

Network::Network(int numInputs, int numHiddenNeurons, int numOutputs)
{
    for (int i = 0; i < numInputs; i++) {
        Neuron* inputNeuron = new Neuron();
        inputLayer.push_back(inputNeuron);
        Neuron* bias = new Neuron();
    }
}
