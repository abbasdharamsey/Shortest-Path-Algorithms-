#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

#include <iostream>
#include <climits>
#include <utility>
#include <queue>

using namespace std;

UndirectedGraph::~UndirectedGraph() {
    // loops through the unordered map vertices calling delete on each vertex
    for (const pair<basic_string<char>, Vertex *> head : vertices) {
        delete head.second;
    }
 }

void UndirectedGraph::addEdge(const std::string &from, const std::string &to,
            unsigned int cost, unsigned int length) {
    Vertex* fromV; 
    Vertex* toV;

    // If the from/to vertex is not in the graph, create it, insert it into the graph, and set a pointer
    // to it. Else, just set it to a pointer
    unordered_map<std::string, Vertex*>::const_iterator finder = vertices.find(from);
    if (finder == vertices.end()) {
        fromV = new Vertex(from);
        vertices.insert(make_pair(from, fromV));
    } 
    else fromV = finder->second;

    finder = vertices.find(to);
    if (finder == vertices.end()) {
        toV = new Vertex(to);
        vertices.insert(make_pair(to, toV));
    }
    else toV = finder->second;

    fromV->addEdge(toV, cost, length);
    toV->addEdge(fromV, cost, length);
}

unsigned int UndirectedGraph::totalEdgeCost() const {
    unsigned int totalEdgeCost = 0;

    // Loop through the vertices adding each edge cost
    for (const pair<basic_string<char>, Vertex *> head : vertices) 
        totalEdgeCost += head.second->totalEdgeCost();

    return totalEdgeCost/2;
}

// Prim's Minimum Spanning Tree
UndirectedGraph * UndirectedGraph::minSpanningTree() {
    // create an Undirected Graph that will only contain the vertex's used in the MST
    UndirectedGraph * MST = new UndirectedGraph();
    
    priority_queue<Edge> pq;
    Vertex* startV; 

    for (const pair<basic_string<char>, Vertex *> head : vertices) 
        head.second->setVisited(false);

    // set a pointer to the starting vertex (the first vertice in the unordered map for simplicity)
    unordered_map<std::string, Vertex*>::const_iterator finder = vertices.begin();
    startV = finder->second;

    // push all the edges of the startV into the priority queue
    for (const pair<const basic_string<char>, Edge> head : startV->edges) {
        pq.push(head.second);
        startV->setVisited(true);
    }
    
    while(pq.size()) {
        Edge currE = pq.top();
        pq.pop();

        if(currE.getTo()->wasVisited()) continue;
            
        // If edge wasn't visited, add it to the MST graph, mark the To vertex as visited
        else {
            MST->addEdge(currE.getFrom()->getName(), currE.getTo()->getName(), currE.getCost(), currE.getLength());
            currE.getTo()->setVisited(true);
        }

        // push the edges of the To vertex into the priority queue
        for (const pair<const basic_string<char>, Edge> head : currE.getTo()->edges)
            pq.push(head.second);
    }

    // return the Minimum Spanning Tree for the driver to render the information
    return MST;
}

// Dijikstra's Shortest Path
unsigned int UndirectedGraph::totalDistance(const std::string &from) {
    unsigned int numOfVisited = 0;
    unsigned int distance = 0;
    Vertex* fromV;
    priority_queue<pair<Vertex*, unsigned int>, 
        vector<pair<Vertex*, unsigned int>>, DijkstraVertexComparator> pq;

    // set each vertex's distance to infinity and visited status to false
    for (const pair<basic_string<char>, Vertex *> head : vertices) {
        head.second->setDistance(UINT_MAX);
        head.second->setVisited(false);
    }

    // find the parameter vertex in vertices, set a pointer to it, set it's distance to 0, 
    // then push it onto the priority queue
    unordered_map<std::string, Vertex*>::const_iterator finder = vertices.find(from);
    fromV = finder->second;
    fromV->setDistance(0);
    pq.push(make_pair(fromV, 0));
    
    while (pq.size()) {
        Vertex* currV = (pq.top()).first;
        
        if (currV->wasVisited()) 
            pq.pop();
        
        // If currV wasn't visited, set visited to true, sum the distance from currV 
        else {
            currV->setVisited(true);
            numOfVisited++;

            currV->setDistance(pq.top().second);
            distance += currV->getDistance();

            // push the vertices that aren't visited but connected to currV onto the priority queue
            for (const pair<const basic_string<char>, Edge> head : currV->edges) {
                if (!head.second.getTo()->wasVisited())
                    pq.push(make_pair(head.second.getTo(), currV->getDistance() + head.second.getLength()));
            }
        }
    }

    // if the graph is connected return the found distance, if it's not return UINT_MAX 
    if(numOfVisited == vertices.size())
        return distance;
    else
        return UINT_MAX;
}

unsigned int UndirectedGraph::totalDistance() {
    unsigned int totDistance = 0;
    unsigned long int currDistance = 0;
    
    // add the current distance of the current vertex to totDistance
    for (const pair<basic_string<char>, Vertex *> head : vertices) { 
        currDistance = totalDistance(head.second->getName());
        
        if (currDistance == UINT_MAX) return UINT_MAX; 
        else totDistance+=currDistance;
    }

    return totDistance;
}