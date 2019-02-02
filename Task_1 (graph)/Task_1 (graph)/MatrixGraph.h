#pragma once
#include "Graph.h"


class CMatrixGraph : public IGraph {
public:
	explicit CMatrixGraph(int _verticesCount);
	CMatrixGraph(const IGraph* copyGraph);

	virtual void AddEdge(int from, int to);
	virtual int VerticesCount() const { return verticesCount; }
	virtual void GetNextVertices(int vertex, vector<int>& vertices) const;
	virtual void GetPrevVertices(int vertex, vector<int>& vertices) const;

private:
	int verticesCount;
	vector<vector<int>> edges;
};