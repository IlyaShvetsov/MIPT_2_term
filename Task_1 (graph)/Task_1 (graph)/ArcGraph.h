#pragma once
#include "Graph.h"


class CArcGraph : public IGraph {
public:
	explicit CArcGraph(int _verticesCount);
	CArcGraph(const IGraph* copyGraph);

	virtual void AddEdge(int from, int to);
	virtual int VerticesCount() const { return verticesCount; }
	virtual void GetNextVertices(int vertex, vector<int>& vertices) const;
	virtual void GetPrevVertices(int vertex, vector<int>& vertices) const;

private:
	int verticesCount;
	vector<pair<int, int>> edges;
};