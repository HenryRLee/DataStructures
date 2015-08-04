#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class BigNumber
{
	int base;
	vector <int> bits;

public:
	void InputNumber(string input);

	string OutputNumber(void);

	friend ostream& operator << (ostream& os, BigNumber bg);
	friend istream& operator >> (istream& is, BigNumber& bg);
	
	friend BigNumber operator + (BigNumber lhs, BigNumber& rhs)
	{
		BigNumber sum;
		int base = lhs.base;
		vector <int> vs;
		vector <int> vb;
		int c = 0;

		if (lhs.bits.size() >= rhs.bits.size())
		{
			vb = lhs.bits;
			vs = rhs.bits;
		}
		else
		{
			vb = rhs.bits;
			vs = lhs.bits;
		}

		sum.base = base;

		for (int i=0; i<vs.size(); i++)
		{
			int s = vs[vs.size()-1-i] + vb[vb.size()-1-i] + c;

			if (s >= base)
				c = 1;
			else
				c = 0;

			sum.bits.push_back(s % base);
		}

		for (int i=vs.size(); i<vb.size(); i++)
		{
			int s = vb[vb.size()-1-i] + c;

			if (s >= base)
				c = 1;
			else
				c = 0;

			sum.bits.push_back(s % base);
		}

		if (c > 0)
			sum.bits.push_back(1);

		reverse(sum.bits.begin(), sum.bits.end());

		return sum;
	}

	BigNumber(int base = 10);
	BigNumber(string input, int base = 10);
};

void BigNumber::InputNumber(string input)
{
	for (int i=0; i<input.length(); i++)
	{
		bits.push_back(input[i] - '0');
	}
}

string BigNumber::OutputNumber(void)
{
	string output;

	for (int i=0; i<bits.size(); i++)
	{
		output.push_back('0' + bits[i]);
	}

	return output;
}

ostream& operator << (ostream& os, BigNumber bg)
{
	os << bg.OutputNumber();
	return os;
}

istream& operator >> (istream& is, BigNumber& bg)
{
	string input;
	is >> input;

	bg.InputNumber(input);

	return is;
}

BigNumber::BigNumber(int base)
{
	this->base = base;
}

BigNumber::BigNumber(string input, int base)
{
	this->base = base;

	InputNumber(input);
}
