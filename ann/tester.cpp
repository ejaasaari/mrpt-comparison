#include <set>
#include <vector>
#include <cstdio>
#include <stdint.h>
#include <omp.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <ANN/ANN.h>

#include "../common.h"

int main(int argc, char **argv) {
    char *path = argv[1];
    int dim = atoi(argv[2]);
    int n, n_test;

    float *train_data = get_data((std::string(path) + "/train.bin").c_str(), dim, &n);
    float *test_data = get_data((std::string(path) + "/test.bin").c_str(), dim, &n_test);

    ANNpointArray X_ann = annAllocPts(n, dim);
    ANNpointArray query = annAllocPts(n_test, dim);
    std::vector<ANNidxArray> indices(n_test);
    std::vector<ANNdistArray> distances(n_test);

    for (int i = 0; i < n; ++i) {
        X_ann[i] = train_data + i * dim;
    }

    // build the index
    ANNkd_tree tree(X_ann, n, dim, 1);

    for (int ind = 0; Ks[ind] != -1; ++ind) {
        int k = Ks[ind];

        for (int i = 0; i < n_test; ++i) {
            indices[i] = new ANNidx[k];
            distances[i] = new ANNdist[k];
        }

        for (int arg = 3; arg < argc; ++arg) {
            std::vector<double> times;
            std::vector<std::set<int>> idx;

            float eps = atof(argv[arg]);
            for (int i = 0; i < n_test; ++i) {
                query[i] = test_data + i * dim;
                double start = omp_get_wtime();
                tree.annkSearch(query[i], k, indices[i], distances[i], eps);
                double end = omp_get_wtime();
                times.push_back(end - start);
                std::set<int> res;
                for (int j = 0; j < k; ++j) res.insert(indices[i][j]);
                idx.push_back(res);
            }

            std::cout << k << " " << eps << " ";
            results(k, times, idx, (std::string(path) + "/truth_" + std::to_string(k)).c_str());
        }
    }

    delete[] train_data;
    delete[] test_data;

    return 0;
}
