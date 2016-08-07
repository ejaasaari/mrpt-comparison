# MRPT performance comparison

## Introduction

MRPT (Multiple Random Projection Trees) is an algorithm for approximate nearest neighbor search in high dimensions. The method is based on combining multiple sparse random projection trees using a novel voting scheme where the final search is focused to points occurring in candidate sets retrieved by multiple trees. MRPT is a result of research conducted at the Helsinki Institute for Information Technology (HIIT).

This project contains a performance comparison between MRPT and other state-of-the-art libraries for approximate nearest neighbor search. We focus mainly on high-dimensional real-world data sets. The performance of the algorithms is measured in terms of query time and recall, that is, the fraction of true nearest neighbors returned.

## Included libraries and data sets

The included libraries are:
- MRPT
- [ANN](https://www.cs.umd.edu/~mount/ANN/)
- [FLANN](http://www.cs.ubc.ca/research/flann/)
- [FALCONN](https://falconn-lib.org/)
- [KGraph](http://kgraph.org)

The included data sets are:

| data set | n       | d    | type of data               |
| -------- | ------- | ---- | -------------------------- |
| [MNIST](http://yann.lecun.com/exdb/mnist/)    | 60000   | 784  | images of hand-written digits |
| News     | 262144  | 1000 | web pages converted into TF-IDF representation |
| [GIST](http://corpus-texmex.irisa.fr/)     | 1000000 | 960  | global color GIST descriptors |
| [SIFT](http://corpus-texmex.irisa.fr/)     | 2500000 | 128  | local SIFT descriptors |
| [Trevi](http://phototour.cs.washington.edu/patches/default.htm)    | 101120  | 4096 | image patches |
| [STL-10](https://cs.stanford.edu/~acoates/stl10/)   | 100000  | 9216 | images of different classes of objects |
| Random   | 50000   | 4096 | random samples from the 4096-dimensional unit sphere |

For each data set, we use a disjoint random sample of 100 points as the test queries.

## Parameters

For the most important tuning parameters (as stated by the authors), we used grid search on the appropriate ranges to
find the optimal parameter combinations in experiment, or the default values whenever provided by the authors. **The exact parameters for each data set can be found in the [parameters](https://github.com/ejaasaari/mrpt-comparison/tree/master/parameters) folder**.

The performance of MRPT is controlled by the number of trees, the depth of the trees and the vote limit. For ANN, we
vary the error bound, and for FLANN, we control the accuracy primarily by tuning the maximum number of leafs
to search, but also vary the number of trees for k-d trees and the branching factor for hierarchical k-means trees. KGraph is
primarily controlled by the search cost parameter, but we also build the graph with varying number of nearest neighbors for
each node. For FALCONN, we search for the optimal number of hash tables and hash functions.

## Results

(Click on the images to enlarge)

| k = 1 | k = 10 | k = 100 |
| ----- | ------ | ------- |
| <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/results/1_small.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/results/10_small.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/results/100_small.png" width=256> |

| MNIST, K=1 | MNIST, K=10 | MNIST, K=100 |
| --- | --- | --- |
<img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/mnist_1.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/mnist_10.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/mnist_100.png" width=256> |

| News, K=1 | News, K=10 | News, K=100 |
| --- | --- | --- |
<img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/news_1.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/news_10.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/news_100.png" width=256> |

| GIST, K=1 | GIST, K=10 | GIST, K=100 |
| --- | --- | --- |
<img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_1.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_10.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_100.png" width=256> |

| SIFT, K=1 | SIFT, K=10 | SIFT, K=100 |
| --- | --- | --- |
<img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_1.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_10.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_100.png" width=256> |

| Trevi, K=1 | Trevi, K=10 | Trevi, K=100 |
| --- | --- | --- |
<img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_1.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_10.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_100.png" width=256> |

| STL-10, K=1 | STL-10, K=10 | STL-10, K=100 |
| --- | --- | --- |
<img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_1.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_10.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/gist_100.png" width=256> |

| Random, K=1 | Random, K=10 | Random, K=100 |
| --- | --- | --- |
<img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/random_1.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/random_10.png" width=256> | <img src="https://raw.githubusercontent.com/ejaasaari/mrpt-comparison/master/images/random_100.png" width=256> |

## Running the comparison

To compile the algorithms and download the data sets, run:
```
./get_algos.sh
./get_data.sh
```

The comparisons can then be run individually for data sets, e.g.:
```
./comparison.sh mnist
```

## Questions

ejaasaar at cs.helsinki.fi
