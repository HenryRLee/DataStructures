#pragma once
#include <vector>

using namespace std;

/*
 * Different from the binary_search in <algorithm>, this one does not only
 * return true or false after the search, but also tells us where the search
 * ends. Requires the vector sorted before this function is used, otherwise the
 * result is not reliable.
 */
template <typename T>
pair <bool, T> binarysearch(vector <T> block, int start, int end, int value,
		bool rightprior = true)
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

	if (rightprior)
		mid = (end + start)/2;
	else
		mid = (end + start + 1)/2;

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
			if (rightprior)
				return binarysearch(block, start, mid, value, rightprior);
			else
				return binarysearch(block, start, mid-1, value, rightprior);
		}
		else
		{
			if (rightprior)
				return binarysearch(block, mid+1, end, value, rightprior);
			else
				return binarysearch(block, mid, end, value, rightprior);
		}
	}
}

