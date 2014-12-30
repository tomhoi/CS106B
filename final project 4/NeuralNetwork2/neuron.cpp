#include "neuron.h"
#include "math.h"

double sigmoid(double val);

Neuron::Neuron() {
    
}

Neuron::~Neuron() {
    
}

double Neuron::calculateOutput() {
    // calculate
    double result = 0;
    for (Connection* connection : sources) { // sum
        result += connection->getWeight() * connection->getSource()->getOutputVal();
    }
    result = sigmoid(result);
    
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

void Neuron::addConnection(Neuron* source) {
    sources.insert(source);
}

void Neuron::addConnection(Connection* connection) {
    if (connection->getDestination() == this) {
        sources.insert(connection);
    }
}

set<Connection*> Neuron::getSources() {
    return sources;
}
