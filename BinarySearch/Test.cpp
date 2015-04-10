#include <iostream>
#include "BinarySearch.h"

using namespace std;

int main(void)
{
	int tuple[] = {0, 3, 6, 9, 12, 15};
	vector <int> test(tuple, tuple+sizeof(tuple)/sizeof(int));
	int input;

	pair <bool, int> data;

	while (1)
	{
		cin >> input;
		data = binarysearch(test, 0, test.size()-1, input, false);

		cout << data.first << " " << data.second << endl;
	}
	return 0;
}
