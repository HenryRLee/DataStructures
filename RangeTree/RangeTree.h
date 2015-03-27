#include <iostream>
#include <vector>

using namespace std;

template <class T>
class RangeTree
{
	vector < vector <T> > tree;

	bool bUseMax;

	T Compare(T a, T b);

public:
	RangeTree(void);
	RangeTree(bool usemax);
	RangeTree(vector <T> block, bool usemax = false);
	RangeTree(vector <T> block, int start, int end, bool usemax = false);

	int SetCompareValue(bool usemax);

	int BuildRangeTree(vector <T> block);
	int BuildRangeTree(vector <T> block, int start, int end);
	int CleanTree(void);

	int SearchRangeTree(int start, int end);
	int PrintRangeTree(void);
};

template <class T>
RangeTree<T>::RangeTree(void)
{
	bUseMax = false;
}

template <class T>
RangeTree<T>::RangeTree(bool usemax)
{
	bUseMax = usemax;
}

template <class T>
RangeTree<T>::RangeTree(vector <T> block, int start, int end, bool usemax)
{
	BuildRangeTree(block, start, end);
}

template <class T>
RangeTree<T>::RangeTree(vector <T> block, bool usemax)
{
	BuildRangeTree(block);
}

template <class T>
T RangeTree<T>::Compare(T a, T b)
{
	if (bUseMax)
		return (a > b ? a : b);
	else
		return (a < b ? a : b);
}

template <class T>
int RangeTree<T>::BuildRangeTree(vector <T> block)
{
	return BuildRangeTree(block, 0, block.size()-1);
}

template <class T>
int RangeTree<T>::SetCompareValue(bool usemax)
{
	bUseMax = usemax;

	return 0;
}

template <class T>
int RangeTree<T>::BuildRangeTree(vector <T> block, int start, int end)
{
	if ((start < 0) || (start >= block.size()) || (end < 0) ||
			(end >= block.size()) || (end < start))
		return 1;

	CleanTree();

	tree.push_back(block);

	for (int depth=1, interval=(1 << depth); interval<(end-start+1)*2; interval*=2, depth++)
	{
		vector <T> newlayer;
		for (int i=0; i<tree[depth-1].size(); i+=2)
		{
			int data;

			if (i == tree[depth-1].size() - 1)
				data = tree[depth-1][i];
			else
				data = Compare(tree[depth-1][i], tree[depth-1][i+1]);

			newlayer.push_back(data);
		}
		tree.push_back(newlayer);
	}

	return 0;
}

template <class T>
int RangeTree<T>::CleanTree(void)
{
	for (int i=0; i<tree.size(); i++)
	{
		tree[i].clear();
	}
	tree.clear();
	return 0;
}

template <class T>
int RangeTree<T>::PrintRangeTree(void)
{
	for (int i=0; i<tree.size(); i++)
	{
		for (int j=0; j<tree[i].size(); j++)
		{
			cout << tree[i][j] << " ";
			for (int k=0; k<i; k++)
			{
				cout << "  ";
			}
		}
		cout << endl;
	}

	return 0;
}

template <class T>
int RangeTree<T>::SearchRangeTree(int start, int end)
{
	int depth;
	int idx;
	int next;
	int first;
	int second;
	int interval;

	if ((tree.size() == 0) || (start < 0) || (start >= tree[0].size()) ||
			(end < 0) || (end >= tree[0].size()) || (end < start))
	{
		return 0;
	}

	interval = end - start + 1;
	depth = 0;

	for (int i=0; (i<tree.size()-1) && ((1 << i) <= interval); i++)
	{
		if ((start % (1 << i)) != 0)
		{
			break;
		}
		depth = i;
	}

	idx = start/(1 << depth);

	first = tree[depth][idx];

	if (interval > (1 << depth))
	{
		second = SearchRangeTree(start + (1 << depth), end);
		return Compare(first, second);
	}
	else
	{
		return first;
	}
}
