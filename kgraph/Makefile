CC = g++
CXXFLAGS = -O3 -fopenmp -fPIC -std=c++11 -I./lib -g
LDFLAGS = -L./lib
LDLIBS = -lkgraph -lboost_timer -lboost_chrono -lgomp

.PHONY:	clean

tester:	tester.cpp
	$(CC) -o tester tester.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	rm tester
