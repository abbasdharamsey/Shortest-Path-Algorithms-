#include "Vertex.hpp"

#include <unordered_map>
#include <utility>

using namespace std;

bool Vertex::addEdge(Vertex *to, unsigned int cost, unsigned int length) {
    unordered_map<std::string, Edge>::const_iterator finder = edges.find(to->getName());
    
    // If the edge doesn't exist in edges, create and add it
    if (finder == edges.end()) {
        Edge newEdge(this, to, cost, length);
        edges.insert(make_pair(to->getName(), newEdge));

        return true;
    } 

    // If the edge does exist, update its cost and length
    Edge foundEdge = finder->second;
    foundEdge.setCost(cost);
    foundEdge.setLength(length);

    return false;
}

const std::string &Vertex::getName() const {
    return this->name;
}

unsigned int Vertex::getDistance() const {
    return distance;
}

void Vertex::setDistance(unsigned int distance) {
    this->distance = distance;
}

bool Vertex::wasVisited() const {
    return visited;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

unsigned int Vertex::totalEdgeCost() const {
    unsigned int totalEdgeCost = 0;

    for (const pair<const basic_string<char>, Edge> head : edges) {
        totalEdgeCost += head.second.getCost();
    }

    return totalEdgeCost;
}
