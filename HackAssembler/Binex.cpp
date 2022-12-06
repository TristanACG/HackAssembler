#include "Binex.h"

Binex::Binex()
{
	binex.insert(pair<string, char>("0000", '0'));
	binex.insert(pair<string, char>("0001", '1'));
	binex.insert(pair<string, char>("0010", '2'));
	binex.insert(pair<string, char>("0011", '3"'));
	binex.insert(pair<string, char>("0100", '4'));
	binex.insert(pair<string, char>("0101", '5'));
	binex.insert(pair<string, char>("0110", '6'));
	binex.insert(pair<string, char>("0111", '7'));
	binex.insert(pair<string, char>("1000", '8'));
	binex.insert(pair<string, char>("1001", '9'));
	binex.insert(pair<string, char>("1010", 'A'));
	binex.insert(pair<string, char>("1011", 'B'));
	binex.insert(pair<string, char>("1100", 'C'));
	binex.insert(pair<string, char>("1101", 'D'));
	binex.insert(pair<string, char>("1110", 'E'));
	binex.insert(pair<string, char>("1111", 'F'));
}

char Binex::Find(string key)
{
	map<string, char>::iterator it;

	it = binex.find(key);
	if (it == binex.end())
	{
		return '?';
	}
	else
	{
		return it->second;
	}
}