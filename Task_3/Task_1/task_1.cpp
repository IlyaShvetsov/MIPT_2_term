#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <climits>
using namespace std;


class CMatrixGraph {
public:
    explicit CMatrixGraph(int _verticesCount);
    ~CMatrixGraph() = default;

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

void CMatrixGraph::AddEdge(int from, int to, int len) {
    edges[from][to] = len;
}

void CMatrixGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    for (int i = 0; i < verticesCount; ++i) {
        vertices.push_back(edges[vertex][i]);
    }
}



int Prim(const CMatrixGraph& Graph) {
    set <pair <int, int> > q;
    vector <bool> isChecked(Graph.VerticesCount(), false);
    int ok = 1, sum = 0;
    isChecked[0] = true;

    vector <int> vertices;
    Graph.GetNextVertices(0, vertices);
    for (int i = 0; i < vertices.size(); ++i) {
        q.insert(make_pair(vertices[i], i));
    }

    pair <int, int> edge;
    while (ok != Graph.VerticesCount()) {
        edge = *q.begin();
        q.erase(q.begin());
        if (!isChecked[edge.second]) {
            isChecked[edge.second] = true;
            vector <int> vertices;
            Graph.GetNextVertices(edge.second, vertices);

            for (int i = 0; i < vertices.size(); ++i) {
                q.insert(make_pair(vertices[i], i));
            }

            sum += edge.first;
            ok++;
        }
    }
    return sum;
}



int main() {
    int n, m;
    ifstream inp("prim.in");
    ofstream out("prim.out");
    inp >> n >> m;
    CMatrixGraph graph(n);
    int from, to, weight;
    for (int i = 0; i < m; ++i) {
        inp >> from >> to >> weight;
        graph.AddEdge(from - 1, to - 1, weight);
    }

    out << Prim(graph) << endl;

    out.close();
    inp.close();
    return 0;
}
