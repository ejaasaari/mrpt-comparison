#include <vector>
#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <omp.h>

#include "kgraph.h"
#include "kgraph-data.h"

#include "../common.h"

using namespace kgraph;

int main(int argc, char **argv) {
    char *path = argv[1];
    int dim = atoi(argv[2]);
    int K = atoi(argv[3]);
    int n, n_test;

    kgraph::verbosity = 0;

    Matrix<float> data;
    data.load(std::string(path) + "/train.bin", dim);
    Matrix<float> queries;
    queries.load(std::string(path) + "/test.bin", dim);
    n_test = queries.size();

    MatrixOracle<float, metric::l2sqr> oracle(data);
    KGraph *index = KGraph::create();
    KGraph::IndexParams params;
    params.K = K;
    params.L = K + 50;
    index->build(oracle, params, NULL);

    omp_set_num_threads(1);
    for (int ind = 0; Ks[ind] != -1; ++ind) {
        int k = Ks[ind];

        for (int arg = 4; arg < argc; ++arg) {
            int P = atoi(argv[arg]);
            KGraph::SearchParams search_params;
            search_params.K = k;
            search_params.P = P;

            std::vector<double> times;
            std::vector<std::set<int>> idx;

            for (int i = 0; i < n_test; ++i) {
                std::vector<unsigned> result(k);
                double start = omp_get_wtime();
                index->search(oracle.query(queries[i]), search_params, &result[0], NULL);
                double end = omp_get_wtime();
                times.push_back(end - start);
                std::set<int> res;
                for (int j = 0; j < k; ++j) res.insert(result[j]);
                idx.push_back(res);
            }

            std::cout << k << " " << K << " " << P << " " ;
            results(k, times, idx, (std::string(path) + "/truth_" + std::to_string(k)).c_str());
        }
    }

    return 0;
}
