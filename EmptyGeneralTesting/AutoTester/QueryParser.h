#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include "QueryParts.h"
using namespace std;
class QueryParser
{
public:
	QueryParser();
	~QueryParser();
	vector<vector<string>> ReadFile(string path);
private:
	QueryParts SplitQuery(vector<string> query);
	const vector<string> allowedWords = { "calls","calls*","modifies","modifies*","uses","uses*","follows","follows*","parent","parent*","affects","affects*","next","next*" };
	const vector<string> parameters = { "assign","stmt","var","proc" };
};