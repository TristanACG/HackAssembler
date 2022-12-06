#include "pch.h"
#include "../HackAssembler/Jumps.h"

TEST(JumpsTest, ExistingValues) 
{
	Jumps jumps = Jumps();
	
	ASSERT_EQ("001", jumps.Find("JGT"));
	ASSERT_EQ("110", jumps.Find("JLE"));
	ASSERT_EQ("111", jumps.Find("JMP"));

	/*jumps.insert(pair<string, string>("null", "000"));
	jumps.insert(pair<string, string>("JGT", "001"));
	jumps.insert(pair<string, string>("JEQ", "010"));
	jumps.insert(pair<string, string>("JGE", "011"));
	jumps.insert(pair<string, string>("JLT", "100"));
	jumps.insert(pair<string, string>("JNE", "101"));
	jumps.insert(pair<string, string>("JLE", "110"));
	jumps.insert(pair<string, string>("JMP", "111"));*/
}