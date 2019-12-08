#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <climits>
using namespace std;


class CListGraph {
public:
    explicit CListGraph(int _verticesCount);
    ~CListGraph() = default;

    void AddEdge(int from, int to, int weight);
    int VerticesCount() const { return verticesCount; }
    void GetNextVertices(int vertex, vector <pair <int, int> >& vertices) const;

private:
    int verticesCount;
    vector <vector <pair <int, int> > > out;
};

CListGraph::CListGraph(int _verticesCount) :
        verticesCount(_verticesCount),
        out(verticesCount)
{}

void CListGraph::AddEdge(int from, int to, int weight) {
    out[from].push_back(pair <int, int>(weight, to));
    out[to].push_back(pair <int, int>(weight, from));
}

void CListGraph::GetNextVertices(int vertex, vector <pair <int, int> >& vertices) const {
    for (int i = 0; i < out[vertex].size(); ++i) {
        vertices.push_back(out[vertex][i]);
    }
}



int Dijkstra(const CListGraph& Graph, int vert_1, int vert_2) {
    set <pair <int, int> > q;
    vector <bool> isChecked(Graph.VerticesCount());
    vector <int> dist(Graph.VerticesCount());
    isChecked.assign(Graph.VerticesCount(), false);
    dist.assign(Graph.VerticesCount(), INT_MAX);
    q.insert(pair <int, int>(0, vert_1));

    pair<int, int> vertex;
    while (!isChecked[vert_2] && !q.empty()) {
        vertex = *q.begin();
        q.erase(q.begin());
        isChecked[vertex.second] = true;
        vector <pair <int, int> > vertices;
        Graph.GetNextVertices(vertex.second, vertices);
        for (int j = 0; j < vertices.size(); ++j) {
            if (!isChecked[vertices[j].second] && vertex.first + vertices[j].first < dist[vertices[j].second]) {
                if (dist[vertices[j].second] != INT_MAX) {
                    q.erase(make_pair(dist[vertices[j].second], vertices[j].second));
                }
                q.insert(pair<int, int>(vertex.first + vertices[j].first, vertices[j].second));
                dist[vertices[j].second] = vertex.first + vertices[j].first;
            }
        }
    }
    return vertex.first;
}



int main() {
    ifstream inp("input.txt");
    ios_base::sync_with_stdio(false);

    int n, m;
    inp >> n >> m;
    CListGraph graph(n);
    int from, to, weight;
    for (int i = 0; i < m; ++i) {
        inp >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }

    int vert_1, vert_2;
    inp >> vert_1 >> vert_2;
    cout << Dijkstra(graph, vert_1, vert_2) << endl;

    inp.close();
    return 0;
}
