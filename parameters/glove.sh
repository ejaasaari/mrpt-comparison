#!/usr/bin/env bash

DATASET_NAME=glove
DIM=200

MRPT_N_TREES="1 5 10 25 50 75 100 125 150 200 250 300 350 400 500 600 700 800 900 1000"
MRPT_DEPTH="6 7 8 9 10 11 12 13 14"
MRPT_SPARSITY=0.07

MRPT_VOTING_N_TREES="10 25 50 75 100 125 150 200 250 300 350 400 500 600 700 800 900 1000 1250 1500"
MRPT_VOTES="1 2 3 4 5 8 10 12 15 20 25 30 40 50 60 70 80 90 100"

FLANN_N_TREES="1 2 4 8 16 32"
FLANN_CHECKS="0 500 1000 1500 2000 2500 3000 3500 4000 4500 5000 6000 8000 10000 12000 14000 16000 18000 20000 25000 50000 75000 100000 150000 200000 300000 400000"

FLANN_BRANCHING="8 16 32 64 128 256"
FLANN_ITERATIONS=15

KGRAPH_COST="1 2 3 4 5 10 25 50 75 100 150 200 300 400 600 800 1000 1200 1400 1600 1800 2000 2500 5000 7500 10000 15000 20000 25000"
KGRAPH_K="10 25 50 100"

ANN_EPS="1.5 1.75 2 2.5 2.5 3 3.5 4 4.5 5 6 7 8 9 10"

FALCONN_TABLES="10 25 50 100 200 400 600 800 1000 1200 1400 1600 1800 2000"
