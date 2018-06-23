// By Jaqueline Reuter and Emma Ahrens, June 2018

#include "text_visualizer.h"
#include "unit.h"
#include "distance_graph.h"
#include <algorithm>
#include <fstream>
#include <list>

using std::cout;
using std::endl;

void Dijkstra(const DistanceGraph& g, GraphVisualizer& v, VertexT start, std::vector<CostT>& kostenZumStart) {
    // ...
}

std::size_t findPosition(const std::vector<DistanceGraph::LocalEdgeT> queue, DistanceGraph::LocalEdgeT edge) {
	for (std::size_t i = 0; i < queue.size(); i++) {
		if (queue[i].first == edge) {
			return i;
		}
	}
	return queue.size();
}

bool A_star(const DistanceGraph& g, GraphVisualizer& v, VertexT start, VertexT ziel, std::list<VertexT>& weg) {
	/*LocalEdgeT edge (1,5.0), edge2 (2,3.);
	queue.push_back(edge);
	queue.push_back(edge2);
	std::make_heap(queue.begin(), queue.end(), compare());
	cout << queue[0].first << " " << queue[1].first << endl;*/

	typedef DistanceGraph::LocalEdgeT LocalEdgeT;
	typedef DistanceGraph::NeighborT NeighborT;
	class compare {
	  public:
		bool operator() (const LocalEdgeT left, const LocalEdgeT right) {
			return left.second < left.first;
		}
	};
	std::vector<LocalEdgeT> queue;

    //start in priority queue
	queue.push_back(LocalEdgeT (start, g.estimatedCost(start, ziel)));
	//array für weg initialisieren
	VertexT * predecessors [g.numVertices()];
	bool * examined [g.numVertices()]; //standardmäßig auf false setzen!

	//kleinsten knoten aus priority queue nehmen und nachbarn mit kosten in priority queue schreiben
	std::make_heap(queue.begin(), queue.end(), compare());
	LocalEdgeT current = queue[0];
	NeighborT neighbors = g.getNeighbors(current.first);
	for (LocalEdgeT n : neighbors) {
		if (!examined[n.first]) {
			std::size_t position = findPosition(queue, n);
			/*
			if (position != queue.end()) { //hier nochmal checken!
				CostT newCosts = g.cost(start, queue[position].first) + g.estimatedCost(queue[position].first, ziel);
				if (newCosts < queue[position].second) {
					queue[position].second = newCosts;
					std::make_heap(queue.begin(), queue.end(), compare()); //Könnte man optimieren!
				}
			} else {
				CostT newCosts = g.cost(start, n.first) + g.estimatedCost(n.first, ziel);
				queue.push_back(LocalEdgeT (n.first, newCosts);
				std::push_heap(queue.begin(), queue.end());
			}
			*/
		}
	}

	//bei nachbarn vorgänger in array setzen, falls nachbar schon in priority queue, dann updaten
	//aber nur falls weg kürzer!

	//weg aus array auslesen und in liste speichern
    return false; // Kein Weg gefunden.
}

int main()
{
    // Frage Beispielnummer vom User ab
    
    // Lade die zugehoerige Textdatei in einen Graphen
    // PruefeHeuristik
    
    // Loese die in der Aufgabenstellung beschriebenen Probleme fuer die jeweilige Datei
    // PruefeDijkstra / PruefeWeg

	//------------------------------
	
	GraphVisualizer * visualizer;
	std::list<VertexT> weg;

    std::ifstream in ("daten/Graph3.dat");
    SimpleDistanceGraph graph (1500);
    in >> graph;
    in.close();

	A_star(graph, *visualizer, 0, 3, weg);
    
    return 0;
}
 
