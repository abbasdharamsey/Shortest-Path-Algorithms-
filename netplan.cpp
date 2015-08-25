#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <istream>
#include <sstream>
#include <climits>

#include "UndirectedGraph.hpp"

using namespace std;

/**
 * Entry point into the netplan program.
 *
 * -Reads a file from the filesystem according to the specification for
 *  PA3, creating an UndirectedGraph.
 * -Finds the total cost & ping time of the graph as presented in the input
 *  file.
 * -Determines the minimum cost graph from the original graph.
 * -Finds the total cost & ping time of the minimum cost graph.
 * -Finds the change of cost & ping time from the original graph to the
 *  minimum cost graph.
 * -Prints the results to stdout.
 *
 * Usage:
 *   ./netplan infile
 *
 */
int main (int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Unable to open file." << std::endl;
        return EXIT_FAILURE;
    }

    ifstream input (argv[1]);

    if (!input.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return EXIT_FAILURE;
    }
    
    // Checks if there is an empty file
    input.seekg(0, ios_base::end);
    size_t length = input.tellg();
    if(!length) {
        cout << 0 << '\n' << 0 << '\n' << 0 << '\n' << 0 << '\n' << 0 << '\n' << 0 << endl;
        return EXIT_SUCCESS;
    }
    input.seekg(0, ios_base::beg);

    UndirectedGraph *mainGraph = new UndirectedGraph();
    string curLine;
    string fromS, toS;
    unsigned int cost, latency;

    // Convert each line to a stream, parse the stream into different variables 
    // that will be used to create edges between vertices
    while (input.good()) {
       input >> fromS >> toS >> cost >> latency;
       mainGraph->addEdge(fromS, toS, cost, latency);
    }

    UndirectedGraph * MST = mainGraph->minSpanningTree(); 
    unsigned int mainEdgeCost = mainGraph->totalEdgeCost();
    unsigned int mainTotalDistance = mainGraph->totalDistance();
    unsigned int mstEdgeCost = MST->totalEdgeCost();
    unsigned int mstTotalDistance = (mainTotalDistance == UINT_MAX) ? UINT_MAX : MST->totalDistance();
    
    cout << mainEdgeCost  << endl;
    cout << mstEdgeCost << endl;
    cout << mainEdgeCost - mstEdgeCost << endl;
    cout << mainTotalDistance << endl;
    cout << mstTotalDistance << endl;
    cout << mstTotalDistance - mainTotalDistance << endl;

    // destructors
    delete mainGraph;
    delete MST;

    return EXIT_SUCCESS;
}
