CC=g++
CXX=g++
CFLAGS+=-std=c++11 -O3 -march=native -ffast-math -DNDEBUG -fopenmp -I./lib/include
LDFLAGS+=-lgomp -L./lib/lib -lflann

all:
	$(CC) -o tester tester.cpp $(CFLAGS) $(LDFLAGS)
