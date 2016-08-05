CC=g++
CXX=g++
CFLAGS+=-std=c++11 -O3 -march=native -ffast-math -DNDEBUG -DEIGEN_DONT_PARALLELIZE -Wno-ignored-attributes -fopenmp -Ilib/ -Iexternal/
LDFLAGS+=-lgomp

all:
	$(CC) $(CFLAGS) $(LDFLAGS) tester.cpp -o tester
