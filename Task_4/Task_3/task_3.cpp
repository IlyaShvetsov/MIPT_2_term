#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class CListGraph {
public:
	explicit CListGraph(int _verticesCount);
	~CListGraph() {}

	void AddEdge(int from, int to);
	int VerticesCount() const { return verticesCount; }
	void GetNextVertices(int vertex, vector<int>& vertices) const;

private:
	int verticesCount;
	vector <vector <int> > out;
};

CListGraph::CListGraph(int _verticesCount) :
	verticesCount(_verticesCount),
	out(verticesCount)
{}

void CListGraph::AddEdge(int from, int to)
{
	out[from].push_back(to);
}

void CListGraph::GetNextVertices(int vertex, vector<int>& vertices) const
{
	vertices = out[vertex];
}



class Lca {
public:
	Lca(int n) : 
		up(n),
		timer(0),
		time_in(n), 
		time_out(n) {}

	void DFS(const CListGraph& graph, int vert, int p, int l);
	bool Ancestor(int a, int b);
	long long Solution(long long a1, long long a2, int x, int y, int z, int m, int l);
	int Solver(int a, int b, int l);

private:
	vector < vector<int> > up;
	vector<int> time_in;
	vector<int> time_out;
	int timer;
};



bool Lca::Ancestor(int a, int b)
{
	return time_in[a] <= time_in[b] && time_out[a] >= time_out[b];
}

void Lca::DFS(const CListGraph& graph, int vert, int p, int l)
{
	time_in[vert] = ++timer;

	up[vert].push_back(p);
	for (int i = 1; i <= l; ++i)
		up[vert].push_back(up[up[vert][i - 1]][i - 1]);

	vector <int> vertices;
	graph.GetNextVertices(vert, vertices);
	for (int i = 0; i < vertices.size(); ++i)
		DFS(graph, vertices[i], vert, l);

	time_out[vert] = ++timer;
}

int Lca::Solver(int a, int b, int l)
{
	if (Ancestor(a, b)) 
		return a;
	if (Ancestor(b, a)) 
		return b;
	for (int i = l; i >= 0; --i)
		if (!Ancestor(up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

long long Lca::Solution(long long a1, long long a2, int x, int y, int z, int m, int l)
{
	int n = time_in.size();
	long long a, b;
	long long answer = 0;
	int ans = 0;
	for (int i = 0; i < m; ++i)
	{
		a = (a1 + ans) % n;
		b = a2;

		ans = Solver(a, b, l);
		answer += ans;

		a1 = (x*a1 + y*a2 + z) % n;
		a2 = (x*a2 + y*a1 + z) % n;
	}

	return answer;
}



int main()
{
	long long n, m, a, b;
	ifstream in("input.txt");
	ofstream out("output.txt");
	in >> n >> m;
	CListGraph graph(n);
	for (int i = 1; i < n; ++i)
	{
		in >> a;
		graph.AddEdge(a, i);
	}
	int x, y, z;
	in >> a >> b;
	in >> x >> y >> z;

	vector <int> time_in(n), time_out(n);

	int l = 1;
	while ((1 << l) <= n)  ++l;

	Lca lca(n);
	int timer = 0;
	lca.DFS(graph, 0, 0, l);

	cout << lca.Solution(a, b, x, y, z, m, l);

	return 0;
}











//
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <stack>
//#include <algorithm>
//#include <limits.h>
//using namespace std;
//
//
//class CListGraph {
//public:
//	explicit CListGraph(int _verticesCount);
//	~CListGraph() {}
//
//	void AddEdge(int from, int to);
//	int VerticesCount() const { return verticesCount; }
//	void GetNextVertices(int vertex, vector<int>& vertices) const;
//
//private:
//	int verticesCount;
//	vector <vector <int> > out;
//};
//
//CListGraph::CListGraph(int _verticesCount) :
//	verticesCount(_verticesCount),
//	out(verticesCount)
//{}
//
//void CListGraph::AddEdge(int from, int to)
//{
//	out[from].push_back(to);
//}
//
//void CListGraph::GetNextVertices(int vertex, vector<int>& vertices) const
//{
//	vertices = out[vertex];
//}
//
//void DFS(const CListGraph& graph, vector<int>& dist, vector<int>& order, int vert)
//{
//	order.push_back(vert);
//
//	vector <int> vertices;
//	graph.GetNextVertices(vert, vertices);
//	for (int i = 0; i < vertices.size(); ++i)
//	{
//		dist[vertices[i]] = dist[vert] + 1;
//		DFS(graph, dist, order, vertices[i]);
//
//		order.push_back(vert);
//	}
//
//
//}
//
///// //////////////////////////////////////// 
//
//long long solution(vector <int>& dist, vector <int>& order, vector <int>& position, long long a1, long long a2, int x, int y, int z, int m)
//{
//
//	int n = order.size();
//
//	vector <pair <int, int> > new_ord(n);
//	for (int i = 0; i < n; ++i)
//		new_ord[i] = make_pair(dist[order[i]], order[i]);
//
//	vector <int> logarithms(n + 1);
//	for (int i = 0; i <= n; ++i)
//		logarithms[i] = log2(i);
//
//	vector <vector < pair <int, int> > >  ST(n);
//	ST[0].resize(n);
//	for (int i = 0; i < n; ++i)
//		ST[0][i] = new_ord[i];
//
//	for (int j = 1; j <= logarithms[n]; ++j)
//	{
//		int x = n - pow(2, j);
//		for (int i = 0; i <= x; ++i)
//			ST[j].push_back(min(ST[j - 1][i], ST[j - 1][i + pow(2, j - 1)]));
//	}
//
//	int k;
//	long long answer = 0;
//	long long a, b;
//	int ans = 0;
//	for (int i = 0; i < m; ++i)
//	{
//		a = position[(a1 + ans) % dist.size()];
//		b = position[a2];
//		if (a > b)
//			swap(a, b);
//		k = logarithms[b - a + 1];
//		ans = min(ST[k][a], ST[k][b - pow(2, k) + 1]).second;
//
//		answer += ans;
//
//		a1 = (x*a1 + y*a2 + z) % dist.size();
//		a2 = (x*a2 + y*a1 + z) % dist.size();
//	}
//
//	return answer;
//}
//
///// //////////////////////////////////////// 
//
//
//
//int main()
//{
//	int n, m;
//	long long a;
//	ifstream in("input.txt");
//	ofstream out("output.txt");
//	in >> n >> m;
//	CListGraph graph(n);
//	for (int i = 1; i < n; ++i)
//	{
//		in >> a;
//		graph.AddEdge(a, i);
//	}
//	int x, y, z;
//	long long b;
//	in >> a >> b;
//	in >> x >> y >> z;
//	
//	vector <int> dist(n), order, position(n, -1);
//
//	dist[0] = 0;
//	DFS(graph, dist, order, 0);
//	for (int i = 0; i < order.size(); ++i)
//		if (position[order[i]] == -1)
//			position[order[i]] = i;
//
//	cout << solution(dist, order, position, a, b, x, y, z, m) << endl;
//
//	return 0;
//}