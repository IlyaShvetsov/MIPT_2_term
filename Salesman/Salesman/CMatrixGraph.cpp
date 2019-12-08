#include "CMatrixGraph.h"


CMatrixGraph::CMatrixGraph(int _verticesCount) :
        verticesCount(_verticesCount),
        edges(verticesCount, vector <float>(verticesCount))
{}

void CMatrixGraph::AddEdge(int from, int to, float len) {
    edges[from][to] = len;
    edges[to][from] = len;
}

void CMatrixGraph::GetNextVertices(int vertex, vector<float>& vertices) const {
    for (int i = 0; i < verticesCount; ++i)
        vertices.push_back(edges[vertex][i]);
}
