CXXFLAGS = -g

prog: vierGewinnt.cpp Spielbrett.o Spielbrett.h unit.h unit.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

Spielbrett.o: Spielbrett.cpp Spielbrett.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm Spielbrett.o
