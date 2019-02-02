#pragma once
#include <vector>
using namespace std;


class CMatrixGraph {
public:
	explicit CMatrixGraph(int _verticesCount);
	~CMatrixGraph() {}

	void AddEdge(int from, int to, float len);
	int VerticesCount() const { return verticesCount; }
	void GetNextVertices(int vertex, vector <float>& vertices) const;

private:
	int verticesCount;
	vector <vector <float> > edges;
};