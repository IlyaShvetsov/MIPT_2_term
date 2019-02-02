#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;


class SegmentTree {
public:
	SegmentTree(int n) :
		tree(n * 4),
		size(n) {}
	~SegmentTree() {}

	void build(vector <int>& arr, int vertice, int T_left, int T_right);
	pair <int, int> get_max(int vertice, int T_left, int T_right, int left, int right);
	void update(int vertice, int T_left, int T_right, int left, int right, int add);
	void push(int vertice);

private:
	vector <pair <int, int> > tree;
	int size;
};

void SegmentTree::build(vector <int>& arr, int vertice, int T_left, int T_right)
{
	if (T_left == T_right)
		tree[vertice] = make_pair(arr[T_left], 0);
	else
	{
		int T_medium = (T_left + T_right) / 2;
		build(arr, vertice * 2 + 1, T_left, T_medium);
		build(arr, vertice * 2 + 2, T_medium + 1, T_right);
		tree[vertice] = max(tree[vertice * 2 + 1], tree[vertice * 2 + 2]);
	}
}

pair <int, int> SegmentTree::get_max(int vertice, int T_left, int T_right, int left, int right)
{
	if (left > right)
		return make_pair(INT_MIN, INT_MIN);
	if (left == T_left && right == T_right)
		return tree[vertice];

	int T_medium = (T_left + T_right) / 2;

	int a = max(
		get_max(vertice * 2 + 1, T_left, T_medium, left, min(right, T_medium)).first,
		get_max(vertice * 2 + 2, T_medium + 1, T_right, max(left, T_medium + 1), right).first
	);

	int b = max(
		get_max(vertice * 2 + 1, T_left, T_medium, left, min(right, T_medium)).second,
		get_max(vertice * 2 + 2, T_medium + 1, T_right, max(left, T_medium + 1), right).second
	);

	return make_pair(a, b);
}

void SegmentTree::push(int vertice)
{                                               
	tree[vertice * 2 + 1].second = tree[vertice * 2 + 1].second + tree[vertice].second;
	tree[vertice * 2 + 2].second = tree[vertice * 2 + 2].second + tree[vertice].second;
	tree[vertice].second = INT_MIN;     // Нейтральный элемент 
}

void SegmentTree::update(int vertice, int T_left, int T_right, int left, int right, int add)
{
	if (left > right)
		return;
	if (left == T_left && T_right == right)
		tree[vertice].second += add;
	else 
	{
		push(vertice);

		int T_medium = (T_left + T_right) / 2;
		update(vertice * 2 + 1, T_left, T_medium, left, min(right, T_medium), add);
		update(vertice * 2 + 2, T_medium + 1, T_right, max(left, T_medium + 1), right, add);
		//tree[vertice] = max(tree[vertice], max(tree[vertice * 2 + 1], tree[vertice * 2 + 2]));
	}
}



int main()
{
	int n, capacity, input, m;
	ifstream in("input.txt");
	in >> n;
	n--;
	vector <int> arr(n);
	for (int i = 0; i < n; ++i)
	{
		in >> input;
		arr[i] = input;
	}
	in >> capacity >> m;

	SegmentTree Tree(n);
	Tree.build(arr, 0, 0, n - 1);

	int left, right, add;
	for (int i = 0; i < m; ++i)
	{
		in >> left >> right >> add;
		int m = Tree.get_max(0, 0, n - 1, left, right - 1).first + Tree.get_max(0, 0, n - 1, left, right - 1).second;
		if (m + add <= capacity)
			Tree.update(0, 0, n - 1, left, right - 1, add);
		else
			cout << i << ' ';
	}

	return 0;
}