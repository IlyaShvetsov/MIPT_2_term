#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits.h>
using namespace std;


struct Edge
{
	int from;
	int to;
	double cost;

	Edge(int _from, int _to, double _cost) :
		from(_from), to(_to), cost(_cost) {}
};

class CArcGraph {
public:
	explicit CArcGraph(int _verticesCount);
	~CArcGraph() {}

	void AddEdge(int from, int to, double cost);
	int VerticesCount() const { return verticesCount; }
	int EdgesCount() const { return edgesCount; }
	vector<Edge> GetEdges() const { return edges; }

private:
	int verticesCount;
	int edgesCount;
	vector<Edge> edges;
};

CArcGraph::CArcGraph(int _verticesCount) :
	verticesCount(_verticesCount),
	edgesCount(0)
{}

void CArcGraph::AddEdge(int from, int to, double cost)
{
	edges.push_back(Edge(from, to, cost));
	edgesCount++;
}

bool Ford_Bellman(const CArcGraph& Graph)
{
	vector<double> distances;
	vector<Edge> edges = Graph.GetEdges();
	distances.resize(Graph.VerticesCount());
	distances.assign(Graph.VerticesCount(), INT_MIN);
	distances[edges[0].from] = 1;
	for (int i = 0; i < Graph.VerticesCount(); ++i)
		for (int j = 0; j < Graph.EdgesCount(); ++j)
			if (distances[edges[j].from] > INT_MIN)
				distances[edges[j].to] = max(distances[edges[j].to], distances[edges[j].from] * edges[j].cost);

	bool x = false;
	for (int j = 0; j < Graph.EdgesCount(); ++j)
		if (distances[edges[j].from] > INT_MIN)
			if (distances[edges[j].to] < distances[edges[j].from] * edges[j].cost)
				x = true;

	return x;
}



int main()
{
	int n;
	double edge;
	ifstream inp("input.txt");
	inp >> n;
	CArcGraph graph(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i != j)
			{
				inp >> edge;
				if (edge != -1)
					graph.AddEdge(i, j, edge);
			}

	if (Ford_Bellman(graph))
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	inp.close();
	return 0;
}