#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

const char _whyte = 0;
const char _grey = 1;
const char _black = 2;


struct IGraph {
	virtual ~IGraph() {}

	virtual void AddEdge(int from, int to) = 0;
	virtual int VerticesCount() const = 0;
	virtual void GetNextVertices(int vertex, vector<int>& vertices) const = 0;
	virtual void GetPrevVertices(int vertex, vector<int>& vertices) const = 0;
};

class CListGraph : public IGraph {
public:
	explicit CListGraph(int _verticesCount);
	CListGraph(const IGraph* copyGraph);

	virtual void AddEdge(int from, int to);
	virtual int VerticesCount() const { return verticesCount; }
	virtual void GetNextVertices(int vertex, vector<int>& vertices) const;
	virtual void GetPrevVertices(int vertex, vector<int>& vertices) const;

private:
	int verticesCount;
	vector<vector<int> > in;
	vector<vector<int> > out;
};

CListGraph::CListGraph(int _verticesCount) :
	verticesCount(_verticesCount),
	in(verticesCount),
	out(verticesCount)
{}

CListGraph::CListGraph(const IGraph* copyGraph) :
	verticesCount(copyGraph->VerticesCount()),
	in(verticesCount),
	out(verticesCount)
{
	for (int i = 0; i < verticesCount; ++i)
	{
		copyGraph->GetPrevVertices(i, in[i]);
		copyGraph->GetNextVertices(i, out[i]);
	}
}

void CListGraph::AddEdge(int from, int to)
{
	in[to].push_back(from);
	out[from].push_back(to);
}

void CListGraph::GetNextVertices(int vertex, vector<int>& vertices) const
{
	vertices = out[vertex];
}

void CListGraph::GetPrevVertices(int vertex, vector<int>& vertices) const
{
	vertices = in[vertex];
}



struct Vertice
{
	int color;
	int len;		// длина кратчайшего пути
	int ways;		// количество кратчайших путей в вершину
	Vertice() : color(0), ways(0) {}
};

int Bfs(const IGraph& Graph, int vert_1, int vert_2)
{
	queue<int> q;
	q.push(vert_1);
	vector<Vertice> vertices;
	vertices.resize(Graph.VerticesCount());
	vertices[vert_1].len = 0;
	vertices[vert_1].ways = 1;		// из вершины в саму себя 1 кратчайший путь
	while (!q.empty())
	{
		int vert = q.front();		// вытаскиваем вершину из очереди
		q.pop();
		vertices[vert].color = _black;	// красим ее в черный
		vector<int> next;

		Graph.GetNextVertices(vert, next);
		// поиск пути
		for (int i = 0; i < (int)next.size(); ++i)
		{
			// если вершина серая, и найденный сейчас путь в эту вершину равен кратчайшему в нее
			if (vertices[next[i]].color == _grey && vertices[next[i]].len > vertices[vert].len)
			{
				vertices[next[i]].ways += vertices[vert].ways;
			}

			if (vertices[next[i]].color == _whyte)
			{
				q.push(next[i]);
				vertices[next[i]].ways += vertices[vert].ways;
				vertices[next[i]].color = _grey;
				vertices[next[i]].len = vertices[vert].len + 1;
			}
		}

		Graph.GetPrevVertices(vert, next);
		// поиск пути
		for (int i = 0; i < (int)next.size(); ++i)
		{
			// если вершина серая, и найденный сейчас путь в эту вершину равен кратчайшему в нее
			if (vertices[next[i]].color == _grey && vertices[next[i]].len > vertices[vert].len)
			{
				vertices[next[i]].ways += vertices[vert].ways;
			}

			if (vertices[next[i]].color == _whyte)
			{
				q.push(next[i]);
				vertices[next[i]].ways += vertices[vert].ways;
				vertices[next[i]].color = _grey;
				vertices[next[i]].len = vertices[vert].len + 1;
			}
		}
	}
	return vertices[vert_2].ways;
}



int main()
{
	int n, m;
	ifstream inp("input.txt");
	inp >> n >> m;
	CListGraph g(n);
	int from, to;
	for (int i = 0; i < m; ++i)
	{
		inp >> from >> to;
		g.AddEdge(from, to);
	}
	inp >> n >> m;
	cout << Bfs(g, n, m) << endl;
	inp.close();
	return 0;
}