#pragma once
#include <map>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

class Sources
{
public:
	Sources();
	string Find(string);
private:
	map<string, string>sources;
};

