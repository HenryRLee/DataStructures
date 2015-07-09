#include <iostream>
#include "RangeSearchVector.h"

using namespace std;

int main(int argc, char *argv[])
{
	int test[] = {0,7,2,5,0,2,1,7,8,4};
	int start, end;

	vector <int> testvector(test, test + sizeof(test)/sizeof(int));

	RangeSearchVector <int> RangeSearchVector(true);

	RangeSearchVector.BuildRangeSearchVector(testvector, 0, testvector.size()-1);

	while (cin >> start >> end)
	{
		cout << RangeSearchVector.SearchRangeSearchVector(start, end) << endl;
	}
	
	return 0;
}
