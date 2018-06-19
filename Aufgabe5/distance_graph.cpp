// By Jaqueline Reuter and Emma Ahrens, June 2018

#include "distance_graph.h"
#include <fstream>

using std::cout;
using std::endl;

int main () {
    std::cout << "Hello World!" << std::endl;
    
    // Tests for class CoordinateGraph
    std::ifstream in ("daten/Graph1.dat");
    CoordinateGraph graph1;
    in >> graph1;
    in.close();

    std::cout << "Estimated cost 1-2: " << graph1.estimatedCost(1,2) << std::endl;
    std::cout << "Real cost 1-2: " << graph1.cost(1,2) << endl;
    
    //Tests for class SimpleDistanceGraph
    in.open("daten/Graph3.dat");
    SimpleDistanceGraph graph2 (1500);
    in >> graph2;
    in.close();

    std::cout << "Estimated cost 2-3: " << graph2.estimatedCost(2,3) << endl;
    std::cout << "Real cost 2-3: " << graph2.cost(2,3) << endl;

    //Tests for class MazeGraph
    MazeGraph graph3 (8);
    std::pair<std::size_t, std::size_t> index = graph3.vertexToIndex(16);
    cout << index.first << " " << index.second << endl;
    cout << graph3.indexToVertex(1,7) << endl;
    DistanceGraph::NeighborT n = graph3.getNeighbors(15);
    cout << "Neighbors of 15:\n";
    for (std::size_t i = 0; i < n.size(); i++) {
        cout << n[i].first << " ";
    }
    cout << endl;

    in.open("daten/Maze2.dat");
    in >> graph3;
    in.close();

    std::cout << "Estimated cost 8-9: " << graph3.estimatedCost(8,9) << endl;
    std::cout << "Real cost 8-9: " << graph3.cost(8,9) << endl;
    
    std::cout << "Estimated cost 9-18: " << graph3.estimatedCost(9,18) << endl;
    std::cout << "Real cost 9-18: " << graph3.cost(9,18) << endl;

    return 0;
}
