#pragma once
#include "BinarySearchTree.h"

enum color
{
	RED,
	BLACK
};

template <class T>
class RedBlackNode : public BinarySearchNode <T>
{
public:
	int color;

	RedBlackNode <T> * left;
	RedBlackNode <T> * right;
	RedBlackNode <T> * parent;

	/*
	RedBlackNode <T> * MinimumNode(void);
	RedBlackNode <T> * MaximumNode(void);

	RedBlackNode <T> * SuccessorNode(void);
	RedBlackNode <T> * PredecessorNode(void);
	*/

	RedBlackNode(void);
};

template <class T>
class RedBlackTree : public BinarySearchTree <T>
{
private:
	RedBlackNode <T> * nil;
	RedBlackNode <T> * root;

	void LeftRotate(RedBlackNode <T> * x);
	void RightRotate(RedBlackNode <T> * x);
public:
	void InsertFixup(RedBlackNode <T> * z);
	void InsertNode(RedBlackNode <T> * z);
	void InsertElement(T key);

	void Transplant(RedBlackNode <T> * u, RedBlackNode <T> * v);

	bool DeleteNode(RedBlackNode <T> * z);
	bool DeleteElement(T key);

	void InorderTreeWalk(void);

	RedBlackNode <T> * KeySearch(T key);
	RedBlackNode <T> * MinimumNode(void);
	RedBlackNode <T> * MaximumNode(void);

	void InorderTreeWalk(RedBlackNode <T> * x);


	RedBlackTree(void);
	~RedBlackTree(void);
};

template <class T>
RedBlackNode<T>::RedBlackNode(void)
{
	color = BLACK;
	left = NULL;
	right = NULL;
	parent = NULL;
}

template <class T>
void RedBlackTree<T>::LeftRotate(RedBlackNode <T> * x)
{
	RedBlackNode <T> * y;

	y = x->right;

	x->right = y->left;
	if (y->left != nil)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == nil)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

template <class T>
void RedBlackTree<T>::RightRotate(RedBlackNode <T> * x)
{
	RedBlackNode <T> * y;

	y = x->left;

	x->left = y->right;
	if (y->right != nil)
		y->right->parent = x;

	y->parent = x->parent;
	if (x->parent == nil)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;

	y->right = x;
	x->parent = y;
}

template <class T>
void RedBlackTree<T>::InsertFixup(RedBlackNode <T> * z)
{
	while (z->parent->color == RED)
	{
		RedBlackNode <T> * y;

		if (z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;

			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->right)
				{
					z = z->parent;
					LeftRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;

				RightRotate(z->parent->parent);
			}
		}
		else
		{
			y = z->parent->parent->left;

			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->left)
				{
					z = z->parent;
					RightRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;

				LeftRotate(z->parent->parent);
			}
		}
	}

	root->color = BLACK;
}

template <class T>
void RedBlackTree<T>::InsertNode(RedBlackNode <T> * z)
{
	RedBlackNode <T> * x;
	RedBlackNode <T> * y;

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
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;

	z->left = nil;
	z->right = nil;
	z->color = RED;

	InsertFixup(z);
}

template <class T>
void RedBlackTree<T>::InsertElement(T key)
{
	RedBlackNode <T> * z;

	z = new RedBlackNode <T>;

	if (NULL == z)
	{
		cout << "Cannot allocate memory for a new RedBlackNode" << endl;
		return;
	}

	z->key = key;

	InsertNode(z);
}

template <class T>
void RedBlackTree<T>::InorderTreeWalk(void)
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
void RedBlackTree<T>::InorderTreeWalk(RedBlackNode <T> * x)
{
	if (x == nil)
		return;

	if (x->left != nil)
		InorderTreeWalk(x->left);

	x->PrintKey();

	if (x->right != nil)
		InorderTreeWalk(x->right);
}

template <class T>
RedBlackTree<T>::RedBlackTree(void)
{
	nil = new RedBlackNode <T>;
	root = nil;
}

template <class T>
RedBlackTree<T>::~RedBlackTree(void)
{
	delete nil;
}
