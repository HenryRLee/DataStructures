#pragma once
#include <vector>
#include <string>

using namespace std;

class Trie
{
	struct TrieNode
	{
		int wcount;		//word count
		int pcount;		//prefix count

		vector <TrieNode *> next;

		TrieNode(int n)
		{
			wcount = 0;
			pcount = 0;
			next.resize(n);
		}
	};

	int size;
	int nchar;

	TrieNode * NewNode(void)
	{
		TrieNode * node = new TrieNode(nchar);
		size++;

		return node;
	}

	TrieNode * root;

public:
	void Insert(vector <int> v);
	void Insert(string s, int offset = 0);

	int CountPrefix(vector <int> v);
	int CountWord(vector <int> v);

	int CountPrefix(string s, int offset = 0);
	int CountWord(string s, int offset = 0);

	void Init(void);
	
	Trie(void);
	Trie(int nchar);
};

void Trie::Insert(vector <int> v)
{
	TrieNode * p = root;

	for (int i=0; i<v.size(); i++)
	{
		int s = v[i];
		TrieNode * next;

		/* Out of range */
		if (s >= p->next.size())
			return;

		next = p->next[s];

		if (next == NULL)
		{
			p->next[s] = NewNode();
		}

		p->pcount++;

		p = p->next[s];
	}

	p->wcount++;
	p->pcount++;
}

void Trie::Insert(string s, int offset)
{
	vector <int> v;

	for (int i=0; i<s.length(); i++)
	{
		v.push_back(s[i] - offset);
	}

	Insert(v);
}

int Trie::CountPrefix(vector <int> v)
{
	TrieNode * p = root;

	for (int i=0; i<v.size(); i++)
	{
		int s = v[i];

		if (p == NULL)
		{
			return 0;
		}
		else
		{
			p = p->next[s];
		}
	}

	return p->pcount;
}

int Trie::CountWord(vector <int> v)
{
	TrieNode * p = root;

	for (int i=0; i<v.size(); i++)
	{
		int s = v[i];

		if (p == NULL)
		{
			return 0;
		}
		else
		{
			p = p->next[s];
		}
	}

	return p->wcount;
}

int Trie::CountPrefix(string s, int offset)
{
	vector <int> v;

	for (int i=0; i<s.length(); i++)
	{
		v.push_back(s[i]);
	}

	return CountPrefix(v);
}

int Trie::CountWord(string s, int offset)
{
	vector <int> v;

	for (int i=0; i<s.length(); i++)
	{
		v.push_back(s[i]);
	}

	return CountWord(v);
}

void Trie::Init(void)
{
	root = new TrieNode(nchar);

	size = 0;
}

Trie::Trie(void)
{
	nchar = 128;

	Init();
}

Trie::Trie(int nchar)
{
	this->nchar = nchar;

	Init();
}

