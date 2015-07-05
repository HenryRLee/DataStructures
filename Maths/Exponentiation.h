#include <vector>

using namespace std;

unsigned long long FastModExp(unsigned long long exp, unsigned long long mod)
{
	if (exp == 0)
	{
		return (1 % mod);
	}
	else if (exp == 1)
	{
		return (2 % mod);
	}
	else
	{
		unsigned long long sub;
		unsigned long long ret;

		sub = FastModExp(exp/2, mod);

		ret = (sub * sub * (1 << (exp % 2))) % mod;

		return ret;
	}
}
