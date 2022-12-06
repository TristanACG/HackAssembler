#pragma once
#include <map>
#include <string>

using namespace std;

class Binex
{
public:
	Binex();
	char Find(string);
private:
	map<string, char>binex;
};

