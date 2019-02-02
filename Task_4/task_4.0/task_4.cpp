#include <iostream>
#include <string>
#include <stack>
using namespace std;


struct CNode_Dec
{
	string value;
	int priority;
	int c;
	CNode_Dec* left;
	CNode_Dec* right;

	CNode_Dec(string _value, int _priority) :
		value(_value),
		priority(_priority),
		left(0), right(0),
		c(0) {}
};

class Tree_Dec {
public:
	Tree_Dec() : root(NULL) {}
	~Tree_Dec() { DFS_Destr(root); }

	void InsertAt(int position, const string& value);
	void DeleteAt(int position);
	string GetAt(int position);
	void Insert(CNode_Dec*& Node, int key, int priority);
	CNode_Dec* root;

private:
	void DFS_Destr(CNode_Dec* Node);
	void split(CNode_Dec* Node, int key, CNode_Dec*& leftTree, CNode_Dec*& rightTree);
	CNode_Dec* merge(CNode_Dec* leftTree, CNode_Dec* rightTree);
};

void Tree_Dec::DFS_Destr(CNode_Dec* Node)
{
	if (Node == NULL)
		return;
	DFS_Destr(Node->left);
	DFS_Destr(Node->right);
	delete Node;
}

void Tree_Dec::split(CNode_Dec* Node, int key, CNode_Dec*& leftTree, CNode_Dec*& rightTree)
{
	if (Node == NULL)
	{
		leftTree = 0;
		rightTree = 0;
		return;
	}

	if (Node->Key <= key)
	{
		split(Node->right, key, Node->right, rightTree);
		leftTree = Node;
	}
	else
	{
		split(Node->left, key, leftTree, Node->left);
		rightTree = Node;
	}
}

CNode_Dec* Tree_Dec::merge(CNode_Dec* leftTree, CNode_Dec* rightTree)
{
	if (leftTree == 0)
		return rightTree;

	if (rightTree == 0)
		return leftTree;

	if (rightTree->priority > leftTree->priority)
	{
		rightTree->left = merge(leftTree, rightTree->left);
		return rightTree;
	}
	else 
	{
		leftTree->right = merge(leftTree->right, rightTree);
		return leftTree;
	}
}

void Tree_Dec::Insert(CNode_Dec*& Node, int key, int priority)
{
	if (root == NULL)
	{
		root = new CNode_Dec(key, priority);
		root->c = 1;
		return;
	}
	if (Node->priority < priority)
	{
		CNode_Dec* leftTree;
		CNode_Dec* rightTree;
		split(Node, key, leftTree, rightTree);
		CNode_Dec* NewNode = new CNode_Dec(key, priority);
		NewNode->left = leftTree;
		NewNode->right = rightTree;
		Node = NewNode;
		return;
	}
	if (Node->value <= key)
		if (Node->right != NULL)
			Insert(Node->right, key, priority);
		else
			Node->right = new CNode_Dec(key, priority);
	else
		if (Node->left != NULL)
			Insert(Node->left, key, priority);
		else
			Node->left = new CNode_Dec(key, priority);;
}



int main()
{
	int n;
	cin >> n;
	Tree_Dec tree;

	for (int i = 0; i < n; ++i)
	{
		char operation;
		int index;
		cin >> operation >> index;
		index++;

		if (operation == '?')
			cout << tree.GetAt(index) << endl;

		else if (operation == '-')
			tree.DeleteAt(index);

		else if (operation == '+')
		{
			string str;
			cin >> str;
			tree.InsertAt(index, str);
		}
	}
}