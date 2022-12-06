#pragma once
#include <map>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

class Jumps
{
public:
	Jumps();
	string Find(string);
private:
	map<string, string>jumps;

};

