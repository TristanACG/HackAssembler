#include "Destinations.h"

Destinations::Destinations()
{
	destinations.insert(pair<string, string>("NULL", "000"));
	destinations.insert(pair<string, string>("M", "001"));
	destinations.insert(pair<string, string>("D", "010"));
	destinations.insert(pair<string, string>("MD", "011"));
	destinations.insert(pair<string, string>("A", "100"));
	destinations.insert(pair<string, string>("AM", "101"));
	destinations.insert(pair<string, string>("AD", "110"));
	destinations.insert(pair<string, string>("AMD", "111"));
}

string Destinations::Find(string key)
{
	map<string, string>::iterator it;

	boost::to_upper(key);
	it = destinations.find(key);
	if (it == destinations.end())
	{
		return ("Key not found: " + key);
	}
	else
	{
		return it->second;
	}
}