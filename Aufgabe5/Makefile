CXXFLAGS = -g -std=c++11 -Wall

a_stern: a_stern.cpp distance_graph.h unit.o unit.h text_visualizer.h
	$(CXX) $(CXXFLAGS) -o $@ $^

run: a_stern
	./$<

test: distance_graph.cpp distance_graph.h unit.o unit.h
	$(CXX) $(CXXFLAGS) -o $@ $^

runtest: test
	./$<

.PHONY: run clean

clean:
	rm -f prog distance_graph.o
