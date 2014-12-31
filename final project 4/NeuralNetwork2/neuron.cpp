#include "neuron.h"
#include "math.h"

double sigmoid(double val);

Neuron::Neuron() {
    hasInputVal = false;
}

Neuron::~Neuron() {
    
}

double Neuron::calculateOutput() {
    // calculate
    double result = 0;
    if (hasInputVal && sources.empty()) { // bias or input neuron
        result += inputVal;
    } else { // hidden or output neuron
        for (Connection* connection : sources) { // sum
            result += connection->getWeight() * connection->getSource()->getOutputVal();
        }
        result = sigmoid(result); // activation
    }
    
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

void Neuron::setInputVal(int val) {
    inputVal = val;
    hasInputVal = true;
}

void Neuron::addSource(Neuron* source) {
    Connection* connection = new Connection(this, source);
    sources.push_back(connection);
}

void Neuron::addSource(Connection* connection) {
    if (connection->getDestination() == this) {
        sources.push_back(connection);
    }
}

vector<Connection*> Neuron::getSources() {
    return sources;
}
