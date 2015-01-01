#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"
#include "connection.h"
#include "vector"

using namespace std;

class Layer
{
public:
    Layer(int size, Layer* prev);
    ~Layer();
    
    vector<Neuron*> getNeurons();
    void setNextLayer(Layer* layer);
    void setInputs(vector<int>& inputs);
    bool isInputLayer();
    Layer* getPrevLayer();
    
    vector<double> feedForward(Layer* curr);
    
private:
    vector<Neuron*> neurons;
    void addNeuron(Neuron* neuron);
    Neuron* bias;
    
    Layer* prevLayer;
    Layer* nextLayer;
};

#endif // LAYER_H
