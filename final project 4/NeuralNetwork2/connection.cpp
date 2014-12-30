#include "connection.h"

Connection::Connection(Neuron* to, Neuron* from) {
    this->weight = (rand() % 100) / 100.0; // between 0 and 1, hundredths place
    this->to = to;
    this->from = from;
}

double Connection::getWeight() {
    return weight;
}

double Connection::adjustWeight(double deltaWeight) {
    weight += deltaWeight;
    return weight;
}

Neuron* Connection::getSource() {
    return from;
}

Neuron* Connection::getDestination() {
    return to;
}
