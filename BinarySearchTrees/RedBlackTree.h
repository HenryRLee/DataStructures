#pragma once
#include "BinarySearchTree.h"

enum color
{
	RED,
	BLACK
};

template <class T>
class RedBlackTree : public BinarySearchTree <T>
{
	using BinarySearchTree <T>::root;
	using BinarySearchTree <T>::nil;
private:
	void Transplant(BinarySearchNode <T> * u, BinarySearchNode <T> * v);

	void LeftRotate(BinarySearchNode <T> * x);
	void RightRotate(BinarySearchNode <T> * x);

	void InsertFixup(BinarySearchNode <T> * z);
	void DeleteFixup(BinarySearchNode <T> * x);
public:
	void InsertNode(BinarySearchNode <T> * z);
	void InsertElement(T key);

	bool DeleteNode(BinarySearchNode <T> * z);
	bool DeleteElement(T key);

	RedBlackTree(void);
	~RedBlackTree(void);
};

template <class T>
void RedBlackTree<T>::Transplant(BinarySearchNode <T> * u, BinarySearchNode <T> * v)
{
	if (u->parent == nil)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	v->parent = u->parent;
}

template <class T>
void RedBlackTree<T>::LeftRotate(BinarySearchNode <T> * x)
{
	BinarySearchNode <T> * y;

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
void RedBlackTree<T>::RightRotate(BinarySearchNode <T> * x)
{
	BinarySearchNode <T> * y;

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
void RedBlackTree<T>::InsertFixup(BinarySearchNode <T> * z)
{
	while (z->parent->color == RED)
	{
		BinarySearchNode <T> * y;

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
void RedBlackTree<T>::InsertNode(BinarySearchNode <T> * z)
{
	BinarySearchTree <T>::InsertNode(z);

	z->left = nil;
	z->right = nil;
	z->color = RED;

	InsertFixup(z);
}

template <class T>
void RedBlackTree<T>::InsertElement(T key)
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
void RedBlackTree<T>::DeleteFixup(BinarySearchNode <T> * x)
{
	while (x != root && x->color == BLACK)
	{
		BinarySearchNode <T> * w;

		if (x == x->parent->left)
		{
			w = x->parent->right;
			
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;

				LeftRotate(x->parent);
				w = x->parent->right;
			}

			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;

					RightRotate(w);
					w = x->parent->right;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;

				LeftRotate(x->parent);
				x = root;
			}
		}
		else
		{
			w = x->parent->left;
			
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;

				RightRotate(x->parent);
				w = x->parent->left;
			}

			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;

					LeftRotate(w);
					w = x->parent->left;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;

				RightRotate(x->parent);
				x = root;
			}
		}
	}

	x->color = BLACK;
}

template <class T>
bool RedBlackTree<T>::DeleteNode(BinarySearchNode <T> * z)
{
	BinarySearchNode <T> * x;
	BinarySearchNode <T> * y;
	int ycolor;

	if (z == nil)
		return false;

	y = z;
	ycolor = y->color;

	if (z->left == nil)
	{
		x = z->right;
		Transplant(z, z->right);
	}
	else if (z->right == nil)
	{
		x = z->left;
		Transplant(z, z->left);
	}
	else
	{
		y = BinarySearchTree <T>::MinimumNode(z->right);
		ycolor = y->color;
		x = y->right;
		
		if (y->parent == z)
		{
			x->parent = y;
		}
		else
		{
			Transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		Transplant(z, y);

		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if (ycolor == BLACK)
		DeleteFixup(x);

	delete z;

	return true;
}

template <class T>
bool RedBlackTree<T>::DeleteElement(T key)
{
	BinarySearchNode <T> * z;

	z = BinarySearchTree <T>::KeySearch(key);

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
RedBlackTree<T>::RedBlackTree(void)
{
	nil = new BinarySearchNode <T>;
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
	nil->color = BLACK;

	root = nil;
}

template <class T>
RedBlackTree<T>::~RedBlackTree(void)
{
	delete nil;
}
