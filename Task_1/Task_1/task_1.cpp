#include <iostream>
#include <vector>
using namespace std;

class animals
{
public:
	virtual ~animals()
	{
		cout << "animal";
	}
};

class cat : public animals
{
public:
	cat()
	{
		cout << "kaef";
	}
	~cat()
	{
		cout << "cat";
	}
};

class dog : public animals
{
public:
	dog()
	{
		cout << "kaef";
	}
	~dog()
	{
		cout << "dog";
	}
};





int main()
{

	/*animals* anim = new animals[100];
	cat anim[1];
	dog anim[2];*/

	vector<int> a;
	a[0] = 5;
	cout << a[0];
	return 0;
}