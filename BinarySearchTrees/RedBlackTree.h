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

	RedBlackNode(void);
};

template <class T>
class RedBlackTree : public BinarySearchTree <T>
{
private:
	RedBlackNode <T> * nil;
	RedBlackNode <T> * root;

	void Transplant(RedBlackNode <T> * u, RedBlackNode <T> * v);

	void LeftRotate(RedBlackNode <T> * x);
	void RightRotate(RedBlackNode <T> * x);

	void InsertFixup(RedBlackNode <T> * z);
	void DeleteFixup(RedBlackNode <T> * x);
public:
	void InsertNode(RedBlackNode <T> * z);
	void InsertElement(T key);

	bool DeleteNode(RedBlackNode <T> * z);
	bool DeleteElement(T key);

	void InorderTreeWalk(void);

	RedBlackNode <T> * KeySearch(T key);
	RedBlackNode <T> * MinimumNode(void);
	RedBlackNode <T> * MaximumNode(void);

	void InorderTreeWalk(RedBlackNode <T> * x);

	RedBlackNode <T> * MinimumNode(RedBlackNode <T> * x);
	RedBlackNode <T> * MaximumNode(RedBlackNode <T> * x);

	RedBlackNode <T> * SuccessorNode(RedBlackNode <T> * x);
	RedBlackNode <T> * PredecessorNode(RedBlackNode <T> * x);

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
void RedBlackTree<T>::Transplant(RedBlackNode <T> * u, RedBlackNode <T> * v)
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
void RedBlackTree<T>::DeleteFixup(RedBlackNode <T> * x)
{
	while (x != root && x->color == BLACK)
	{
		RedBlackNode <T> * w;

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
bool RedBlackTree<T>::DeleteNode(RedBlackNode <T> * z)
{
	RedBlackNode <T> * x;
	RedBlackNode <T> * y;
	int ycolor;

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
		y = MinimumNode(z->right);
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

	return true;
}

template <class T>
bool RedBlackTree<T>::DeleteElement(T key)
{
	RedBlackNode <T> * z;

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
void RedBlackTree<T>::InorderTreeWalk(void)
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
RedBlackNode <T> * RedBlackTree<T>::KeySearch(T key)
{
	RedBlackNode <T> * x;

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
RedBlackNode <T> * RedBlackTree<T>::MinimumNode(void)
{
	return MinimumNode(root);
}

template <class T>
RedBlackNode <T> * RedBlackTree<T>::MaximumNode(void)
{
	return MaximumNode(root);
}

template <class T>
RedBlackNode <T> * RedBlackTree<T>::MinimumNode(RedBlackNode <T> * x)
{
	while (x->left != nil)
		x = x->left;

	return x;
}

template <class T>
RedBlackNode <T> * RedBlackTree<T>::MaximumNode(RedBlackNode <T> * x)
{
	while (x->right != nil)
		x = x->right;

	return x;
}

template <class T>
RedBlackNode <T> * RedBlackTree<T>::SuccessorNode(RedBlackNode <T> * x)
{
	RedBlackNode <T> * y;

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
RedBlackNode <T> * RedBlackTree<T>::PredecessorNode(RedBlackNode <T> * x)
{
	RedBlackNode <T> * y;

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
RedBlackTree<T>::RedBlackTree(void)
{
	nil = new RedBlackNode <T>;
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;

	root = nil;
}

template <class T>
RedBlackTree<T>::~RedBlackTree(void)
{
	delete nil;
}
