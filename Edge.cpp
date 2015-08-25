#include "Edge.hpp"

Vertex *Edge::getFrom() const {
    return from;
}

Vertex *Edge::getTo() const {
    return to;
}

void Edge::setCost(unsigned int cost) {
    this->cost = cost;
}

unsigned int Edge::getCost() const {
    return cost;
}

void Edge::setLength(unsigned int length) {
    this->length = length;
}

unsigned int Edge::getLength() const {
    return length;
}

bool Edge::operator<(const Edge &right) const {
    return (this->cost > right.cost);
}
