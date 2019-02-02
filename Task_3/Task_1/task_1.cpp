//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <set>
//using namespace std;
//
//
//class CListGraph {
//public:
//	explicit CListGraph(int _verticesCount);
//	~CListGraph() {}
//
//	void AddEdge(int from, int to, int weight);
//	int VerticesCount() const { return verticesCount; }
//	void GetNextVertices(int vertex, vector <pair <int, int> >& vertices) const;
//
//private:
//	int verticesCount;
//	vector <vector <pair <int, int> > > out;
//};
//
//CListGraph::CListGraph(int _verticesCount) :
//	verticesCount(_verticesCount),
//	out(verticesCount)
//{}
//
//void CListGraph::AddEdge(int from, int to, int weight)
//{
//	out[from].push_back(pair <int, int>(weight, to));
//	out[to].push_back(pair <int, int>(weight, from));
//}
//
//void CListGraph::GetNextVertices(int vertex, vector <pair <int, int> >& vertices) const
//{
//	for (int i = 0; i < out[vertex].size(); ++i)
//		vertices.push_back(out[vertex][i]);
//}
//
//
//
//int Prim(const CListGraph& Graph)
//{
//	set <pair <int, int> > q;
//	vector <bool> isChecked(Graph.VerticesCount(), false);
//	int ok = 1, sum = 0;
//	isChecked[0] = true;
//
//	vector <pair <int, int> > vertices;
//	Graph.GetNextVertices(0, vertices);
//	for (int j = 0; j < vertices.size(); ++j)
//		q.insert(make_pair(vertices[j].first, vertices[j].second));
//
//	pair <int, int> edge;
//	while (ok != Graph.VerticesCount())
//	{
//		edge = *q.begin();
//		q.erase(q.begin());
//		if (!isChecked[edge.second])
//		{
//			isChecked[edge.second] = true;
//			vector <pair <int, int> > vertices;
//			Graph.GetNextVertices(edge.second, vertices);
//
//			for (int j = 0; j < vertices.size(); ++j)
//				q.insert(make_pair(vertices[j].first, vertices[j].second));
//
//			sum += edge.first;
//			ok++;
//		}
//	}
//	return sum;
//}
//
//
//
//int main()
//{
//	int n, m;
//	ifstream inp("kruskal.in");
//	ofstream out("kruskal.out");
//	inp >> n >> m;
//	CListGraph graph(n);
//	int from, to, weight;
//	for (int i = 0; i < m; ++i)
//	{
//		inp >> from >> to >> weight;
//		graph.AddEdge(from- 1, to-1, weight);
//	}
//
//	out << Prim(graph) << endl;
//
//	out.close();
//	inp.close();
//	return 0;
//}


#include <iostream>
#include <fstream>
#include <vector>
#include <set>
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
	edges(verticesCount, vector <int>(verticesCount, INT_MAX))
{}

void CMatrixGraph::AddEdge(int from, int to, int len)
{
	edges[from][to] = len;
}

void CMatrixGraph::GetNextVertices(int vertex, vector<int>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		vertices.push_back(edges[vertex][i]);
}



int Prim(const CMatrixGraph& Graph)
{
	set <pair <int, int> > q;
	vector <bool> isChecked(Graph.VerticesCount(), false);
	int ok = 1, sum = 0;
	isChecked[0] = true;

	vector <int> vertices;
	Graph.GetNextVertices(0, vertices);
	for (int i = 0; i < vertices.size(); ++i)
		q.insert(make_pair(vertices[i], i));

	pair <int, int> edge;
	while (ok != Graph.VerticesCount())
	{
		edge = *q.begin();
		q.erase(q.begin());
		if (!isChecked[edge.second])
		{
			isChecked[edge.second] = true;
			vector <int> vertices;
			Graph.GetNextVertices(edge.second, vertices);

			for (int i = 0; i < vertices.size(); ++i)
				q.insert(make_pair(vertices[i], i));

			sum += edge.first;
			ok++;
		}
	}
	return sum;
}



int main()
{
	int n, m;
	ifstream inp("kruskal.in");
	ofstream out("kruskal.out");
	inp >> n >> m;
	CMatrixGraph graph(n);
	int from, to, weight;
	for (int i = 0; i < m; ++i)
	{
		inp >> from >> to >> weight;
		graph.AddEdge(from - 1, to - 1, weight);
	}

	out << Prim(graph) << endl;

	out.close();
	inp.close();
	return 0;
}