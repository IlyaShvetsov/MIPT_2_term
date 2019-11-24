#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"


int main()
{
	CArcGraph graph(2);
	graph.AddEdge(3, 1);
	graph.AddEdge(1, 1);

	vector<int> in2;
	graph.GetPrevVertices(1, in2);

	for (int i = 0; i < in2.size(); ++i)
		cout << in2[i];


	return 0;
}
