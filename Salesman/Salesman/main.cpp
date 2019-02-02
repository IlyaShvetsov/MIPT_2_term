#include <iostream>
#include "Prim_solution.h"
#include "True_solution.h"
#include "Generator.h"
#include <ctime>


int main()
{
	srand(time(NULL));
	Generator Gener;

	int experiments, points_count;
	cin >> experiments >> points_count;

	vector <float> errors;
	float a, b, sum = 0;
	for (int i = 0; i < experiments; ++i)
	{
		CMatrixGraph graph = Gener.Generate(points_count);
		Prim_solution prim(graph);
		True_solution tru(graph);
		a = prim.Solution();
		b = tru.Solution();
		cout << a  << endl;
		errors.push_back(a - b);
		sum += (a - b);
	}

	float medium = sum / experiments;
	sum = 0;
	for (int i = 0; i < experiments; ++i)
		sum += pow((errors[i] - medium), 2);
	sum = sqrt(sum / experiments);
	
	cout << sum * 100 << '%' << endl;

	return 0;
}