#include "layer.h"

Layer::Layer(int size, Layer* prev) {
    prevLayer = prev; // set previous layer
    
    for (int i = 0; i < size; i++) { // add given number of neurons
        Neuron* neuron = new Neuron();
        addNeuron(neuron);
    }
    
    Neuron* bias = new Neuron();
    bias->setInputVal(-1);
    for (Neuron* curr : neurons) {
        curr->addSource(bias);
    }    
}

vector<Neuron*> Layer::getNeurons() {
    return neurons;
}

void Layer::addNeuron(Neuron* neuron) {
    neurons.push_back(neuron);
    if (prevLayer) {
        for (Neuron* prev : prevLayer->getNeurons()) { // connect to all previous layer neurons
            neuron->addSource(prev);
        }
    }
    neuron->addSource(bias); // connect to bias
}

void Layer::setNextLayer(Layer* layer) {
    nextLayer = layer;
}

void Layer::setInputs(vector<int> &inputs) {
    if (inputs.size() == neurons.size() && !prevLayer) { // check if valid input layer and inputs
        for (int i = 0; i < neurons.size(); i++) {
            neurons[i]->setInputVal(inputs[i]);
        }
    }
}
