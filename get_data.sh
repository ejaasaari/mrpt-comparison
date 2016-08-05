#!/usr/bin/env bash

REMOVE_DOWNLOADED=true # remove downloaded datasets after they've been converted
TEST_N=100 # number of test queries

if [ ! -f "data/mnist/data.bin" ]; then
    mkdir -p data/mnist
    echo "Downloading MNIST..."
    wget "http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz" -O train-images-idx3-ubyte.gz
    echo "Extracting MNIST..."
    gunzip train-images-idx3-ubyte.gz
    echo "Converting MNIST..."
    python2 tools/binary_converter.py train-images-idx3-ubyte data/mnist/data.bin
    python2 tools/binary_converter.py --sample data/mnist/data.bin data/mnist/train.bin data/mnist/test.bin $TEST_N 784
    if [ "$REMOVE_DOWNLOADED" = true ]; then
        rm train-images-idx3-ubyte
    fi
fi

if [ ! -f "data/stl10/data.bin" ]; then
    mkdir -p data/stl10
    echo "Downloading STL-10..."
    wget "http://cs.stanford.edu/~acoates/stl10/stl10_binary.tar.gz" -O stl10_binary.tar.gz
    echo "Extracting STL-10..."
    tar xzf stl10_binary.tar.gz
    echo "Converting STL-10..."
    python2 tools/binary_converter.py stl10_binary/unlabeled_X.bin data/stl10/data.bin
    python2 tools/binary_converter.py --sample data/stl10/data.bin data/stl10/train.bin data/stl10/test.bin $TEST_N 9216
    rm -r stl10_binary
    if [ "$REMOVE_DOWNLOADED" = true ]; then
        rm stl10_binary.tar.gz
    fi
fi

if [ ! -f "data/gist/data.bin" ]; then
    mkdir -p data/gist
    echo "Downloading GIST..."
    wget "ftp://ftp.irisa.fr/local/texmex/corpus/gist.tar.gz" -O gist.tar.gz
    echo "Extracting GIST..."
    tar xzf gist.tar.gz
    echo "Converting GIST..."
    python2 tools/binary_converter.py gist/gist_base.fvecs data/gist/data.bin
    python2 tools/binary_converter.py --sample data/gist/data.bin data/gist/train.bin data/gist/test.bin $TEST_N 960
    rm -r gist
    if [ "$REMOVE_DOWNLOADED" = true ]; then
        rm gist.tar.gz
    fi
fi

if [ ! -f "data/trevi/data.bin" ]; then
    mkdir -p data/trevi
    echo "Downloading Trevi..."
    wget "http://phototour.cs.washington.edu/patches/trevi.zip" -O trevi.zip
    echo "Extracting Trevi..."
    mkdir patches
    unzip -q trevi.zip -d patches
    echo "Converting Trevi..."
    python2 tools/binary_converter.py patches/ data/trevi/data.bin
    python2 tools/binary_converter.py --sample data/trevi/data.bin data/trevi/train.bin data/trevi/test.bin $TEST_N 4096
    rm -r patches
    if [ "$REMOVE_DOWNLOADED" = true ]; then
        rm trevi.zip
    fi
fi

if [ ! -f "data/random/data.bin" ]; then
    mkdir -p data/random
    echo "Generating random data..."
    python2 tools/binary_converter.py 50000 data/random/data.bin
    python2 tools/binary_converter.py --sample data/random/data.bin data/random/train.bin data/random/test.bin $TEST_N 4096
fi

if [ ! -f "data/sift/data.bin" ]; then
    mkdir -p data/sift
    echo "Downloading SIFT..."
    wget "ftp://ftp.irisa.fr/local/texmex/corpus/bigann_learn.bvecs.gz" -O bigann_learn.bvecs.gz
    echo "Extracting SIFT..."
    gunzip bigann_learn.bvecs.gz
    echo "Converting SIFT..."
    python2 tools/binary_converter.py bigann_learn.bvecs data/sift/data.bin 2500000
    python2 tools/binary_converter.py --sample data/sift/data.bin data/sift/train.bin data/sift/test.bin $TEST_N 128
    if [ "$REMOVE_DOWNLOADED" = true ]; then
        rm bigann_learn.bvecs
    fi
fi
