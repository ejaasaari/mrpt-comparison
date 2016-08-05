#include <vector>
#include <cstdio>
#include <stdint.h>
#include <omp.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Mrpt.h"
#include <Eigen/Core>

#include "../common.h"

using namespace Eigen;

int main(int argc, char **argv) {
    char *path = argv[1];
    int dim = atoi(argv[2]);
    int n_trees = atoi(argv[3]);
    int depth = atoi(argv[4]);
    float sparsity = atof(argv[5]);
    int n, n_test;

    float *train_data = get_data((std::string(path) + "/train.bin").c_str(), dim, &n);
    float *test_data = get_data((std::string(path) + "/test.bin").c_str(), dim, &n_test);

    const Map<MatrixXf> *X = new Map<MatrixXf>(train_data, dim, n);
    Mrpt index(X, n_trees, depth, sparsity);
    index.grow();

    omp_set_num_threads(1);
    for (int ind = 0; Ks[ind] != -1; ++ind) {
        int k = Ks[ind];

        for (int arg = 6; arg < argc; ++arg) {
            int votes = atoi(argv[arg]);
            if (votes > n_trees) continue;

            std::vector<double> times;
            std::vector<std::set<int>> idx;

            for (int i = 0; i < n_test; ++i) {
                std::vector<int> result(k);
                double start = omp_get_wtime();
                int nn = index.query(Map<VectorXf>(&test_data[i * dim], dim), k, votes, 0, &result[0]);
                double end = omp_get_wtime();
                times.push_back(end - start);
                idx.push_back(std::set<int>(result.begin(), result.end()));
            }

            std::cout << k << " " << n_trees << " " << depth << " " << sparsity << " " << votes << " ";
            results(k, times, idx, (std::string(path) + "/truth_" + std::to_string(k)).c_str());
        }
    }

    delete[] train_data;
    delete[] test_data;
    delete X;

    return 0;
}
