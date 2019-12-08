#include "CMatrixGraph.h"


class True_solution {
public:
    True_solution(const CMatrixGraph& graph);
    ~True_solution() {}

    float Solution();

private:
    int verticesCount;
    vector <vector <float> > edges;
    float ans;
};
