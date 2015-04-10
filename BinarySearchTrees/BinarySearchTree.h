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

	BinarySearchNode <T> * MinimumNode(void);
	BinarySearchNode <T> * MaximumNode(void);

	BinarySearchNode <T> * SuccessorNode(void);
	BinarySearchNode <T> * PredecessorNode(void);

	BinarySearchNode(void);
};

template <class T>
class BinarySearchTree
{
	BinarySearchNode <T> * root;

public:
	void InsertNode(BinarySearchNode <T> * z);
	void InsertElement(T key);

	void Transplant(BinarySearchNode <T> * u, BinarySearchNode <T> * v);

	bool DeleteNode(BinarySearchNode <T> * z);
	bool DeleteElement(T key);

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
BinarySearchNode <T> * BinarySearchNode<T>::MinimumNode(void)
{
	BinarySearchNode <T> * x;

	x = this;

	while (x->left != NULL)
		x = x->left;

	return x;
}

template <class T>
BinarySearchNode <T> * BinarySearchNode<T>::MaximumNode(void)
{
	BinarySearchNode <T> * x;

	x = this;

	while (x->right != NULL)
		x = x->right;

	return x;
}

template <class T>
BinarySearchNode <T> * BinarySearchNode<T>::SuccessorNode(void)
{
	BinarySearchNode <T> * x;
	BinarySearchNode <T> * y;

	if (this->right != NULL)
	{
		return this->right->MinimumNode();
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
		return this->left->MaximumNode();
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
		y = z->right->MinimumNode();
		
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
	return root->MinimumNode();
}

template <class T>
BinarySearchNode <T> * BinarySearchTree<T>::MaximumNode(void)
{
	return root->MaximumNode();
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(void)
{
	root = NULL;
}
