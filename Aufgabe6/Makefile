CXXFLAGS = -Wall -pedantic -std=c++11 

run: loesung
	./loesung

loesung.o: loesung.cpp
	$(CXX) $(CXXFLAGS) -c $<

loesung: loesung.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f loesung loesung.o

.PHONY: clean run
