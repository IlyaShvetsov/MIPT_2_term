#pragma once
#include "Graph.h"
#include <unordered_set>


class CHashGraph : public IGraph {
public:
	explicit CHashGraph(int _verticesCount);
	CHashGraph(const IGraph* copyGraph);

	virtual void AddEdge(int from, int to);
	virtual int VerticesCount() const { return verticesCount; }
	virtual void GetNextVertices(int vertex, vector<int>& vertices) const;
	virtual void GetPrevVertices(int vertex, vector<int>& vertices) const;

private:
	int verticesCount;
	vector<unordered_set<int>> in;
	vector<unordered_set<int>> out;
};