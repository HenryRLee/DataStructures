#pragma once
#include <vector>
#include <string>

using namespace std;

class PolyHash
{
	vector <int> vtext;
	vector <long long> vbase;
	vector <long long> vhash;
	int base;

	long long modulus;

	long long FastmodulusExp(long long base, long long exp, long long modulus);

public:
	void BuildHash(vector <int> v);
	void BuildHash(string s, int offset = 0);

	long long Hash(int i, int j);

	PolyHash(int base);
	PolyHash(void);
};

long long PolyHash::FastmodulusExp(long long base, long long exp, long long modulus)
{
	if (exp == 0)
	{
		return (1 % modulus);
	}
	else if (exp == 1)
	{
		return (base % modulus);
	}
	else
	{
		long long sub;
		long long ret;

		sub = FastmodulusExp(base, exp/2, modulus);

		if (exp % 2 == 0)
			ret = (sub * sub) % modulus;
		else
			ret = (sub * sub * base) % modulus;

		return ret;
	}
}

void PolyHash::BuildHash(vector <int> v)
{
	vtext = v;

	vbase.clear();
	vhash.clear();

	vbase.push_back(1);
	for (int i=1; i<=v.size(); i++)
	{
		vbase.push_back((vbase[i-1] * base) % modulus);
	}

	vhash.push_back(0);
	for (int i=1; i<=v.size(); i++)
	{
		vhash.push_back((vhash[i-1] + v[i-1] * vbase[i-1]) % modulus);
	}
}

void PolyHash::BuildHash(string s, int offset)
{
	vector <int> v;

	for (int i=0; i<s.length(); i++)
	{
		v.push_back(s[i]);
	}

	BuildHash(v);
}

long long PolyHash::Hash(int i, int j)
{
	if (i > j || j >= vhash.size()-1 || j >= vbase.size()-1 || i < 0)
	{
		return -1;
	}

	return ((vhash[j+1] - vhash[i]) * vbase[vbase.size() - 1 - j]) % modulus;
}

PolyHash::PolyHash(int base)
{
	this->base = base;

	modulus = 1e9 + 7;
}

PolyHash::PolyHash(void)
{
	base = 26;

	modulus = 1e9 + 7;
}
