#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;


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
	in(verticesCount + 1),
	out(verticesCount + 1)
{}

CListGraph::CListGraph(const IGraph* copyGraph) :
	verticesCount(copyGraph->VerticesCount()),
	in(verticesCount + 1),
	out(verticesCount + 1)
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



void DFS_1(int vert, vector<bool>& color, stack<int>& order, vector<vector<int> >& primary)
{
	color[vert] = 1;
	for (int i = 0; i < (int)primary[vert].size(); ++i)
		if (color[primary[vert][i]] == 0)
			DFS_1(primary[vert][i], color, order, primary);
	order.push(vert);
}

void DFS_2(int vert, vector<bool>& color, stack<int>& component, vector<vector<int> >& reverced)
{
	color[vert] = 1;
	component.push(vert);
	for (int i = 0; i < (int)reverced[vert].size(); ++i)
		if (color[reverced[vert][i]] == 0)
			DFS_2(reverced[vert][i], color, component, reverced);
}

int Find_components(const CListGraph& Graph, vector<vector<int> >& primary, vector<vector<int> >& reverced, vector<int>& components)      // алгоритм Косарайю
{
	stack<int> order, component;
	vector<bool> color;
	color.resize(Graph.VerticesCount() + 1);
	components.resize(Graph.VerticesCount() + 2);

	for (int i = 1; i <= Graph.VerticesCount(); ++i)
		if (color[i] == 0)
			DFS_1(i, color, order, primary);
	color.assign(Graph.VerticesCount() + 1, 0);
	int comp_color = 1;
	for (int i = 1; i <= Graph.VerticesCount(); ++i)
	{
		int vert = order.top();
		order.pop();
		if (color[vert] == 0) {
			DFS_2(vert, color, component, reverced);
			while (!component.empty())
			{
				components[component.top()] = comp_color;
				component.pop();
			}
			comp_color++;
		}
	}
	return comp_color - 1;
}

int Find_Edges(const CListGraph& Graph, int compCount, vector<int>& components, vector<vector<int> >& primary)
{
	if (compCount == 1)
		return 0;
	vector<bool> in, out;
	in.resize(compCount + 1);
	in.assign(compCount + 1, false);
	out.resize(compCount + 1);
	out.assign(compCount + 1, false);
	for (int i = 1; i <= Graph.VerticesCount(); ++i)
		for (int j = 0; j < (int)primary[i].size(); ++j)
			if (components[i] != components[primary[i][j]])
			{
				in[components[i]] = true;
				out[components[primary[i][j]]] = true;
			}
	int in_f = 0, out_f = 0;
	for (int i = 1; i <= compCount; ++i)
	{
		if (!in[i])
			in_f++;
		if (!out[i])
			out_f++;
	}
	return max(in_f, out_f);
}



int main()
{
	int n, m;
	ifstream inp("input.txt");
	inp >> n >> m;
	CListGraph graph(n);
	int from, to;
	for (int i = 0; i < m; ++i)
	{
		inp >> from >> to;
		graph.AddEdge(from, to);
	}

	vector<vector<int> > primary, reverced;
	primary.resize(graph.VerticesCount() + 1);
	reverced.resize(graph.VerticesCount() + 1);
	for (int i = 0; i < graph.VerticesCount(); ++i)
	{
		graph.GetNextVertices(i, primary[i]);
		graph.GetPrevVertices(i, reverced[i]);
	}
	vector<int> components;
	int compCount = Find_components(graph, primary, reverced, components);
	cout << Find_Edges(graph, compCount, components, primary);

	inp.close();
	return 0;
}