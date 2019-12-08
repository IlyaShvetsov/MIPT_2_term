#include "Generator.h"


CMatrixGraph Generator::Generate(int n) {

    CMatrixGraph Graph(n);
    vector <float> x, y;

    float r, f;
    for (int i = 0; i < n; ++i) {
        r = 1.0f / (float)rand();
        f = 1.0f / (float)rand();
        x.push_back(cos(6.28 * f) * sqrt(-2 * log(r)));
        y.push_back(sin(6.28 * f) * sqrt(-2 * log(r)));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Graph.AddEdge(i, j, sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])));
        }
    }

    return Graph;
}
