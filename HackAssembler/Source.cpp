#include "Source.h"

Sources::Sources()
{
	sources.insert(pair<string, string>("0", "101010"));
	sources.insert(pair<string, string>("1", "111111"));
	sources.insert(pair<string, string>("-1","111010"));
	sources.insert(pair<string, string>("D", "001100"));
	sources.insert(pair<string, string>("A", "110000"));
	sources.insert(pair<string, string>("!D","001101"));
	sources.insert(pair<string, string>("!A","110001"));
	sources.insert(pair<string, string>("-D","001111"));
	sources.insert(pair<string, string>("-A","110011"));
	sources.insert(pair<string, string>("D+1","011111"));
	sources.insert(pair<string, string>("A+1","110111"));
	sources.insert(pair<string, string>("D-1","001110"));
	sources.insert(pair<string, string>("A-1","110010"));
	sources.insert(pair<string, string>("D+A","000010"));
	sources.insert(pair<string, string>("D-A","010011"));
	sources.insert(pair<string, string>("A-D","000111"));
	sources.insert(pair<string, string>("D&A","000000"));
	sources.insert(pair<string, string>("D|A","010101"));

	sources.insert(pair<string, string>("M","110000"));
	sources.insert(pair<string, string>("!M","110001"));
	sources.insert(pair<string, string>("-M", "110011"));
	sources.insert(pair<string, string>("M+1","110111"));
	sources.insert(pair<string, string>("M-1","110010"));
	sources.insert(pair<string, string>("D+M","000010"));
	sources.insert(pair<string, string>("M+D","000010"));
	sources.insert(pair<string, string>("D-M","010011"));
	sources.insert(pair<string, string>("M-D","000111"));
	sources.insert(pair<string, string>("D&M","000000"));
	sources.insert(pair<string, string>("D|M","010101"));

}

string Sources::Find(string key)
{
	map<string, string>::iterator it;

	boost::to_upper(key);
	it = sources.find(key);
	if (it == sources.end())
	{
		return ("Key not found: " + key);
	}
	else
	{
		return it->second;
	}
}
