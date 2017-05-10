#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <algorithm>
#include "Parameter.h"
#include "Part.h"

class QueryParts
{
public:
	QueryParts();
	~QueryParts();
	vector<vector<string>> parameters;
	//string tag;
	string selectingItem;
	//vector<string> parameteresInBracket;
	vector<Parameter> ParametersList;
	vector<Part> parts;
	vector<Parameter> parametersWithVector;
	vector<vector<string>> examples;
};
