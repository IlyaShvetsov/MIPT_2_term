#include "CMatrixGraph.h"


class Prim_solution {
public:
	Prim_solution(const CMatrixGraph& graph);
	~Prim_solution() {}

	float Solution() const;

private:
	void prim(vector <int>& ans) const;
	
	int verticesCount;
	vector <vector <float> > edges;
};