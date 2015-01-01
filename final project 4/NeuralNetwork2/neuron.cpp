#include "neuron.h"
#include "math.h"

double sigmoid(double val);
double calculateOutput(Neuron* curr);

Neuron::Neuron() {
    hasInputVal = false;
}

Neuron::~Neuron() {
    
}

double Neuron::feedForward() {
    return calculateOutput(this);
}

double calculateOutput(Neuron *curr) {
    if (curr->getHasInputVal()) { // base case (bias or input neuron)
        return curr->getInputVal();
    } else {
        double result = 0;
        for (Connection* connection : curr->getSources()) {
            result += connection->getWeight() * calculateOutput(connection->getSource());
        }
        result = sigmoid(result);
        return result;
    }
}

double Neuron::getInputVal() {
    return inputVal;
}

bool Neuron::getHasInputVal() {
    return hasInputVal;
}

double sigmoid(double val) {
    return (1 / (1 + exp(val)));
}

void Neuron::setInputVal(double val) {
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
