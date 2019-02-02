#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;


class CMatrixGraph {
public:
	explicit CMatrixGraph(int _verticesCount);
	~CMatrixGraph() {}

	void AddEdge(int from, int to, int len);
	int VerticesCount() const { return verticesCount; }
	void GetNextVertices(int vertex, vector <int>& vertices) const;

private:
	int verticesCount;
	vector <vector <int> > edges;
};

CMatrixGraph::CMatrixGraph(int _verticesCount) :
	verticesCount(_verticesCount),
	edges(verticesCount, vector <int>(verticesCount, 0))
{}

void CMatrixGraph::AddEdge(int from, int to, int len)
{
	edges[from][to] += len;
}

void CMatrixGraph::GetNextVertices(int vertex, vector<int>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		vertices.push_back(edges[vertex][i]);
}



bool bfs(const vector <vector <int> >& capacity, const vector <vector <int> >& flows, vector <int>& dist)
{
	int n = capacity.size();
	int vert_1 = 0, vert_2 = n - 1;
	dist.assign(n, -1);
	dist[vert_1] = 0;
	queue <int> q;
	q.push(vert_1);
	int vert;
	while (!q.empty())
	{
		vert = q.front();
		q.pop();
		for (int i = 0; i < n; ++i)
			if (capacity[vert][i] > flows[vert][i] && dist[i] == -1)
			{
				dist[i] = dist[vert] + 1;
				q.push(i);
			}
	}
	return dist[vert_2] != -1;
}

int dfs(const vector <vector <int> >& capacity, vector <vector <int> >& flows, 
	vector <int>& p, vector <int>& dist, int vert_x, int minC)
{
	int n = capacity.size();
	int vert_1 = 0, vert_2 = n - 1;
	if (vert_x == vert_2 || minC == 0)
		return minC;
	
	for (int i = p[vert_x]; i < n; ++i)
	{
		if (dist[i] == dist[vert_x] + 1)
		{
			int delta = dfs(capacity, flows, p, dist, i, min(minC, capacity[vert_x][i] - flows[vert_x][i]));
			if (delta != 0)
			{
				flows[vert_x][i] += delta;
				flows[i][vert_x] -= delta;
				return delta;
			}
		}
		p[vert_x]++;
	}
	return 0;
}

int Dinitz(const CMatrixGraph& Graph)
{
	int n = Graph.VerticesCount();
	int vert_1 = 0, vert_2 = n - 1;
	vector <vector <int> > capacity(n);
	vector <vector <int> > flows(n, vector <int>(n, 0));
	vector <int> dist(n, -1);
	for (int i = 0; i < n; ++i)
		Graph.GetNextVertices(i, capacity[i]);

	int maxflow = 0;
	while (bfs(capacity, flows, dist))
	{
		vector <int> p(n, 0);
		int flow = dfs(capacity, flows, p, dist, vert_1, INT_MAX);
		while (flow != 0)
		{
			maxflow += flow;
			flow = dfs(capacity, flows, p, dist, vert_1, INT_MAX);
		}
	}
	return maxflow;
}



int main()
{
	int n, m;
	ifstream inp("maxflow.in");
	ofstream out("maxflow.out");
	inp >> n >> m;
	CMatrixGraph graph(n);
	int from, to, weight;
	for (int i = 0; i < m; ++i)
	{
		inp >> from >> to >> weight;
		graph.AddEdge(from - 1, to - 1, weight);
	}

	out << Dinitz(graph) << endl;

	out.close();
	inp.close();
	return 0;
}