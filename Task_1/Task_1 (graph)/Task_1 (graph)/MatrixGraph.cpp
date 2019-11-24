#include "MatrixGraph.h"


CMatrixGraph::CMatrixGraph(int _verticesCount) :
	verticesCount(_verticesCount),
	edges(verticesCount)
{
	for (int i = 0; i < verticesCount; ++i)
		edges[i].resize(verticesCount);
}

CMatrixGraph::CMatrixGraph(const IGraph* copyGraph) :
	verticesCount(copyGraph->VerticesCount()),
	edges(verticesCount)
{
	for (int i = 0; i < verticesCount; ++i)
		edges[i].resize(verticesCount);
	vector<int> vertices;
	for (int i = 0; i < verticesCount; ++i)
	{
		copyGraph->GetPrevVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j)
			edges[i][vertices[j]] = 1;
	}
}

void CMatrixGraph::AddEdge(int from, int to)
{
	edges[from][to] = true;
}

void CMatrixGraph::GetNextVertices(int vertex, vector<int>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		if (edges[vertex][i] == 1)
			vertices.push_back(i);
}

void CMatrixGraph::GetPrevVertices(int vertex, vector<int>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		if (edges[i][vertex] == 1)
			vertices.push_back(i);
}