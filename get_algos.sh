#!/usr/bin/env bash

if [ ! -f exact/tester ]; then
    pushd exact
    make
    popd
fi

if [ ! -f mrpt/tester ]; then
    pushd mrpt
    make
    popd
fi

if [ ! -d ann/lib ]; then
    wget "https://www.cs.umd.edu/~mount/ANN/Files/1.1.2/ann_1.1.2.zip"
    unzip -q "ann_1.1.2.zip"
    mv "ann_1.1.2/" "ann/lib"
    patch ann/lib/Make-config patches/ann1.patch
    patch ann/lib/Makefile patches/ann2.patch
    patch ann/lib/include/ANN/ANN.h patches/ann3.patch
    pushd ann/lib
    make linux-g++
    popd
    pushd ann
    make
    popd
    rm "ann_1.1.2.zip"
fi

if [ ! -d falconn/lib ]; then
    wget "https://github.com/FALCONN-LIB/FALCONN/archive/v1.2.zip" -O falconn.zip
    unzip -q falconn.zip
    mv "FALCONN-1.2/src/include" "falconn/lib"
    pushd falconn
    make
    popd
    rm -r "FALCONN-1.2"
    rm "falconn.zip"
fi

mkdir -p flann/build
if [ ! -d flann/lib ]; then
    mkdir -p flann/lib
    git clone "https://github.com/mariusmuja/flann.git" flann-build
    patch flann-build/CMakeLists.txt patches/flann1.patch
    mkdir flann-build/build
    pushd flann-build/build
    cmake -DCMAKE_INSTALL_PREFIX=../../flann/lib ..
    make
    make install
    popd
    rm -rf flann-build
    pushd flann
    make
    popd
fi

if [ ! -f flann-kmeans/tester ]; then
    pushd flann-kmeans
    make
    popd
fi

if [ ! -d kgraph/lib ]; then
    wget "http://www.kgraph.org/releases/kgraph-1.4-x86_64.tar.gz" -O "kgraph-1.4-x86_64.tar.gz"
    tar xzf "kgraph-1.4-x86_64.tar.gz"
    mv "kgraph-1.4-x86_64" "kgraph/lib"
    cp kgraph/lib/bin/libkgraph.so kgraph/lib
    pushd kgraph
    make
    popd
    rm "kgraph-1.4-x86_64.tar.gz"
fi
