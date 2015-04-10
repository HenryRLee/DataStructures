#pragma once
#include <iostream>

using namespace std;

template <class T> class BinarySearchNode;
template <class T> class BinarySearchTree;

template <class T>
class BinarySearchNode
{
protected:
	T key;

	BinarySearchNode <T> * left;
	BinarySearchNode <T> * right;
	BinarySearchNode <T> * parent;

public:
	void PrintKey(void);

	BinarySearchNode(void);

	friend class BinarySearchTree <T>;
};

template <class T>
class BinarySearchTree
{
protected:
	BinarySearchNode <T> * root;

	void Transplant(BinarySearchNode <T> * u, BinarySearchNode <T> * v);
public:
	void InsertNode(BinarySearchNode <T> * z);
	void InsertElement(T key);

	bool DeleteNode(BinarySearchNode <T> * z);
	bool DeleteElement(T key);

	void InorderTreeWalk(void);

	BinarySearchNode <T> * KeySearch(T key);
	BinarySearchNode <T> * MinimumNode(void);
	BinarySearchNode <T> * MaximumNode(void);

	void InorderTreeWalk(BinarySearchNode <T> * x);

	BinarySearchNode <T> * MinimumNode(BinarySearchNode <T> * x);
	BinarySearchNode <T> * MaximumNode(BinarySearchNode <T> * x);

	BinarySearchNode <T> * SuccessorNode(BinarySearchNode <T> * x);
	BinarySearchNode <T> * PredecessorNode(BinarySearchNode <T> * x);

	BinarySearchTree(void);
};

template <class T>
void BinarySearchNode<T>::PrintKey(void)
{
	cout << key << " ";
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
	BinarySearchNode <T> * z;

	z = new BinarySearchNode <T>;

	if (NULL == z)
	{
		cout << "Cannot allocate memory for a new BinarySearchNode" << endl;
		return;
	}

	z->key = key;

	InsertNode(z);
}

template <class T>
void BinarySearchTree<T>::Transplant(BinarySearchNode <T> * u, BinarySearchNode <T> * v)
{
	if (NULL == u->parent)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if (v != NULL)
		v->parent = u->parent;
}

template <class T>
bool BinarySearchTree<T>::DeleteNode(BinarySearchNode <T> * z)
{
	if (NULL == z)
		return false;

	if (NULL == z->left)
	{
		Transplant(z, z->right);
	}
	else if (NULL == z->right)
	{
		Transplant(z, z->left);
	}
	else
	{
		BinarySearchNode <T> * y;
		y = MinimumNode(z->right);
		
		if (y->parent != z)
		{
			Transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		Transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
	}
	delete z;

	return true;
}

template <class T>
bool BinarySearchTree<T>::DeleteElement(T key)
{
	BinarySearchNode <T> * z;

	z = KeySearch(key);

	if (z != NULL)
	{
		DeleteNode(z);
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
void BinarySearchTree<T>::InorderTreeWalk(void)
{
	if (root != NULL)
	{
		InorderTreeWalk(root);
		cout << endl;
	}
	else
	{
		cout << "Tree is empty" << endl;
	}
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
	return MinimumNode(root);
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::MaximumNode(void)
{
	return MaximumNode(root);
}

template <class T>
void BinarySearchTree<T>::InorderTreeWalk(BinarySearchNode <T> * x)
{
	if (NULL == x)
		return;

	if (x->left != NULL)
		InorderTreeWalk(x->left);

	x->PrintKey();

	if (x->right != NULL)
		InorderTreeWalk(x->right);
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::MinimumNode(BinarySearchNode <T> * x)
{
	while (x->left != NULL)
		x = x->left;

	return x;
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::MaximumNode(BinarySearchNode <T> * x)
{
	while (x->right != NULL)
		x = x->right;

	return x;
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::SuccessorNode(BinarySearchNode <T> * x)
{
	BinarySearchNode <T> * y;

	if (x->right != NULL)
	{
		return MinimumNode(x->right);
	}
	else
	{
		y = x->parent;

		while (y != NULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}

		return y;
	}
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::PredecessorNode(BinarySearchNode <T> * x)
{
	BinarySearchNode <T> * y;

	if (x->left != NULL)
	{
		return MaximumNode(x->left);
	}
	else
	{
		y = x->parent;

		while (y != NULL && x == y->left)
		{
			x = y;
			y = y->parent;
		}

		return y;
	}
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(void)
{
	root = NULL;
}
