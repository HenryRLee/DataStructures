#include <iostream>

using namespace std;

template <class T>
class BinarySearchNode
{
public:
	T key;

	BinarySearchNode <T> * left;
	BinarySearchNode <T> * right;
	BinarySearchNode <T> * parent;

	void PrintKey(void);

	void InorderTreeWalk(void);

	BinarySearchNode <T> * SuccessorNode(void);
	BinarySearchNode <T> * PredecessorNode(void);

	BinarySearchNode(void);
};

template <class T>
class BinarySearchTree
{
	BinarySearchNode <T> * root;

public:
	void InsertNode(BinarySearchNode <T> * key);
	void InsertElement(T key);

	void RemoveNode(BinarySearchNode <T> * key);
	void RemoveElement(T key);

	void InorderTreeWalk(void);

	BinarySearchNode <T> * KeySearch(T key);
	BinarySearchNode <T> * MinimumNode(void);
	BinarySearchNode <T> * MaximumNode(void);

	BinarySearchTree(void);
};

template <class T>
void BinarySearchNode<T>::PrintKey(void)
{
	cout << key << " ";
}

template <class T>
void BinarySearchNode<T>::InorderTreeWalk(void)
{
	if (left != NULL)
		left->InorderTreeWalk();

	PrintKey();

	if (right != NULL)
		right->InorderTreeWalk();
}

template <class T>
BinarySearchNode <T> * BinarySearchNode<T>::SuccessorNode(void)
{
	BinarySearchNode <T> * x;
	BinarySearchNode <T> * y;

	if (this->right != NULL)
	{
		x = this->right;

		while (x->left != NULL)
			x = x->left;

		return x;
	}
	else
	{
		y = this->parent;
		x = this;

		while (y != NULL and x == y->right)
		{
			x = y;
			y = y->parent;
		}

		return y;
	}
}

template <class T>
BinarySearchNode <T> * BinarySearchNode<T>::PredecessorNode(void)
{
	BinarySearchNode <T> * x;
	BinarySearchNode <T> * y;

	if (this->left != NULL)
	{
		x = this->left;

		while (x->right != NULL)
			x = x->right;

		return x;
	}
	else
	{
		y = this->parent;
		x = this;

		while (y != NULL and x == y->left)
		{
			x = y;
			y = y->parent;
		}

		return y;
	}
}

template <class T>
BinarySearchNode<T>::BinarySearchNode(void)
{
	parent = NULL;
	left = NULL;
	right = NULL;
}

template <class T>
void BinarySearchTree<T>::InsertNode(BinarySearchNode <T> * z)
{
	BinarySearchNode <T> * x;
	BinarySearchNode <T> * y;

	y = NULL;
	x = root;

	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;

	if (y == NULL)
		root = z;				// tree was empty
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
}

template <class T>
void BinarySearchTree<T>::InsertElement(T key)
{
	BinarySearchNode <T> * nodeNew;

	nodeNew = new BinarySearchNode <T>;

	if (NULL == nodeNew)
	{
		cout << "Cannot allocate memory for a new BinarySearchNode" << endl;
		return;
	}

	nodeNew->key = key;

	InsertNode(nodeNew);
}

template <class T>
void BinarySearchTree<T>::InorderTreeWalk(void)
{
	root -> InorderTreeWalk();
	cout << endl;
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::KeySearch(T key)
{
	BinarySearchNode <T> * x;

	x = root;

	while (x != NULL && key != x->key)
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::MinimumNode(void)
{
	BinarySearchNode <T> * x;

	x = root;

	while (x->left != NULL)
		x = x->left;

	return x;
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::MaximumNode(void)
{
	BinarySearchNode <T> * x;

	x = root;

	while (x->right != NULL)
		x = x->right;

	return x;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(void)
{
	root = NULL;
}
