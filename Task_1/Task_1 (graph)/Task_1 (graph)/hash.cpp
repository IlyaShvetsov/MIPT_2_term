#include "hash.h"


CHashGraph::CHashGraph(int _verticesCount) :
	verticesCount(_verticesCount),
	in(verticesCount),
	out(verticesCount)
{}

CHashGraph::CHashGraph(const IGraph* copyGraph) :
	verticesCount(copyGraph->VerticesCount()),
	in(verticesCount),
	out(verticesCount)
{
	vector<int> vertices;
	for (int i = 0; i < verticesCount; ++i)
	{
		copyGraph->GetPrevVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j)
			in[i].insert(vertices[j]);
		copyGraph->GetNextVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j)
			out[i].insert(vertices[j]);
	}
}

void CHashGraph::AddEdge(int from, int to)
{
	in[to].insert(from);
	out[from].insert(to);
}

void CHashGraph::GetNextVertices(int vertex, vector<int>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		if (out[i].find(i) == out[i].end())
			vertices.push_back(i);
}

void CHashGraph::GetPrevVertices(int vertex, vector<int>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		if (in[i].find(i) == in[i].end())
			vertices.push_back(i);
}