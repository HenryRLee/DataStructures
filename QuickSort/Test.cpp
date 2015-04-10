#include <iostream>
#include "QuickSort.h"

int main(void)
{
	int myints[] = {1, 3, 9, 7, 3, 40, 7, 10, 169, 13, 151};

	vector <int> block(myints, myints+sizeof(myints)/sizeof(int));

	block = quicksort(block, false);

	for (int i=0; i<block.size(); i++)
	{
		cout << block[i] << endl;
	}

	return 0;
}
