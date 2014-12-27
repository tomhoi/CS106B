#include "neuron.h"
#include "math.h"

double sigmoid(double val);

Neuron::Neuron(double weight) {
    this->weight = weight;
    outputVal = 0;
}

Neuron::Neuron() {
    Neuron((rand() % 100) / 100.0); // between 0 and 1, hundredths place
}

Neuron::~Neuron() {
    
}

double Neuron::calculateOutput() {
    // calculate
    double result = 0;
    for (Neuron* neuron : inputs) { // sum
        result += neuron->getOutputVal() * neuron->getWeight();
    }
    result = sigmoid(result); // activation
    
    // set as own output val and return
    outputVal = result;
    return result;
}

double sigmoid(double val) {
    return (1 / (1 + exp(val)));
}

double Neuron::getOutputVal() {
    return outputVal;
}

double Neuron::getWeight() {
    return weight;
}

double Neuron::adjustWeight(double deltaWeight) {
    weight += deltaWeight;
    return weight;
}

void Neuron::addInputNeuron(Neuron* input) {
    inputs.insert(input);
    input->addOutputNeuron(this);
}

void Neuron::addOutputNeuron(Neuron* output) {
    outputs.insert(output);
    output->addInputNeuron(this); // make the backwards connection as well
}
