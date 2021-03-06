#pragma once
#include <vector>

using namespace std;

template <class T>
class RangeSearchVector
{
	vector < vector <T> > layers;

	bool bUseMax;

	virtual T Function(T a, T b);

public:
	RangeSearchVector(void);
	RangeSearchVector(bool usemax);
	RangeSearchVector(vector <T> block, bool usemax = false);
	RangeSearchVector(vector <T> block, int start, int end, bool usemax = false);

	int SetCompareType(bool usemax);

	int BuildRangeSearchVector(vector <T> block);
	int BuildRangeSearchVector(vector <T> block, int start, int end);
	int CleanLayers(void);

	T SearchRangeSearchVector(int start, int end);
	int PrintRangeSearchVector(void);
};

template <class T>
RangeSearchVector<T>::RangeSearchVector(void)
{
	bUseMax = false;
}

template <class T>
RangeSearchVector<T>::RangeSearchVector(bool usemax)
{
	bUseMax = usemax;
}

template <class T>
RangeSearchVector<T>::RangeSearchVector(vector <T> block, int start, int end, bool usemax)
{
	BuildRangeSearchVector(block, start, end);
}

template <class T>
RangeSearchVector<T>::RangeSearchVector(vector <T> block, bool usemax)
{
	BuildRangeSearchVector(block);
}

template <class T>
T RangeSearchVector<T>::Function(T a, T b)
{
	if (bUseMax)
		return (a > b ? a : b);
	else
		return (a < b ? a : b);
}

template <class T>
int RangeSearchVector<T>::BuildRangeSearchVector(vector <T> block)
{
	return BuildRangeSearchVector(block, 0, block.size()-1);
}

template <class T>
int RangeSearchVector<T>::SetCompareType(bool usemax)
{
	bUseMax = usemax;

	return 0;
}

template <class T>
int RangeSearchVector<T>::BuildRangeSearchVector(vector <T> block, int start,
		int end)
{
	if ((start < 0) || (start >= block.size()) || (end < 0) ||
			(end >= block.size()) || (end < start))
		return 1;

	CleanLayers();

	layers.push_back(block);

	for (int depth=1, interval=(1 << depth); interval<(end-start+1)*2; interval*=2, depth++)
	{
		vector <T> newlayer;
		for (int i=0; i<layers[depth-1].size(); i+=2)
		{
			T data;

			if (i == layers[depth-1].size() - 1)
				data = layers[depth-1][i];
			else
				data = Function(layers[depth-1][i], layers[depth-1][i+1]);

			newlayer.push_back(data);
		}
		layers.push_back(newlayer);
	}

	return 0;
}

template <class T>
int RangeSearchVector<T>::CleanLayers(void)
{
	for (int i=0; i<layers.size(); i++)
	{
		layers[i].clear();
	}
	layers.clear();
	return 0;
}

template <class T>
T RangeSearchVector<T>::SearchRangeSearchVector(int start, int end)
{
	int depth;
	int idx;
	int next;
	T first;
	T second;
	int interval;
	T ret;

	if ((layers.size() == 0) || (start < 0) || (start >= layers[0].size()) ||
			(end < 0) || (end >= layers[0].size()) || (end < start))
	{
		return ret;
	}

	interval = end - start + 1;
	depth = 0;

	for (int i=0; (i<layers.size()-1) && ((1 << i) <= interval); i++)
	{
		if ((start % (1 << i)) != 0)
		{
			break;
		}
		depth = i;
	}

	idx = start/(1 << depth);

	first = layers[depth][idx];

	if (interval > (1 << depth))
	{
		second = SearchRangeSearchVector(start + (1 << depth), end);
		return Function(first, second);
	}
	else
	{
		return first;
	}
}

template <class T>
int RangeSearchVector<T>::PrintRangeSearchVector(void)
{
	for (int i=0; i<layers.size(); i++)
	{
		for (int j=0; j<layers[i].size(); j++)
		{
			cout << layers[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	return 0;
}
