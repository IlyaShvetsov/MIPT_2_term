#include "Prim_solution.h"
#include <set>


Prim_solution::Prim_solution(const CMatrixGraph& graph) :
        verticesCount(graph.VerticesCount()),
        edges(verticesCount) {
    for (int i = 0; i < verticesCount; ++i) {
        graph.GetNextVertices(i, edges[i]);
    }
}

void Prim_solution::prim(vector <int>& ans) const {
    set <pair <float, int> > q;
    vector <bool> isChecked(verticesCount, false);
    int ok = 1;
    isChecked[0] = true;
    ans.push_back(0);

    for (int i = 0; i < verticesCount; ++i) {
        q.insert(make_pair(edges[0][i], i));
    }

    pair <float, int> edge;
    while (ok != verticesCount) {
        edge = *q.begin();
        q.erase(q.begin());
        if (!isChecked[edge.second]) {
            isChecked[edge.second] = true;

            for (int i = 0; i < verticesCount; ++i) {
                q.insert(make_pair(edges[edge.second][i], i));
            }

            ans.push_back(edge.second);
            ok++;
        }
    }
}

float Prim_solution::Solution() const {
    float sum = 0;
    vector <int> ans;
    prim(ans);

    for (int i = 1; i < verticesCount; ++i) {
        sum += edges[ans[i - 1]][ans[i]];
    }
    sum += edges[ans[verticesCount - 1]][ans[0]];

    return sum;
}
