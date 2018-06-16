// By Jaquline Reuter und Emma Ahrens, June 2018

#ifndef _DISTANCE_GRAPH_
#define _DISTANCE_GRAPH_

#include <functional>
#include <list>
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>

typedef std::size_t                 VertexT;
typedef std::pair<VertexT,VertexT>  EdgeT;
typedef double                      CostT;

extern const double infty;
extern const VertexT undefinedVertex;

//-------------------------------------------------------------------------------------------------
// Abstrakte Basisklasse zur Repraesentation eines Distanzgraphen
//-------------------------------------------------------------------------------------------------

class DistanceGraph
{
  public:
    typedef std::pair<VertexT,CostT>  LocalEdgeT;
    typedef std::vector<LocalEdgeT>   NeighborT;
    
  protected:
    // Die Anzahl der Knoten im Graphen.
    std::size_t vertexCount;
    
  public:
    DistanceGraph( int num_verts= 0)
      : vertexCount(num_verts) {}
      
    virtual ~DistanceGraph() {}

    // Gibt die Anzahl der Knoten im Graphen zurueck.
    std::size_t numVertices() const { return vertexCount; }

    // Gibt die Nachbarknoten eines gegebenen Knotens v zurueck.
    virtual const NeighborT& getNeighbors( VertexT v) const = 0;
    
    // Heuristik: Schaetzt die Kosten, um vom Knoten "from" zum Knoten "to" zu gelangen.
    virtual CostT estimatedCost( VertexT from, VertexT to) const = 0;
    
    // Gibt die wahren Kosten c an, um vom Knoten "from" zum Knoten "to" zu gelangen.
    // Existiert zwischen den beiden Knoten keine Kante, werden die Kosten mit infty bewertet.
    virtual CostT cost( VertexT from, VertexT to) const = 0;
};
//-------------------------------------------------------------------------------------------------
// Klasse zur Implementierung von Graphen, für deren Knoten die Position durch Koordinaten gegeben ist
// Benutze diese Klasse für die Graphen 1 und 2 (Bei Graph 2 müsste man sich das nochmal überlegen! TODO)
//-------------------------------------------------------------------------------------------------

class CoordinateGraph : public DistanceGraph {
  private:
    std::vector<NeighborT> vertices;
    double * northSouth;
    double * eastWest;

    //typedef std::size_t                 VertexT;
    //typedef std::pair<VertexT,VertexT>  EdgeT;
    //typedef double                      CostT;
    //typedef std::pair<VertexT,CostT>  LocalEdgeT;
    //typedef std::vector<LocalEdgeT>   NeighborT;

  public:
    CoordinateGraph(int num_verts = 0) :  DistanceGraph(num_verts) { //Warum kann ich das nicht außerhalb der Klasse definieren!!??!?! Irgendwas mit vtable! TODO
        NeighborT dummy;
        vertices.resize(num_verts, dummy);
        northSouth = new double [num_verts];
        eastWest = new  double [num_verts];
    }

    const NeighborT& getNeighbors(VertexT v) const override {   //& steht in diesem Fall für Pass By Reference!
        if (vertices.size() > v) {
            return vertices[v];
        } else {
            std::cerr << "Fehler in CoordinateGraph::getNeighbors(VertexT): Ungültiger Index!\n";
            exit(0);
        }
    };
    
    void resize(int num_verts) {
        vertexCount = num_verts;
        NeighborT dummy;
        vertices.resize(num_verts, dummy);
        northSouth = new double [num_verts];
        eastWest = new double [num_verts];
    };

    void addEdge(VertexT from, VertexT to, CostT cost) {
        LocalEdgeT edge;
        edge.first = to;
        edge.second = cost;
        vertices[from].push_back(edge);
    }

    void addCoordinates(VertexT v, double ns, double ew) {
        northSouth[v] = ns;
        eastWest[v] = ew;
    }

    CostT estimatedCost( VertexT from, VertexT to) const override {
        return sqrt(pow(northSouth[to] - northSouth[from],2) + pow(eastWest[to] - eastWest[from],2));
    };

    CostT cost( VertexT from, VertexT to) const override {
        NeighborT neighbors = vertices[from];
        for (auto edge : neighbors) {
            if (edge.first == to) {
                return edge.second;
            }
        }
        return 100000.; //Change to infty TODO
    };

    void print() {
        std::cout << "Printing Graph:\n";
        std::cout << "Edges:\n";
        for (std::size_t i = 0; i < vertexCount; i++) {
            std::cout << i;
            for (std::size_t j = 0; j < vertices[i].size(); j++) {
                std::cout << "\t" << vertices[i][j].second << " " << vertices[i][j].first << std::endl;
            }
        }
        std::cout << "Coordinates:\n";
        for (std::size_t i = 0; i < vertexCount; i++) {
            std::cout << i << " " << northSouth[i] << " " << eastWest[i] << std::endl;
        }
    };
};

std::istream& operator>> (std::istream& in, CoordinateGraph& graph) {
    int num_verts, num_edges;
    in >> num_verts >> num_edges;
    graph.resize(num_verts);

    for (int i = 0; i < num_edges; i++) {
        size_t from, to;
        double cost;

        in >> from >> to >> cost;
        graph.addEdge(from, to, cost);

    }

    for (int i = 0; i < num_verts; i++) {
        double ns, ew;
        in >> ns >> ew;
        graph.addCoordinates(i, ns, ew);
    }

    return in;
}

//-------------------------------------------------------------------------------------------------
// Klasse zur Implementierung von Graphen, deren Knotenabstände in Kilometer oder Minuten gegeben ist.
// Benutze diese Klasse für Graphen 3 und 4.
//-------------------------------------------------------------------------------------------------

class SimpleDistanceGraph : public DistanceGraph {
  private:
    std::vector<NeighborT> vertices;
    CostT edge_max;

    //typedef std::size_t                 VertexT;
    //typedef std::pair<VertexT,VertexT>  EdgeT;
    //typedef double                      CostT;
    //typedef std::pair<VertexT,CostT>  LocalEdgeT;
    //typedef std::vector<LocalEdgeT>   NeighborT;
  public:
    SimpleDistanceGraph(double edge_max, int num_verts = 0) : DistanceGraph(num_verts) {//Copied
        (*this).edge_max = edge_max;
        NeighborT dummy;
        vertices.resize(num_verts, dummy);
    }

    //Destruktor notwenig? TODO

    void resize(int num_verts) {//Copied
        vertexCount = num_verts;
        NeighborT dummy;
        vertices.resize(num_verts, dummy);
    };

    void addEdge(VertexT from, VertexT to, CostT cost) {//Copied
        LocalEdgeT edge;
        edge.first = to;
        edge.second = cost;
        vertices[from].push_back(edge);
    }

    const NeighborT& getNeighbors(VertexT v) const override {
        if (vertices.size() > v) {
            return vertices[v];
        } else {
            std::cerr << "Fehler in SimpleDistanceGraph::getNeighbors(VertexT): Ungültiger Index!\n";
            exit(0);
        }
    };
    
    CostT estimatedCost( VertexT from, VertexT to) const override {
        CostT c = cost(from, to);

        if (c == 100000) {   //Change to infty TODO
            return edge_max;
        } else {
            return c;
        }
    };

    CostT cost( VertexT from, VertexT to) const override {
        NeighborT neighbors = vertices[from];
        for (auto edge : neighbors) {
            if (edge.first == to) {
                return edge.second;
            }
        }
        return 100000.; //Change to infty TODO
    };

    void print() {
        std::cout << "Printing Graph:\n";
        std::cout << "Edges:\n";
        for (std::size_t i = 0; i < vertexCount; i++) {
            std::cout << i;
            for (std::size_t j = 0; j < vertices[i].size(); j++) {
                std::cout << "\t" << vertices[i][j].second << " " << vertices[i][j].first << std::endl;
            }
        }
    };
};

std::istream& operator>> (std::istream& in, SimpleDistanceGraph& graph) {
    int num_verts, num_edges;
    in >> num_verts >> num_edges;
    graph.resize(num_verts);

    for (int i = 0; i < num_edges; i++) {
        size_t from, to;
        double cost;

        in >> from >> to >> cost;
        graph.addEdge(from, to, cost);

    }

    return in;
}

//-------------------------------------------------------------------------------------------------
// Abstrakte Basisklasse zur Repraesentation eines Distanzgraphen
//-------------------------------------------------------------------------------------------------

/*class MazeGraph : public DistanceGraph {
  public:
    DistanceGraph(int num_verts = 0);

    //Destruktor notwenig?

    const NeighborT& getNeighbors( VertexT v) const override;
    CostT estimatedCost( VertexT from, VertexT to) const override;
    CostT cost( VertexT from, VertexT to) const override;
};*/

#endif
