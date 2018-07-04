// By Jaqueline Reuter and Emma Ahrens, June 2018

#include "text_visualizer.h"
#include "unit.h"
#include "distance_graph.h"
#include <algorithm>
#include <fstream>
#include <list>

using std::cout;
using std::endl;

bool IsElem(std::vector<VertexT>& s, VertexT v){
	for (std::size_t i = 0; i < s.size(); i++){
		if(s[i] == v)
			return true;
	}
	return false;
}

void Dijkstra(const DistanceGraph& g, /*GraphVisualizer& x,*/ VertexT start, std::vector<CostT>& kostenZumStart) {
	std::vector<VertexT> S;
    	S.push_back(start);
	size_t z = g.numVertices();
	kostenZumStart.resize(z,infty);
	kostenZumStart[start]=0;
	VertexT v = start+1;
	
	for(std::size_t i = 0; i < z; i++){
		if(i == start)
			continue;                 
		else{
			double c = g.cost(start,i);
			kostenZumStart[i]=c;
		}
	}
	while(S.size()!=z){
	
		std::size_t l=0;
		while (IsElem(S,l)){
			l++;
		}
		v = l;
		
		for(std::size_t j = 0; j < z; j++){
			if(IsElem(S,j))
				continue;
			else if(kostenZumStart[j] <= kostenZumStart[v] && kostenZumStart[j] != 0){
				v = j;	
						
			}
		}
		S.push_back(v);
		for(std::size_t k = 0; k < z; k++){
			CostT f = kostenZumStart[v]+ g.cost(v,k);
			if(IsElem(S,k))
				continue;
			else if (f < kostenZumStart[k]){
				kostenZumStart[k] = f;
			}
		}
	}
}

std::size_t findPosition(const std::vector<DistanceGraph::LocalEdgeT> queue, DistanceGraph::LocalEdgeT edge) {
	for (std::size_t i = 0; i < queue.size(); i++) {
		if (queue[i].first == edge.first) {
			return i;
		}
	}
	return queue.size();
}

void makePath(VertexT * predecessors, std::list<VertexT>& weg, VertexT start, VertexT ziel, std::size_t vertexCount) {
	weg.resize(0);
	VertexT current = ziel;
	weg.push_front(current);
	while (predecessors[current] != vertexCount) {
		current = predecessors[current];
		weg.push_front(current);
	}
}

void initializeVertexArray(VertexT * predecessors, std::size_t length) {
	for (std::size_t i = 0; i < length; i++)
		predecessors[i] = length;
}

void initializeBoolArray(bool * examined, std::size_t length) {
	for (std::size_t i = 0; i < length; i++)
		examined[i] = false;
}

bool A_star(const DistanceGraph& g, GraphVisualizer& v, VertexT start, VertexT ziel, std::list<VertexT>& weg) {
	typedef DistanceGraph::LocalEdgeT LocalEdgeT;
	typedef DistanceGraph::NeighborT NeighborT;
	class compare {
	  public:
		bool operator() (const LocalEdgeT& left, const LocalEdgeT& right) {
			return left.second > right.second;
		}
	};
	std::vector<LocalEdgeT> queue;
	std::size_t numVertices = g.numVertices();
	VertexT * predecessors = new VertexT [numVertices];
	initializeVertexArray(predecessors, numVertices);
	CostT * realCostsTo = new CostT [numVertices];
	bool * examined = new bool [numVertices]; //standardmäßig auf false setzen!
	initializeBoolArray(examined, numVertices);

	queue.push_back(LocalEdgeT (start, g.estimatedCost(start, ziel)));
	realCostsTo[start] = 0;

	std::make_heap(queue.begin(), queue.end(), compare());

	do {
		LocalEdgeT current = queue[0];
		std::pop_heap(queue.begin(), queue.end());
		queue.pop_back();

		if (current.first == ziel) {
			makePath(predecessors, weg, start, ziel, numVertices);
			return true;
		}

		examined[current.first] = true;

		NeighborT neighbors = g.getNeighbors(current.first);
		for (LocalEdgeT n : neighbors) {
			if (examined[n.first])
				continue;

			CostT realCosts = realCostsTo[current.first] + g.cost(current.first, n.first);

			std::size_t position = findPosition(queue, n);
			if ((position != queue.size()) && (realCostsTo[n.first] <= realCosts))
					continue;

			predecessors[n.first] = current.first;
			realCostsTo[n.first] = realCosts;

			CostT estimatedTotal = realCosts + g.estimatedCost(n.first, ziel);
			if (position != queue.size()) {
				queue[position].second = estimatedTotal;
			} else {
				queue.push_back(LocalEdgeT (n.first, estimatedTotal));
			}
		}
		std::make_heap(queue.begin(), queue.end(), compare());
	} while (queue.size() != 0);

	// delete!!
	delete [] predecessors;
	delete [] realCostsTo;
	delete [] examined;
    return false; // Kein Weg gefunden.
}

int main()
{
    // Frage Beispielnummer vom User ab
	int example = 1;
	cout << "Beispiel (1-10): ";
	std::cin >> example;
    
    // Lade die zugehoerige Textdatei in einen Graphen
    // PruefeHeuristik
    
	std::ifstream in;
	GraphVisualizer * visualizer;
	std::list<VertexT> weg;
	std::vector<CostT> kostenZumStart;

	if ((example == 1) || (example == 2)) {
		(example == 1) ? in.open("daten/Graph1.dat") : in.open("daten/Graph2.dat");
		CoordinateGraph graph;
		in >> graph;
		in.close();

		for (std::size_t i = 0; i < graph.numVertices(); i++) {
			Dijkstra(graph, i, kostenZumStart);
			PruefeDijkstra (example, i, kostenZumStart);
		}

		// A*
		for (std::size_t i = 0; i < graph.numVertices(); i++) {
			for (std::size_t j = 0; j < graph.numVertices(); j++) {
				bool pathFound = A_star(graph, *visualizer, i, j, weg);
				if (pathFound) {
					PruefeWeg(example, weg);
				}
			}
		}
	} else if ((example == 3) || (example == 4)) {
		SimpleDistanceGraph graph (1500);
		if (example == 3) {
			in.open("daten/Graph3.dat");
		} else {
			in.open("daten/Graph4.dat");
			graph.setMaxEdge(120);
		}
		in >> graph;
		in.close();

		for (std::size_t i = 0; i < graph.numVertices(); i++) {
			Dijkstra(graph, i, kostenZumStart);
			PruefeDijkstra (example, i, kostenZumStart);
		}

		// A*
		for (std::size_t i = 0; i < graph.numVertices(); i++) {
			for (std::size_t j = 0; j < graph.numVertices(); j++) {
				A_star(graph, *visualizer, i, j, weg);
				PruefeWeg(example, weg);
			}
		}
	} else if ((example >= 5) && (example <= 9)) {
		MazeGraph graph;
		switch (example) {
			case 5:
				in.open("daten/Maze1.dat");
				break;
			case 6:
				in.open("daten/Maze2.dat");
				break;
			case 7:
				in.open("daten/Maze3.dat");
				break;
			case 8:
				in.open("daten/Maze4.dat");
				break;
			case 9:
				in.open("daten/Maze5.dat");
				break;
		}
		in >> graph;
		in.close();


		// A*
		cout << StartZielPaare(example).size() << endl;
		for ( auto pair : StartZielPaare(example)) {
			auto start = pair.first;
			auto goal  = pair.second;
			bool pathFound = A_star(graph, *visualizer, start, goal, weg);
			if (pathFound) {
				PruefeWeg(example, weg);
			}
		}
	} else if (example == 10) {
		int breite;
		cout << "Breite des zufälligen Labyrinths: ";
		std::cin >> breite;
		VertexT start, ziel;
		MazeGraph graph (breite);
		std::vector<CellType> graphContent = ErzeugeLabyrinth(breite, breite, 1992);
		uebersetzeLabyrinth(graphContent, graph, breite, start, ziel);
		A_star(graph, *visualizer, start, ziel, weg);
		PruefeWeg(example, weg);
	}
    
    return 0;
}
 
