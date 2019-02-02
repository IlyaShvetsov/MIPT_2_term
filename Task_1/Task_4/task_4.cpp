#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream inp("input.txt");


class CMatrixGraph {
public:
	explicit CMatrixGraph(int n);
	~CMatrixGraph() {}
	void FillGraph();
	bool Find();

private:
	int verticesCount;
	vector<vector<bool> > edges;
};

CMatrixGraph::CMatrixGraph(int _verticesCount) :
	verticesCount(_verticesCount),
	edges(verticesCount)
{
	for (int i = 0; i < verticesCount; ++i)
		edges[i].resize(verticesCount);
}

void CMatrixGraph::FillGraph()
{
	int a;
	for (int i = 0; i < verticesCount; ++i)
		for (int j = 0; j < verticesCount; ++j)
		{
			inp >> a;
			if (a)
				edges[i][j] = 1;
			else
				edges[i][j] = 0;
		}
}

bool CMatrixGraph::Find()
{
	int i = 0;
				// идем лесенкой вниз
	for (int j = 0; j < verticesCount; ++j)
	{
		for ( ; (i < verticesCount) && ((edges[i][j] == 1 && i != j) || (edges[i][j] == 0 && i == j)); ++i);
				// если дошли до конца, проверяем, сток ли это
		if (i == verticesCount)
		{
			for (i = 0; (i < verticesCount) && ((edges[i][j] == 1 && i != j) || (edges[i][j] == 0 && i == j)); ++i);
			if (i == verticesCount)		
			{
				for (i = 0; (i < verticesCount) && (edges[j][i] == 0); ++i);
				if (i == verticesCount)
				// нашли сток
					return true;
				else
				// если это не сток, то стока нет и во всем графе
					return false;
			}
		}
	}
	return false;
}



int main()
{
	int n;
	inp >> n;
	CMatrixGraph g(n);
	g.FillGraph();
	if (g.Find())
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}