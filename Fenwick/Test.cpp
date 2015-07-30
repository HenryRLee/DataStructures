#include "Fenwick.h"
#include <iostream>

int main(void)
{
	Fenwick <int> fenwick;
	int a[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
	int idx;

	fenwick.Resize(sizeof(a)/sizeof(int));

	for (int i=0; i<sizeof(a)/sizeof(int); i++)
	{
		fenwick.Update(i+1, a[i]);
	}

	for (int i=0; i<sizeof(a)/sizeof(int); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;

	while (cin >> idx)
	{
		cout << fenwick.GetSum(idx) << endl;
	}

	return 0;
}
