// By Jaquline Reuter und Emma Ahrens, June 2018

#ifndef _DISTANCE_GRAPH_
#define _DISTANCE_GRAPH_

#include "unit.h"
#include <iostream>
#include <cmath>

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
        return infty;
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

	void setMaxEdge(double edge_max) {
		(*this).edge_max = edge_max;
	}

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

        if (c == infty) {
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
        return infty;
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

class MazeGraph : public DistanceGraph {
  private:
    bool ** mazeField;
    int width;

    typedef std::pair<std::size_t,std::size_t> indexT;

  public:
    MazeGraph(int width = 0) : DistanceGraph(width*width) {
        (*this).width = width;

        mazeField = new bool * [width];
        for (int i = 0; i < width; i++) {
            mazeField[i] = new bool [width];
        }
    };

    //Destruktor notwenig?

    void resize(int width) {
        vertexCount = width*width;
        (*this).width = width;

        mazeField = new bool * [width];
        for (int i = 0; i < width; i++) {
            mazeField[i] = new bool [width];
        }
    };

    void setPassage(int i, int j, bool passage) {
        if ((i > -1) && (i < width) && (j > -1) && (j < width)) {
            mazeField[i][j] = passage;
        }
    }

    indexT vertexToIndex(VertexT v) const {
        indexT result;
        result.second = v % width;
        result.first = (v - result.second)/width;
        return result;
    };

    int indexToVertex(int i, int j) const {
        if ((i < 0) || (j < 0) || (i > 7) || (j > 7)) {
            return -1;
        }
        return j + i*width;
    };

    const NeighborT& getNeighbors( VertexT v) const override {
        NeighborT * result = new NeighborT;
        indexT currentPosition = vertexToIndex(v);
        
        //oben
        indexT neighbourI = std::make_pair(currentPosition.first - 1, currentPosition.second);
        //unten
        indexT neighbourI2 = std::make_pair(currentPosition.first + 1, currentPosition.second);
        //rechts
        indexT neighbourI3 = std::make_pair(currentPosition.first, currentPosition.second + 1);
        //links
        indexT neighbourI4 = std::make_pair(currentPosition.first, currentPosition.second - 1);

        indexT neighbourIndices [4] = {neighbourI, neighbourI2, neighbourI3, neighbourI4};

        for (indexT index : neighbourIndices) {
            LocalEdgeT edge;
            int vertex = indexToVertex(index.first, index.second);

            if (vertex> -1) {
                edge.first = vertex;
                mazeField[index.first][index.second] ? edge.second = 0 : edge.second = 1;
                (*result).push_back(edge);
            }
        }

        return *result;
    };

    CostT estimatedCost( VertexT from, VertexT to) const override {
        if (cost(from, to) != infty) {
            return cost(from, to);
        } else {
            indexT fromI = vertexToIndex(from);
            indexT toI = vertexToIndex(to);
            if (mazeField[fromI.first][fromI.second] && mazeField[toI.first][toI.second]) {
                return 0;
            } else {
                return 1;
            }
        }
    };

    CostT cost( VertexT from, VertexT to) const override {
        NeighborT neighbors = getNeighbors(from);
        for (std::size_t i = 0; i < neighbors.size(); i++) {
            if (neighbors[i].first == to) {
                indexT fromI = vertexToIndex(from);
                indexT toI = vertexToIndex(to);
                if (mazeField[fromI.first][fromI.second] && mazeField[toI.first][toI.second]) {
                    return 0;
                } else {
                    return 1;
                }
            }
        }
        return infty;
    };
};

std::istream& operator>> (std::istream& in, MazeGraph& graph) {
    int a, b;
    in >> a >> b;
    graph.resize(a);
   
    char c = '.';
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            in >> c;
            if (c == '#') {
                graph.setPassage(i,j,false);
            } else if (c == '.') {
                graph.setPassage(i,j,true);
            }
        }
    }

    return in;
}

#endif
