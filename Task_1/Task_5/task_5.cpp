#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;


class CAdjacencyMatrix {
public:
	explicit CAdjacencyMatrix(int _verticesCount);
	~CAdjacencyMatrix() {}

	virtual void AddEdge(int from, int to, double len);
	virtual int VerticesCount() const { return verticesCount; }
	virtual void GetNextVertices(int vertex, vector<double>& vertices) const;
	virtual void GetPrevVertices(int vertex, vector<double>& vertices) const;

private:
	int verticesCount;
	vector<vector<double> > edges;
};

CAdjacencyMatrix::CAdjacencyMatrix(int _verticesCount) :
	verticesCount(_verticesCount),
	edges(verticesCount, vector<double>(_verticesCount))
{}

void CAdjacencyMatrix::AddEdge(int from, int to, double len)
{
	edges[from][to] = len;
}

void CAdjacencyMatrix::GetNextVertices(int vertex, vector<double>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		vertices.push_back(edges[vertex][i]);
}

void CAdjacencyMatrix::GetPrevVertices(int vertex, vector<double>& vertices) const
{
	for (int i = 0; i < verticesCount; ++i)
		vertices.push_back(edges[i][vertex]);
}



struct Vertice
{
	bool isChecked;
	pair <int, int> coordinates;
	bool is_right;
	bool is_left;
	Vertice() : isChecked(false), is_right(false), is_left(false) {}
};

void FindDistances(CAdjacencyMatrix& Graph, vector<Vertice>& vertices)
{
	for (int i = 0; i < Graph.VerticesCount(); ++i)
	{
		Graph.AddEdge(0, i, pow((vertices[0].coordinates.first - vertices[i].coordinates.first), 2));
		Graph.AddEdge(i, 0, pow((vertices[0].coordinates.first - vertices[i].coordinates.first), 2));
	}
	for (int i = 1; i < Graph.VerticesCount() - 1; ++i)
		for (int j = 1; j < Graph.VerticesCount() - 1; ++j)
			Graph.AddEdge(i, j, pow((vertices[i].coordinates.first - vertices[j].coordinates.first), 2)
				+ pow((vertices[i].coordinates.second - vertices[j].coordinates.second), 2));
	for (int i = 0; i < Graph.VerticesCount(); ++i)
	{
		Graph.AddEdge(Graph.VerticesCount() - 1, i, pow((vertices[Graph.VerticesCount() - 1].coordinates.first - vertices[i].coordinates.first), 2));
		Graph.AddEdge(i, Graph.VerticesCount() - 1, pow((vertices[Graph.VerticesCount() - 1].coordinates.first - vertices[i].coordinates.first), 2));
	}
}


bool dfs(const CAdjacencyMatrix& Graph, vector<Vertice>& vertices, int index, double table, int radius)
{
	vertices[index].isChecked = true;
	vector<double> next;
	Graph.GetNextVertices(index, next);
	for (int i = 0; i < Graph.VerticesCount(); ++i)
	{
		long double edge = 0;
		if (((vertices[index].is_left) && (vertices[i].is_right)) ||
			((vertices[index].is_right) && (vertices[i].is_left)))
		{
			edge = table*table;
		}
		else if (((vertices[index].is_left) || (vertices[index].is_right)) ||
			((vertices[i].is_left) || (vertices[i].is_right)))
		{
			edge = pow((table + radius), 2);
		}
		else
		{
			edge = pow((table + 2 * radius), 2);
		}		
		if (next[i] < edge && !vertices[i].isChecked)
		{
			dfs(Graph, vertices, i, table, radius);
			if (vertices[Graph.VerticesCount() - 1].isChecked)
				return false;
		}
	}
	return true;
}

double BinSearch(const CAdjacencyMatrix& Graph, vector<Vertice> vertices, int xr, int radius)
{
	double table = xr;
	double max = table;
	double min = 0;
	while (max - min > 0.000001 || max - min < -0.000001)
	{
		for (int i = 0; i < Graph.VerticesCount(); ++i)
			vertices[i].isChecked = false;
		if (dfs(Graph, vertices, 0, table, radius))
			min = table;
		else
			max = table;
		table = (min + max) / 2;
	}
	return table;
}



int main()
{
	int xl, xr, radius, n;
	ifstream inp("input.txt");
	inp >> xl >> xr >> radius >> n;
	CAdjacencyMatrix graph(n + 2);

	vector<Vertice> vertices;
	vertices.resize(n + 2);
	vertices[0].is_left = true;
	vertices[0].coordinates = pair <int, int>(xl, 0);
	vertices[n + 1].is_right = true;
	vertices[n + 1].coordinates = pair <int, int>(xr, 0);
	int x, y;
	for (int i = 1; i <= n; ++i)
	{
		inp >> x >> y;
		vertices[i].coordinates = pair<int, int>(x, y);
	}
	FindDistances(graph, vertices);
	printf("%.3f", BinSearch(graph, vertices, xr, radius));

	inp.close();
	return 0;
}