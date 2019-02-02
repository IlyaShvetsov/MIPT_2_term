#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

int Dinitz(const CMatrixGraph& Graph, string s1, string s2, vector <int>& dist)
{
	int n = Graph.VerticesCount();
	int vert_1 = 0, vert_2 = n - 1;
	vector <vector <int> > capacity(n);
	vector <vector <int> > flows(n, vector <int>(n, 0));
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



int Create_index(vector <int>& index_1, vector <int>& index_2, const string& s1, const string& s2)
{
	int j = 0;
	for (int i = 0; i < s1.length(); ++i)
		if (s1[i] == '?')
		{
			j++;
			index_1[i] = j;
		}
	for (int i = 0; i < s2.length(); ++i)
		if (s2[i] == '?')
		{
			j++;
			index_2[i] = j;
		}
	return j;
}

void Create_graph(CMatrixGraph& graph, vector <int>& index_1, vector <int>& index_2, const string& s1, const string& s2)
{
	int n = graph.VerticesCount();
	for (int j = 0; j <= s1.length() - s2.length(); ++j)
		for (int i = 0; i < s2.length(); ++i)
		{
			if ((s1[i + j] == '0' && s2[i] == '1') || (s1[i + j] == '1' && s2[i] == '0'))
				graph.AddEdge(0, n - 1, 1);
			if (s1[i + j] == '0' && s2[i] == '?')
				graph.AddEdge(0, index_2[i], 1);
			if (s1[i + j] == '?' && s2[i] == '0')
				graph.AddEdge(0, index_1[i + j], 1);
			if (s1[i + j] == '1' && s2[i] == '?')
				graph.AddEdge(index_2[i], n - 1, 1);
			if (s1[i + j] == '?' && s2[i] == '1')
				graph.AddEdge(index_1[i + j], n - 1, 1);
			if (s1[i + j] == '?' && s2[i] == '?')
			{
				graph.AddEdge(index_1[i + j], index_2[i], 1);
				graph.AddEdge(index_2[i], index_1[i + j], 1);
			}
		}
}

void Find_strings(int n, string s1, string s2, vector <int>& dist, vector <char>& str1, vector <char>& str2)
{
	vector <int> xxx(n - 1, 0);
	for (int i = 1; i < n - 1; ++i)
		if (dist[i] == -1)
			xxx[i] = 1;

	int j = 1;
	for (int i = 0; i < s1.length(); ++i)
		if (s1[i] == '?')
		{
			str1[i] = (char)(xxx[j] + 48);
			j++;
		}
		else
			str1[i] = s1[i];
	for (int i = 0; i < s2.length(); ++i)
		if (s2[i] == '?')
		{
			str2[i] = (char)(xxx[j] + 48);
			j++;
		}
		else
			str2[i] = s2[i];
}

int Hamming(const string& s1, const string& s2, vector <char>& str1, vector <char>& str2)
{
	vector <int> index_1(s1.size()), index_2(s2.size());
	int j = Create_index(index_1, index_2, s1, s2);   // j - количество знаков вопроса
	int n = j + 2;									  // вершин в графе - j + 2
	CMatrixGraph graph(n);
	Create_graph(graph, index_1, index_2, s1, s2);
	vector <int> dist(n, -1);

	int maxflow = Dinitz(graph, s1, s2, dist);
	Find_strings(n, s1, s2, dist, str1, str2);

	return maxflow;
}



int main()
{
	string s1, s2;
	ifstream inp("input.txt");
	inp >> s1 >> s2;
	if (s1.length() < s2.length())
		swap(s1, s2);

	vector <char> str1(s1.length());
	vector <char> str2(s2.length());

	cout << Hamming(s1, s2, str1, str2) << endl;
	for (int i = 0; i < s1.length(); ++i)
		cout << str1[i];
	cout << endl;
	for (int i = 0; i < s2.length(); ++i)
		cout << str2[i];
	cout << endl;

	inp.close();
	return 0;
}