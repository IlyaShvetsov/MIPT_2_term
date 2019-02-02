#include "ArcGraph.h"


CArcGraph::CArcGraph(int _verticesCount) :
	verticesCount(_verticesCount)
{}

CArcGraph::CArcGraph(const IGraph* copyGraph) :
	verticesCount(copyGraph->VerticesCount())
{
	vector<int> vertices;
	for (int i = 0; i < verticesCount; ++i)
	{
		copyGraph->GetPrevVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j)
			edges.push_back(pair<int, int>(vertices[j], i));
		copyGraph->GetNextVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j)
			edges.push_back(pair<int, int>(i, vertices[j]));
	}
}

void CArcGraph::AddEdge(int from, int to)
{
	edges.push_back(pair<int, int>(from, to));
}

void CArcGraph::GetNextVertices(int vertex, vector<int>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		if (edges[i].first == vertex)
			vertices.push_back(edges[i].second);
}

void CArcGraph::GetPrevVertices(int vertex, vector<int>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		if (edges[i].second == vertex)
			vertices.push_back(edges[i].first);
}