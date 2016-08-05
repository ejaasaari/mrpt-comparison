#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <utility>

using namespace std;

int Ks[] = {1, 10, 100, -1};

float *get_data(const char *file, int dim, int *n) {
    struct stat sb;
    stat(file, &sb);
    int N = sb.st_size / (sizeof(float) * dim);
    *n = N;

    float *data = new float[N * dim];

    FILE *fd;
    fd = fopen(file, "rb");
    fread(data, sizeof(float), N * dim, fd);
    fclose(fd);

    return data;
}

void results(int k, const vector<double> &times, const vector<set<int>> &idx, const char *truth) {
    double time;
    vector<set<int>> correct;

    ifstream fs(truth);
    for (int j = 0; fs >> time; ++j) {
        set<int> res;
        for (int i = 0; i < k; ++i) {
            int r;
            fs >> r;
            res.insert(r);
        }
        correct.push_back(res);
    }

    vector<pair<double, double>> results;

    double accuracy, total_time = 0, total_accuracy = 0;
    for (unsigned i = 0; i < times.size(); ++i) {
        set<int> intersect;
        set_intersection(correct[i].begin(), correct[i].end(), idx[i].begin(), idx[i].end(),
                         inserter(intersect, intersect.begin()));
        accuracy = intersect.size() / static_cast<double>(k);
        total_time += times[i];
        total_accuracy += accuracy;
        results.push_back(make_pair(times[i], accuracy));
    }

    double mean_accuracy = total_accuracy / results.size(), variance = 0;
    for (auto res : results)
        variance += (res.second - mean_accuracy) * (res.second - mean_accuracy);
    variance /= (results.size() - 1);

    cout << setprecision(5);
    cout << mean_accuracy << " " << variance << " " << total_time << endl;
}
