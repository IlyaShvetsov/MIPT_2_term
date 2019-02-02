#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;



int second_min(int& a, int& b, int& c, int& d)
{
	int x, y;
	if (a > b)
		x = a;
	else
		x = b;
	if (c < d)
		y = c;
	else
		y = d;
	if (x < y)
		return x;
	else
		return y;
}

void solution(const vector <int>& arr, const vector <pair <int, int> >& section, vector <int>& ans)
{
	int n = arr.size();
	vector <int> logarithms(n + 1);
	for (int i = 0; i <= n; ++i)
		logarithms[i] = log2(i);

	vector <vector <pair <int, int> > > ST(n);
	ST[0].resize(n);
	for (int i = 0; i < n; ++i)
		ST[0][i] = make_pair(arr[i], INT_MAX);

	for (int j = 1; j <= logarithms[n]; ++j)
	{
		int x = n - pow(2, j);
		for (int i = 0; i <= x; ++i)
			ST[j].push_back(make_pair(min(ST[j - 1][i].first, ST[j - 1][i + pow(2, j - 1)].first),
				second_min(ST[j - 1][i].first, ST[j - 1][i + pow(2, j - 1)].first, ST[j - 1][i].second,
					ST[j - 1][i + pow(2, j - 1)].second)));
	}

	int a, b, k;
	for (int i = 0; i < section.size(); ++i)
	{
		a = section[i].first;
		b = section[i].second;
		k = logarithms[b - a + 1];
		if (ST[k][a].first == ST[k][b - pow(2, k) + 1].first)
			ans.push_back(min(ST[k][a].second, ST[k][b - pow(2, k) + 1].second));
		else
			ans.push_back(second_min(ST[k][a].first, ST[k][b - pow(2, k) + 1].first, ST[k][a].second, ST[k][b - pow(2, k) + 1].second));
	}
}



int main()
{
	int n, m, a, b;
	cin >> n >> m;
	vector <int> arr;
	vector <pair <int, int> > section;
	for (int i = 0; i < n; ++i)
	{
		cin >> a;
		arr.push_back(a);
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> a >> b;
		section.push_back(make_pair(--a, --b));
	}

	vector <int> ans;
	solution(arr, section, ans);
	for (int i = 0; i < m; ++i)
		cout << ans[i] << endl;

	return 0;
}