#include <vector>

using namespace std;

template <typename T>
vector <T> quicksort(vector <T> block, bool ascend = true)
{
	vector <T> left;
	vector <T> right;
	vector <T> sorted;
	T pivot;

	if (block.size() == 1 || block.size() == 0)
		return block;

	pivot = block[0];

	for (int i=1; i<block.size(); i++)
	{
		if (ascend ^ (block[i] > pivot))
			left.push_back(block[i]);
		else
			right.push_back(block[i]);
	}

	left = quicksort(left, ascend);
	right = quicksort(right, ascend);

	for (int i=0; i<left.size(); i++)
		sorted.push_back(left[i]);

	sorted.push_back(pivot);

	for (int i=0; i<right.size(); i++)
		sorted.push_back(right[i]);

	return sorted;
}
