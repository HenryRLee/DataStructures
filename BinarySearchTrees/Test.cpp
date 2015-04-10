#include <iostream>
#include "RedBlackTree.h"

using namespace std;


int main(void)
{
	RedBlackTree <int> tree;
	RedBlackNode <int> * node;

	srand(time(NULL));

	cout << "Inserting ";

	for (int i=0; i<10; i++)
	{
		int random = rand()%100;
		tree.InsertElement(random);
		cout << random << " ";
	}

	tree.InsertElement(77);
	cout << 77;

	cout << endl;

	cout << "Tree walk ";
	tree.InorderTreeWalk();

	node = tree.MinimumNode();

	if (node != NULL)
	{
		cout << "Found minimum ";
		node->PrintKey();
		cout << endl;
	}

	node = tree.MaximumNode();

	if (node != NULL)
	{
		cout << "Found maximum ";
		node->PrintKey();
		cout << endl;
	}

	node = tree.KeySearch(77);

	if (node != NULL)
	{
		RedBlackNode <int> * nextnode;

		cout << "Found key ";
		node->PrintKey();
		cout << endl;

		nextnode = tree.SuccessorNode(node);
		if (nextnode != NULL)
		{
			cout << "Successor ";
			nextnode->PrintKey();
			cout << endl;

			tree.DeleteNode(nextnode);

			cout << "Successor deleted ";
			tree.InorderTreeWalk();
		}

		nextnode = tree.PredecessorNode(node);
		if (nextnode != NULL)
		{
			cout << "Predecessor ";
			nextnode->PrintKey();
			cout << endl;

			tree.DeleteNode(nextnode);

			cout << "Predecessor deleted ";
			tree.InorderTreeWalk();
		}

	}

	if (tree.DeleteElement(77))
	{
		cout << "Delete element 77" << endl;
		tree.InorderTreeWalk();
	}

	return 0;
}
