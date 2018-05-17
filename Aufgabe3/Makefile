CXXFLAGS = -O2 -Wall

prog: iterations.cpp vektor.o matrix.o unit.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test: test.cpp vektor.o matrix.o
	$(CXX) $(CXXFLAGS) -o $@ $^

vektor.o: vektor.cpp vektor.h matrix.h
	$(CXX) $(CXXFLAGS) -c $<

matrix.o: matrix.cpp matrix.h vektor.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm -f test vektor.o matrix.o prog Jacobi.txt GS.txt CG.txt
