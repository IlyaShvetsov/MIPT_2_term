#include "ListGraph.h"


CListGraph::CListGraph(int _verticesCount) :
	verticesCount(_verticesCount),
	in(verticesCount),
	out(verticesCount)
{}

CListGraph::CListGraph(const IGraph* copyGraph) : 
	verticesCount(copyGraph->VerticesCount()), 
	in(verticesCount), 
	out(verticesCount) 
{
	for (int i = 0; i < verticesCount; ++i) 
	{
		copyGraph->GetPrevVertices(i, in[i]);
		copyGraph->GetNextVertices(i, out[i]);
	}
}

void CListGraph::AddEdge(int from, int to)
{
	in[to].push_back(from);
	out[from].push_back(to);
}

void CListGraph::GetNextVertices(int vertex, vector<int>& vertices) const
{
	vertices = out[vertex];
}

void CListGraph::GetPrevVertices(int vertex, vector<int>& vertices) const
{
	vertices = in[vertex];
}