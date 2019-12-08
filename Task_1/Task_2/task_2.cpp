#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

const char _whyte = 0;
const char _grey = 1;
const char _black = 2;


struct IGraph {
    virtual ~IGraph() = default;

    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;
    virtual void GetNextVertices(int vertex, vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, vector<int>& vertices) const = 0;
};

class CListGraph : public IGraph {
public:
    explicit CListGraph(int _verticesCount);
    CListGraph(const IGraph* copyGraph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override { return verticesCount; }
    void GetNextVertices(int vertex, vector<int>& vertices) const override;
    void GetPrevVertices(int vertex, vector<int>& vertices) const override;

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
        out(verticesCount) {
    for (int i = 0; i < verticesCount; ++i) {
        copyGraph->GetPrevVertices(i, in[i]);
        copyGraph->GetNextVertices(i, out[i]);
    }
}

void CListGraph::AddEdge(int from, int to) {
    in[to].push_back(from);
    out[from].push_back(to);
}

void CListGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    vertices = out[vertex];
}

void CListGraph::GetPrevVertices(int vertex, vector<int>& vertices) const {
    vertices = in[vertex];
}



struct Vertex {
    int color;
    int len;
    Vertex() : color(0), len(0) {}
};

bool bfs(const IGraph& Graph, int vertex) {
    queue<int> q;
    vector<Vertex> vertices;
    vertices.resize(Graph.VerticesCount());
    q.push(vertex);
    while (!q.empty()) {
        int vert = q.front(); // вытаскиваем вершину из очереди
        q.pop();
        vertices[vert].color = _black; // красим ее в черный
        vector<int> next;

        Graph.GetNextVertices(vert, next);
        // проверка на цикл
        for (int i = 0; i < next.size(); ++i) {
            // если вершина серая, и цикл меньше min
            if (vertices[next[i]].color == _grey) {
                return (vertices[next[i]].len + vertices[vert].len + 1);
            }

            if (vertices[next[i]].color == _whyte) {
                q.push(next[i]);
                vertices[next[i]].color = _grey;
                vertices[next[i]].len = vertices[vert].len + 1;
            }
        }

        Graph.GetPrevVertices(vert, next);
        // проверка на цикл
        for (int i = 0; i < (int)next.size(); ++i) {
            // если вершина серая, и цикл меньше min
            if (vertices[next[i]].color == _grey) {
                return (vertices[next[i]].len + vertices[vert].len + 1);
            }

            if (vertices[next[i]].color == _whyte) {
                q.push(next[i]);
                vertices[next[i]].color = _grey;
                vertices[next[i]].len = vertices[vert].len + 1;
            }
        }

    }
    return 1000000;
}

int Find(const IGraph& Graph) {
    int min = 1000000, result = min;
    // если нашли цикл размера 3, выходим
    for (int i = 0; i < Graph.VerticesCount() && min != 3; ++i) {
        result = bfs(Graph, i);
        if (result < min) {
            min = result;
        }
    }

    if (min == 1000000) {
        return -1;  // если не нашли цикл, возвращаем -1
    } else {
        return min; // иначе возвращаем длину цикла
    }
}



int main() {
    int n, m;
    ifstream inp("input.txt");
    inp >> n >> m;
    CListGraph g(n);
    int from, to;
    for (int i = 0; i < m; ++i) {
        inp >> from >> to;
        g.AddEdge(from, to);
    }
    cout << Find(g) << endl;
    inp.close();
    return 0;
}
