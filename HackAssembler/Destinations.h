#pragma once
#include <map>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

class Destinations
{
public:
	Destinations();
	string Find(string);
private:
	map<string, string>destinations;

};

