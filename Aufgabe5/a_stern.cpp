// By Jaqueline Reuter and Emma Ahrens, June 2018

#include "text_visualizer.h"
#include "unit.h"

// KLASSENDEFINITIONEN

// Ein Graph, der Koordinaten von Knoten speichert.
class CoordinateGraph : public DistanceGraph {
private:
    CostT * distances;

public:
    CoordinateGraph ();
    const NeighborT& getNeighbors( VertexT v) const override;
    CostT cost( VertexT from, VertexT to) const override;
};

// Graph, bei dem die Knotepnpunkte durch Koordinaten angegeben sind.
class DistCoordGraph : public CoordinateGraph {
public:
    CostT estimatedCost( VertexT from, VertexT to) const override;
};

// Graph, bei dem die Distanz zwischen Knoten als Zeit (in min) angegeben ist.
class TimeCoordGraph : public CoordinateGraph {
public:
    CostT estimatedCost( VertexT from, VertexT to) const override;
};

// Labyrinth. Hier sind die Kosten zwischen Knoten 1 (Durchgang frei) oder 0 (Wand).
class MazeGraph : public DistanceGraph {
public:
    const NeighborT& getNeighbors( VertexT v) const override;
    CostT cost( VertexT from, VertexT to) const override;
    CostT estimatedCost( VertexT from, VertexT to) const override;
};

// IMPLEMENTIERUNG DER KLASSEN

const DistanceGraph::NeighborT& CoordinateGraph::getNeighbors( VertexT v ) const {
    DistanceGraph::NeighborT * result = new DistanceGraph::NeighborT ();
    return (*result);
}

// ALGORITHMEN ZUR WEGSUCHE

void Dijkstra(const DistanceGraph& g, GraphVisualizer& v, VertexT start, std::vector<CostT>& kostenZumStart) {
    // ...
}

bool A_star(const DistanceGraph& g, GraphVisualizer& v, VertexT start, VertexT ziel, std::list<VertexT>& weg) {
    // ...
    return false; // Kein Weg gefunden.
}

int main()
{
    // Frage Beispielnummer vom User ab
    
    // Lade die zugehoerige Textdatei in einen Graphen
    // PruefeHeuristik
    
    // Loese die in der Aufgabenstellung beschriebenen Probleme fuer die jeweilige Datei
    // PruefeDijkstra / PruefeWeg
    
    return 0;
}
 
