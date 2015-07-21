#include "Trie.h"
#include <iostream>

using namespace std;

int main(void)
{
	string s;
	Trie trie;

	trie.Insert("abcde");

	cout << trie.CountPrefix("abc") << endl;
	cout << trie.CountWord("abc") << endl;

	trie.Insert("abc");

	cout << trie.CountPrefix("abc") << endl;
	cout << trie.CountWord("abc") << endl;
}
