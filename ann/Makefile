CC=g++
CXX=g++
CFLAGS+=-std=c++11 -Wall -Wextra -O3 -march=native -ffast-math -DNDEBUG -fopenmp -I./lib/include
LDFLAGS+=-L./lib/lib -lANN -lgomp

all:
	$(CC) $(CFLAGS) tester.cpp -o tester $(LDFLAGS)
