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
    char *train = argv[1];
    char *test = argv[2];
    int dim = atoi(argv[3]);
    int k = atoi(argv[4]);
    int n, n_test;

    float *train_data = get_data(train, dim, &n);
    float *test_data = get_data(test, dim, &n_test);

    // build dummy index
    const Map<MatrixXf> *X = new Map<MatrixXf>(train_data, dim, n);
    Mrpt index(X, 0, 0, 1.);

    VectorXi idx(n);
    std::iota(idx.data(), idx.data() + n, 0);

    omp_set_num_threads(1);
    for (int i = 0; i < n_test; ++i) {
        std::vector<int> result(k);
        double start = omp_get_wtime();
        index.exact_knn(Map<VectorXf>(&test_data[i * dim], dim), k, idx, n, &result[0]);
        double end = omp_get_wtime();
        printf("%g\n", end - start);
        for (int i = 0; i < k; ++i) printf("%d ", result[i]);
        printf("\n");
    }

    delete[] train_data;
    delete[] test_data;
    delete X;

    return 0;
}
