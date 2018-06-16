// By Jaqueline Reuter and Emma Ahrens, June 2018

#include "distance_graph.h"
#include <fstream>

int main () {
    std::cout << "Hello World!" << std::endl;
    
    std::ifstream in ("daten/Graph1.dat");
    CoordinateGraph graph;
    double a;
    in >> graph;
    graph.addEdge(2,3,0.7);
    graph.print();

    return 0;
}
