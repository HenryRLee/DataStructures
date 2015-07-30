#pragma once
#include <vector>

using namespace std;

template <class T>
class Fenwick
{
	vector <T> arr;
	vector <T> tree;
	void UpdateDiff(int idx, T diff);
public:
	T GetSum(int idx);
	void Update(int idx, T value);

	void Resize(int size);
	int GetSize(void);

	Fenwick(void);
	Fenwick(int size);
};

template <class T>
T Fenwick<T>::GetSum(int idx)
{
	T sum;

	sum = 0;

	if (idx > GetSize() || idx <= 0)
		return -1;

	while (idx > 0)
	{
		sum += tree[idx];
		idx = idx - (idx & (-idx));
	}

	return sum;
}

template <class T>
void Fenwick<T>::UpdateDiff(int idx, T diff)
{
	if (idx > GetSize() || idx <= 0)
		return;

	tree[idx] += diff;

	UpdateDiff(idx + (idx & (-idx)), diff);
}

template <class T>
void Fenwick<T>::Update(int idx, T value)
{
	T diff; 

	if (idx > GetSize() || idx <= 0)
		return;

	diff = value - arr[idx];

	arr[idx] = value;

	UpdateDiff(idx, diff);
}

template <class T>
void Fenwick<T>::Resize(int size)
{
	tree.resize(size + 1);
	arr.resize(size + 1);
}

template <class T>
int Fenwick<T>::GetSize(void)
{
	return tree.size() - 1;
}

template <class T>
Fenwick<T>::Fenwick(void)
{
}

template <class T>
Fenwick<T>::Fenwick(int size)
{
	Resize(size);
}

