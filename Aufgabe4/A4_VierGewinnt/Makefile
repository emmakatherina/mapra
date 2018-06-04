CXXFLAGS = -g -O3 -std=c++11 -Wall
LIBS = -lX11 -pthread

prog: vierGewinnt.cpp Spielbrett.o unit.o plotx11.o
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $^

netz: vierGewinntNetzwerk.cpp Spielbrett.o unit.o plotx11.o
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $^

run: prog
	./prog

Spielbrett.o: Spielbrett.cpp Spielbrett.h
	$(CXX) $(CXXFLAGS) $(LIBS) -c $<

.PHONY: clean run
clean:
	rm -f Spielbrett.o prog netz
