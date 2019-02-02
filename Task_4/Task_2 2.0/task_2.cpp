#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


class SegmentTree {
public:
	SegmentTree(int n, vector <int>& arr) :
		tree(n * 4, pair<int, int>(0, 0)),
		size(n) { Build(arr, 0, 0, n - 1); }
	~SegmentTree() {}

	void Build(vector <int>& arr, int vertice, int T_left, int T_right);
	int Get_max(int vertice, int T_left, int T_right, int left, int right);
	void Update(int vertice, int T_left, int T_right, int left, int right, int add);
	void Push(int vertice);

private:
	vector <pair <int, int> > tree;
	int size;
};

void SegmentTree::Build(vector <int>& arr, int vertice, int T_left, int T_right)
{
	if (T_left == T_right)
		tree[vertice] = make_pair(arr[T_left], 0);
	else
	{
		int T_medium = (T_left + T_right) / 2;
		Build(arr, vertice * 2 + 1, T_left, T_medium);
		Build(arr, vertice * 2 + 2, T_medium + 1, T_right);
		tree[vertice] = max(tree[vertice * 2 + 1], tree[vertice * 2 + 2]);
	}
}

void SegmentTree::Push(int vertice)
{
	tree[vertice * 2 + 1].second = tree[vertice * 2 + 1].second + tree[vertice].second;
	tree[vertice * 2 + 2].second = tree[vertice * 2 + 2].second + tree[vertice].second;
	tree[vertice].second = 0;     // Нейтральный элемент 
}

int SegmentTree::Get_max(int vertice, int T_left, int T_right, int left, int right)
{
	if (left > right)
		return 0;
	if (left == T_left && right == T_right)
		return tree[vertice].first + tree[vertice].second;
	Push(vertice);

	int T_medium = (T_left + T_right) / 2;

	int ans = max(
		Get_max(vertice * 2 + 1, T_left, T_medium, left, min(right, T_medium)),
		Get_max(vertice * 2 + 2, T_medium + 1, T_right, max(left, T_medium + 1), right)
	);

	int a = tree[vertice * 2 + 1].first + tree[vertice * 2 + 1].second;
	int b = tree[vertice * 2 + 2].first + tree[vertice * 2 + 2].second;
	tree[vertice].first = max(a, b);

	return ans;
}

void SegmentTree::Update(int vertice, int T_left, int T_right, int left, int right, int add)
{
	if (left > right)
		return;
	if (left == T_left && T_right == right)
		tree[vertice].second += add;
	else
	{
		Push(vertice);

		int T_medium = (T_left + T_right) / 2;
		Update(vertice * 2 + 1, T_left, T_medium, left, min(right, T_medium), add);
		Update(vertice * 2 + 2, T_medium + 1, T_right, max(left, T_medium + 1), right, add);
		int a = tree[vertice * 2 + 1].first + tree[vertice * 2 + 1].second;
		int b = tree[vertice * 2 + 2].first + tree[vertice * 2 + 2].second;
		tree[vertice].first = max(a, b);
	}
}



int main()
{
	int n, capacity, input, m;
	ifstream in("input.txt");
	in >> n;
	n--;
	vector<int> arr(n, 0);
	for (int i = 0; i < n; ++i)
	{
		in >> input;
		arr[i] = input;
	}
	in >> capacity >> m;

	SegmentTree Tree(n, arr);

	int left, right, add;
	for (int i = 0; i < m; ++i)
	{
		in >> left >> right >> add;
		if (Tree.Get_max(0, 0, n - 1, left, right - 1) + add <= capacity)
			Tree.Update(0, 0, n - 1, left, right - 1, add);
		else
			cout << i << ' ';
	}

	return 0;
}