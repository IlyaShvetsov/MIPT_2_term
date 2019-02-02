//#include "True_solution.h"
//#include <limits.h>
//const float FLOAT_MAX = pow(10, 38);
//
//
//True_solution::True_solution(const CMatrixGraph& graph) :
//	verticesCount(graph.VerticesCount()),
//	edges(verticesCount),
//	ans(FLOAT_MAX)
//{
//	for (int i = 0; i < verticesCount; ++i)
//		graph.GetNextVertices(i, edges[i]);
//}
//
//void True_solution::solution(vector <int>& order, vector <int>& remainder)
//{
//	for (int i = 0; i < remainder.size(); ++i)
//	{
//		vector <int> new_order = order;
//		new_order.push_back(remainder[i]);
//		vector <int> new_remainder;
//		for (int j = 0; j < remainder.size(); ++j)
//			if (j != i)
//				new_remainder.push_back(remainder[j]);
//		solution(new_order, new_remainder);
//	}
//
//	if (order.size() != verticesCount)
//		return;
//
//	float sum = edges[order[verticesCount - 1]][order[0]];
//	for (int i = 1; i < verticesCount; ++i)
//		sum += edges[order[i - 1]][order[i]];
//
//	if (sum < ans)
//		ans = sum;
//}
//
//float True_solution::Solution()
//{
//	vector <int> order, remainder;
//	for (int i = 0; i < verticesCount; ++i)
//		remainder.push_back(i);
//
//	solution(order, remainder);
//
//	return ans;
//}

#include <iostream>
#include <string>
#include <algorithm>
#include "True_solution.h"
const float FLOAT_MAX = pow(10, 38);


True_solution::True_solution(const CMatrixGraph& graph) :
	verticesCount(graph.VerticesCount()),
	edges(verticesCount), 
	ans(FLOAT_MAX)
{
	for (int i = 0; i < verticesCount; ++i)
		graph.GetNextVertices(i, edges[i]);
}

float True_solution::Solution()
{
	vector <int> order;
	for (int i = 0; i < verticesCount; ++i)
		order.push_back(i);

	do {
		float sum = edges[order[verticesCount - 1]][order[0]];
			for (int i = 1; i < verticesCount; ++i)
				sum += edges[order[i - 1]][order[i]];
		
			if (sum < ans)
				ans = sum;
	} while (next_permutation(order.begin(), order.end()));

	return ans;
}