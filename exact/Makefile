CC=g++
CXX=g++
CFLAGS+=-std=c++11 -O3 -march=native -fno-rtti -fno-stack-protector -fno-exceptions -ffast-math -DNDEBUG -DEIGEN_DONT_PARALLELIZE -fopenmp -I./
LDFLAGS+=-lgomp

all:
	$(CC) -o tester tester.cpp $(CFLAGS) $(LDFLAGS)
