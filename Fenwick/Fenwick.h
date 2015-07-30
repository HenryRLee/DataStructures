#pragma once
#include <vector>

using namespace std;

template <class T>
class Fenwick
{
	vector <T> arr;
	vector <T> tree;
public:
	T GetSum(int idx);
	void UpdateDiff(int idx, T diff);
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

	if (idx >= GetSize() || idx < 0)
		return -1;

	idx++;

	while (idx > 0)
	{
		sum += tree[idx-1];
		idx = idx - (idx & (-idx));
	}

	return sum;
}

template <class T>
void Fenwick<T>::UpdateDiff(int idx, T diff)
{
	if (idx >= GetSize() || idx < 0)
		return;

	tree[idx] += diff;

	idx++;
	idx = idx + (idx & (-idx));
	idx--;

	UpdateDiff(idx, diff);
}

template <class T>
void Fenwick<T>::Update(int idx, T value)
{
	T diff; 

	if (idx >= GetSize() || idx < 0)
		return;

	diff = value - arr[idx];

	arr[idx] = value;

	UpdateDiff(idx, diff);
}

template <class T>
void Fenwick<T>::Resize(int size)
{
	tree.resize(size);
	arr.resize(size);
}

template <class T>
int Fenwick<T>::GetSize(void)
{
	return tree.size();
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

