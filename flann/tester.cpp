#include <cstdio>
#include <stdint.h>
#include <omp.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <flann/flann.hpp>

#include "../common.h"

using namespace flann;

int main(int argc, char **argv) {
    char *path = argv[1];
    int dim = atoi(argv[2]);
    int n_trees = atoi(argv[3]);
    int n, n_test;

    float *train_data = get_data((std::string(path) + "/train.bin").c_str(), dim, &n);
    float *test_data = get_data((std::string(path) + "/test.bin").c_str(), dim, &n_test);

    Matrix<float> dataset(train_data, n, dim);

    Index<L2<float> > index(dataset, flann::KDTreeIndexParams(n_trees));
    index.buildIndex();

    omp_set_num_threads(1);
    for (int ind = 0; Ks[ind] != -1; ++ind) {
        int k = Ks[ind];

        for (int arg = 4; arg < argc; ++arg) {
            std::vector<double> times;
            std::vector<std::set<int>> idx;

            Matrix<int> indices(new int[k], 1, k);
            Matrix<float> dists(new float[k], 1, k);

            int checks = atoi(argv[arg]);
            for (int i = 0; i < n_test; ++i) {
                Matrix<float> query(test_data + i * dim, 1, dim);
                double start = omp_get_wtime();
                index.knnSearch(query, indices, dists, k, flann::SearchParams(checks));
                double end = omp_get_wtime();
                times.push_back(end - start);
                set<int> res;
                int *result = indices[0];
                for (int i = 0; i < k; ++i) res.insert(result[i]);
                idx.push_back(res);
            }

            std::cout << k << " " << n_trees << " " << checks << " ";
            results(k, times, idx, (std::string(path) + "/truth_" + std::to_string(k)).c_str());
        }
    }

    delete[] train_data;
    delete[] test_data;

    return 0;
}
