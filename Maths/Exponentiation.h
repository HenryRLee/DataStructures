#include <vector>

using namespace std;

unsigned long long FastModExp(unsigned long long base, unsigned long long exp,
		unsigned long long mod)
{
	if (exp == 0)
	{
		return (1 % mod);
	}
	else if (exp == 1)
	{
		return (base % mod);
	}
	else
	{
		unsigned long long sub;
		unsigned long long ret;

		sub = FastModExp(base, exp/2, mod);

		if (exp % 2 == 0)
			ret = (sub * sub) % mod;
		else
			ret = (sub * sub * base) % mod;

		return ret;
	}
}
