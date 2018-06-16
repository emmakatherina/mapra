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
    
    //Tests for class 
    in.open("daten/Graph3.dat");
    SimpleDistanceGraph graph2 (1500);
    in >> graph2;
    in.close();

    std::cout << "Estimated cost 2-3: " << graph2.estimatedCost(2,3) << endl;
    std::cout << "Real cost 2-3: " << graph2.cost(2,3) << endl;

    return 0;
}
