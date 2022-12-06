#include "Jumps.h"

Jumps::Jumps()
{
	jumps.insert(pair<string, string>("NULL","000"));
	jumps.insert(pair<string, string>("JGT", "001"));
	jumps.insert(pair<string, string>("JEQ", "010"));
	jumps.insert(pair<string, string>("JGE", "011"));
	jumps.insert(pair<string, string>("JLT", "100"));
	jumps.insert(pair<string, string>("JNE", "101"));
	jumps.insert(pair<string, string>("JLE", "110"));
	jumps.insert(pair<string, string>("JMP", "111"));
}

string Jumps::Find(string key)
{
	map<string, string>::iterator it;
	
	boost::to_upper(key);
	it = jumps.find(key);
	if (it == jumps.end())
	{
		return ("Key not found: " + key);
	}
	else
	{
		return it->second;
	}
}
