#include <algorithm>
#include <cstdio>
#include <iostream>
#include <omp.h>
#include <set>
#include <stdint.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include <falconn/lsh_nn_table.h>

#include "../common.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;

using falconn::construct_table;
using falconn::DenseVector;
using falconn::DistanceFunction;
using falconn::LSHConstructionParameters;
using falconn::get_default_parameters;
using falconn::compute_number_of_hash_functions;

typedef DenseVector<float> Point;

int main(int argc, char **argv) {
    char *path = argv[1];
    int dim = atoi(argv[2]);
    int tables = atoi(argv[3]);
    int hash_bits = atoi(argv[4]);
    int n, n_test;

    float *train_data = get_data((std::string(path) + "/train.bin").c_str(), dim, &n);
    float *test_data = get_data((std::string(path) + "/test.bin").c_str(), dim, &n_test);

    vector<Point> dataset, queries;

    for (int i = 0; i < n; ++i) {
        Point p;
        p.resize(dim);
        for (int j = 0; j < dim; ++j)
            p[j] = train_data[i * dim + j];
        dataset.push_back(p);
    }

    for (int i = 0; i < n_test; ++i) {
        Point p;
        p.resize(dim);
        for (int j = 0; j < dim; ++j)
            p[j] = test_data[i * dim + j];
        queries.push_back(p);
    }

    LSHConstructionParameters params
        = get_default_parameters<Point>(dataset.size(),
                                        dataset[0].size(),
                                        DistanceFunction::EuclideanSquared,
                                        true);
    params.l = tables;
    compute_number_of_hash_functions<Point>(hash_bits, &params);

    auto table = construct_table<Point>(dataset, params);
    table->set_num_probes(tables);

    omp_set_num_threads(1);
    for (int ind = 0; Ks[ind] != -1; ++ind) {
        int k = Ks[ind];

        std::vector<double> times;
        std::vector<std::set<int>> idx;

        for (int i = 0; i < n_test; ++i) {
            vector<int32_t> result(k);
            double start = omp_get_wtime();
            table->find_k_nearest_neighbors(queries[i], k, &result);
            double end = omp_get_wtime();
            times.push_back(end - start);
            set<int> res;
            for (int i = 0; i < k; ++i) res.insert(result[i]);
            idx.push_back(res);
        }

        std::cout << k << " " << tables << " " << hash_bits;
        results(k, times, idx, (std::string(path) + "/truth_" + std::to_string(k)).c_str());
    }

    delete[] train_data;
    delete[] test_data;

    return 0;
}
