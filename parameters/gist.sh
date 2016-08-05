#!/usr/bin/env bash

DATASET_NAME=gist
DIM=960

MRPT_N_TREES="1 5 10 25 50 75 100 125 150 200 250 300 350 400 500 600"
MRPT_DEPTH="8 9 10 11 12 13 14 15 16"
MRPT_SPARSITY=0.032

MRPT_VOTING_N_TREES="10 25 50 75 100 125 150 200 250 300 350 400 500 600 700 800 900 1000"
MRPT_VOTES="1 2 3 4 5 8 10 12 15 20 25 30 40 50 60 70 80 90 100"

FLANN_N_TREES="1 2 4 8 16 32"
FLANN_CHECKS="0 1000 2000 3000 4000 5000 6000 8000 10000 12000 14000 16000 18000 20000 22500 25000 30000 35000 40000 45000 50000 60000 75000 100000 125000 150000 200000"

FLANN_BRANCHING="8 16 32 64 128 256"
FLANN_ITERATIONS=15

KGRAPH_COST="1 2 3 4 5 10 25 50 75 100 150 200 400 600 800 1000 2000 3000 4000 5000 6000 8000 10000 12000 15000"
KGRAPH_K="10 25 50 100"

ANN_EPS="1.5 2 2.5 3 4 5 6 8 10 12 15"

FALCONN_TABLES="1 2 3 4 5 6 8 10 12 15 20 25 30 40 50"
FALCONN_HASH_BITS="16 17 18 19 20 21 22"
