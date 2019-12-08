#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


class CAdjacencyMatrix {
public:
    explicit CAdjacencyMatrix(int _verticesCount);
    ~CAdjacencyMatrix() = default;

    void AddEdge(int from, int to, int len);
    int VerticesCount() const { return verticesCount; }
    void GetNextVertices(int vertex, vector<int>& vertices) const;
    void GetPrevVertices(int vertex, vector<int>& vertices) const;

private:
    int verticesCount;
    vector<vector<int> > edges;
};

CAdjacencyMatrix::CAdjacencyMatrix(int _verticesCount) :
        verticesCount(_verticesCount),
        edges(verticesCount) {
    for (int i = 0; i < verticesCount; ++i)
        edges[i].resize(verticesCount);
}

void CAdjacencyMatrix::AddEdge(int from, int to, int len) {
    edges[from][to] = len;
}

void CAdjacencyMatrix::GetNextVertices(int vertex, vector<int>& vertices) const {
    for (int i = 0; i < verticesCount; ++i) {
        vertices.push_back(edges[vertex][i]);
    }
}

void CAdjacencyMatrix::GetPrevVertices(int vertex, vector<int>& vertices) const {
    for (int i = 0; i < verticesCount; ++i) {
        vertices.push_back(edges[i][vertex]);
    }
}



int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void Floyd(const CAdjacencyMatrix& Graph, vector<vector<int> >& distances) {
    for (int i = 0; i < Graph.VerticesCount(); ++i) {
        Graph.GetNextVertices(i, distances[i]);
    }

    for (int k = 0; k < Graph.VerticesCount(); ++k) {
        for (int i = 0; i < Graph.VerticesCount(); ++i) {
            for (int j = 0; j < Graph.VerticesCount(); ++j) {
                distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
            }
        }
    }
}



int main() {
    int n, edge;
    ifstream inp("floyd.in");
    ofstream out("floyd.out");
    inp >> n;
    CAdjacencyMatrix graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inp >> edge;
            graph.AddEdge(i, j, edge);
        }
    }

    vector<vector<int> > distances;
    distances.resize(n);
    Floyd(graph, distances);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << distances[i][j] << ' ';
        }
        out << endl;
    }

    inp.close();
    out.close();
    return 0;
}
