#pragma once
#include <iostream>

using namespace std;

template <class T> class BinarySearchNode;
template <class T> class BinarySearchTree;
template <class T> class RedBlackTree;

template <class T>
class BinarySearchNode
{
protected:
	T key;

	int color;

	BinarySearchNode <T> * left;
	BinarySearchNode <T> * right;
	BinarySearchNode <T> * parent;

public:
	void PrintKey(void);

	T ReturnKey(void);

	BinarySearchNode(void);

	friend class BinarySearchTree <T>;
	friend class RedBlackTree <T>;
};

template <class T>
class BinarySearchTree
{
protected:
	BinarySearchNode <T> * root;
	BinarySearchNode <T> * nil;

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
T BinarySearchNode<T>::ReturnKey(void)
{
	return key;
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

	y = nil;
	x = root;

	while (x != nil)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;

	if (y == nil)
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
	if (nil == u->parent)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if (v != nil)
		v->parent = u->parent;
}

template <class T>
bool BinarySearchTree<T>::DeleteNode(BinarySearchNode <T> * z)
{
	if (nil == z)
		return false;

	if (nil == z->left)
	{
		Transplant(z, z->right);
	}
	else if (nil == z->right)
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

	if (z != nil)
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
	if (root != nil)
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

	while (x != nil && key != x->key)
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
	if (nil == x)
		return;

	if (x->left != nil)
		InorderTreeWalk(x->left);

	x->PrintKey();

	if (x->right != nil)
		InorderTreeWalk(x->right);
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::MinimumNode(BinarySearchNode <T> * x)
{
	if (x != nil)
	{
		while (x->left != nil)
			x = x->left;
	}

	return x;
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::MaximumNode(BinarySearchNode <T> * x)
{
	if (x != nil)
	{
		while (x->right != nil)
			x = x->right;
	}

	return x;
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::SuccessorNode(BinarySearchNode <T> * x)
{
	BinarySearchNode <T> * y;

	if (nil == x)
		return nil;

	if (x->right != nil)
	{
		return MinimumNode(x->right);
	}
	else
	{
		y = x->parent;

		while (y != nil && x == y->right)
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

	if (nil == x)
		return nil;

	if (x->left != nil)
	{
		return MaximumNode(x->left);
	}
	else
	{
		y = x->parent;

		while (y != nil && x == y->left)
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
	nil = NULL;
}
