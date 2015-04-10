#include <iostream>
#include "RangeSearchVector.h"

using namespace std;

int main(int argc, char *argv[])
{
	int test[] = {0,1,2,3,4,5,6,7,8};

	vector <int> testvector(test, test + sizeof(test)/sizeof(int));

	RangeSearchVector <int> RangeSearchVector(true);

	RangeSearchVector.BuildRangeSearchVector(testvector, 0, testvector.size()-1);

	while (1)
	{
		int start, end;
		cin >> start >> end;
		cout << RangeSearchVector.SearchRangeSearchVector(start, end) << endl;
	}
	
	return 0;
}
