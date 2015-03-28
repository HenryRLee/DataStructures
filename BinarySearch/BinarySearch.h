#include <vector>
#include <iterator>

using namespace std;

template <typename T>
pair <bool, T> binarysearch(vector <T> block, int start, int end, int value)
{
	int mid;
	pair <bool, T> ret;

	if ((start < 0) || (start >= block.size()) || (end < 0) ||
			(end >= block.size()))
	{
		ret.first = false;
		ret.second = 0;

		return ret;
	}

	mid = (end + start)/2;

	if (block[mid] == value)
	{
		ret.first = true;
		ret.second = mid;
		return ret;
	}
	else
	{
		if (start == end)
		{
			ret.first = false;
			ret.second = start;
			return ret;
		}

		if (value < block[mid])
		{
			return binarysearch(block, start, mid, value);
		}
		else
		{
			return binarysearch(block, mid+1, end, value);
		}
	}
}

